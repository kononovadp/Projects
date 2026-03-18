import pandas as pd
import numpy as np
import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt
from IPython import display
from jiwer import wer
import io
from contextlib import redirect_stdout
from keras.saving import register_keras_serializable
from random import randrange
from datetime import datetime
dagshub = '/content/lab8/dagshub_storage/'
google_drive = '/content/drive/MyDrive/Colab Notebooks/L8/'
wavs_path = dagshub + "LJSpeech-1.1/wavs/"
metadata_path = dagshub + "LJSpeech-1.1/metadata.csv"
count_of_epochs = 10
batch_size = 8
frame_length = 256
frame_step = 160
fft_length = 384
characters = [x for x in "abcdefghijklmnopqrstuvwxyz'?! "]
char_to_num = keras.layers.StringLookup(vocabulary=characters, oov_token="")
num_to_char = keras.layers.StringLookup(
	vocabulary=char_to_num.get_vocabulary(),
	oov_token="",
	invert=True)
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def encode_single_sample(wav_file, label):
	file = tf.io.read_file(wavs_path + wav_file + ".wav")
	audio, _ = tf.audio.decode_wav(file)
	audio = tf.squeeze(audio, axis=-1)	
	audio = tf.cast(audio, tf.float32)
	spectrogram = tf.signal.stft(audio, frame_length=frame_length, frame_step=frame_step, fft_length=fft_length)
	spectrogram = tf.abs(spectrogram)
	spectrogram = tf.math.pow(spectrogram, 0.5)
	means = tf.math.reduce_mean(spectrogram, 1, keepdims=True)
	stddevs = tf.math.reduce_std(spectrogram, 1, keepdims=True)
	spectrogram = (spectrogram - means) / (stddevs + 1e-10)
	label = tf.strings.lower(label)
	label = tf.strings.unicode_split(label, input_encoding="UTF-8")
	label = char_to_num(label)
	return spectrogram, label
@register_keras_serializable()
def CTCLoss(y_true, y_pred):
	batch_len = tf.cast(tf.shape(y_true)[0], dtype="int64")
	input_length = tf.cast(tf.shape(y_pred)[1], dtype="int64")
	label_length = tf.cast(tf.shape(y_true)[1], dtype="int64")
	input_length = input_length * tf.ones(shape=(batch_len, 1), dtype="int64")
	label_length = label_length * tf.ones(shape=(batch_len, 1), dtype="int64")
	loss = keras.backend.ctc_batch_cost(y_true, y_pred, input_length, label_length)
	return loss
# https://nvidia.github.io/OpenSeq2Seq/html/speech-recognition/deepspeech2.html
def deep_speech2_model(input_dim, output_dim, rnn_layers=5, rnn_units=128):
	input_spectrogram = layers.Input((None, input_dim), name="input")
	x = layers.Reshape((-1, input_dim, 1), name="expand_dim")(input_spectrogram)
	x = layers.Conv2D(
		filters=32,
		kernel_size=[11, 41],
		strides=[2, 2],
		padding="same",
		use_bias=False,
		name="conv_1")(x)
	x = layers.BatchNormalization(name="conv_1_bn")(x)
	x = layers.ReLU(name="conv_1_relu")(x)
	x = layers.Conv2D(
		filters=32,
		kernel_size=[11, 21],
		strides=[1, 2],
		padding="same",
		use_bias=False,
		name="conv_2")(x)
	x = layers.BatchNormalization(name="conv_2_bn")(x)
	x = layers.ReLU(name="conv_2_relu")(x)
	x = layers.Reshape((-1, x.shape[-2] * x.shape[-1]))(x)
	for i in range(1, rnn_layers + 1):
		recurrent = layers.GRU(
			units=rnn_units,
			activation="tanh",
			recurrent_activation="sigmoid",
			use_bias=True,
			return_sequences=True,
			reset_after=True,
			name=f"gru_{i}")
		x = layers.Bidirectional(
			recurrent, name=f"bidirectional_{i}", merge_mode="concat")(x)
		if i < rnn_layers:
			x = layers.Dropout(rate=0.5)(x)
	x = layers.Dense(units=rnn_units * 2, name="dense_1")(x)
	x = layers.ReLU(name="dense_1_relu")(x)
	x = layers.Dropout(rate=0.5)(x)
	output = layers.Dense(units=output_dim + 1, activation="softmax")(x)
	model = keras.Model(input_spectrogram, output, name="DeepSpeech_2")
	opt = keras.optimizers.Adam(learning_rate=1e-4)
	model.compile(optimizer=opt, loss=CTCLoss)
	return model
def СNN_bi_LSTM_model(input_dim=(None, 193, 1), num_classes=32):
	input_spectrogram = tf.keras.Input(shape=input_dim, name="input")
	x = layers.Conv2D(32, kernel_size=(3, 3), padding="same", activation="relu")(input_spectrogram)
	x = layers.BatchNormalization()(x)
	x = layers.MaxPooling2D(pool_size=(2, 2))(x)
	x = layers.Conv2D(64, kernel_size=(3, 3), padding="same", activation="relu")(x)
	x = layers.BatchNormalization()(x)
	x = layers.MaxPooling2D(pool_size=(2, 2))(x)
	new_shape = tf.keras.layers.Reshape((-1, x.shape[2] * x.shape[3]))(x)
	x = layers.Bidirectional(layers.LSTM(128, return_sequences=True))(new_shape)
	x = layers.Bidirectional(layers.LSTM(128, return_sequences=True))(x)
	x = layers.Dense(128, activation="relu")(x)
	x = layers.Dropout(0.2)(x)
	output = layers.Dense(num_classes, activation="softmax", name="output")(x)
	model = models.Model(inputs=input_spectrogram, outputs=output, name="CNN_BiLSTM_Model")
	model.compile(optimizer=keras.optimizers.Adam(learning_rate=1e-4), loss=CTCLoss)
	return model
"""def СNN_bi_LSTM_model(input_dim=(None, 193, 1), num_classes=32):
    input_spectrogram = tf.keras.Input(shape=input_dim, name="input")
    x = layers.Conv2D(16, kernel_size=(3, 3), padding="same", activation="relu")(input_spectrogram)
    x = layers.BatchNormalization()(x)
    x = layers.MaxPooling2D(pool_size=(2, 2))(x)
    x = layers.Conv2D(32, kernel_size=(3, 3), padding="same", activation="relu")(x)
    x = layers.BatchNormalization()(x)
    x = layers.MaxPooling2D(pool_size=(2, 2))(x)
    new_shape = tf.keras.layers.Reshape((-1, x.shape[2] * x.shape[3]))(x)
    x = layers.Bidirectional(layers.LSTM(64, return_sequences=True))(new_shape)
    x = layers.Bidirectional(layers.LSTM(64, return_sequences=True))(x)
    x = layers.Dense(64, activation="relu")(x)
    x = layers.Dropout(0.2)(x)
    output = layers.Dense(num_classes, activation="softmax", name="output")(x)
    model = models.Model(inputs=input_spectrogram, outputs=output, name="CNN_BiLSTM_Model")
    model.compile(optimizer=keras.optimizers.Adam(learning_rate=1e-3), loss=CTCLoss)
    return model"""
def decode_batch_predictions(pred):
	input_len = np.ones(pred.shape[0]) * pred.shape[1]
	# results = keras.backend.ctc_decode(pred, input_length=input_len, greedy=True)[0][0]
	results = keras.backend.ctc_decode(pred, input_length=input_len, greedy=False, beam_width=100)[0][0]
	output_text = []
	for result in results:
		result = tf.strings.reduce_join(num_to_char(result)).numpy().decode("utf-8")
		output_text.append(result)
	return output_text
class DisplayAccuracy(keras.callbacks.Callback):
	def __init__(self, val_dataset, decoder, num_to_char, interval=1):
		super().__init__()
		self.val_dataset = val_dataset
		self.decoder = decoder
		self.num_to_char = num_to_char
		self.interval = interval
	def on_epoch_end(self, epoch: int, logs=None):
		if (epoch + 1) % self.interval != 0:
			return
		total_chars = 0
		correct_chars = 0
		for batch in self.val_dataset.take(1):
			X, y = batch
			y_pred = self.model.predict(X, verbose=False)
			decoded = self.decoder(y_pred)
			for i in range(len(decoded)):
				true = tf.gather(y[i], tf.where(tf.not_equal(y[i], -1)))
				true_text = tf.strings.reduce_join(self.num_to_char(tf.squeeze(true, axis=-1))).numpy().decode("utf-8")
				pred_text = decoded[i]
				compare_len = min(len(true_text), len(pred_text))
				correct = sum([true_text[j] == pred_text[j] for j in range(compare_len)])
				total_chars += len(true_text)
				correct_chars += correct
		acc = 100 * correct_chars / total_chars if total_chars else 0
		print("\nEpoch ", epoch+1, "accuracy: ", f"{acc:.5f}%")
def train():
	print("Preparing datasets and model...",flush=True,end="")
	start=datetime.now()
	metadata_df = pd.read_csv(metadata_path, sep="|", header=None, quoting=3)
	metadata_df.columns = ["file_name", "transcription", "normalized_transcription"]
	metadata_df = metadata_df[["file_name", "normalized_transcription"]]
	metadata_df = metadata_df.sample(frac=1).reset_index(drop=True)
	metadata_df.head(3)	
	split = int(len(metadata_df) * 0.90)
	df_train = metadata_df[:split]
	df_val = metadata_df[split:]	
	# df_train = metadata_df
	# df_val = metadata_df
	train_dataset = tf.data.Dataset.from_tensor_slices(
		(list(df_train["file_name"]), list(df_train["normalized_transcription"])))
	train_dataset = (
		train_dataset.map(encode_single_sample, num_parallel_calls=tf.data.AUTOTUNE)
		.padded_batch(batch_size)
		.prefetch(buffer_size=tf.data.AUTOTUNE))
	validation_dataset = tf.data.Dataset.from_tensor_slices(
		(list(df_val["file_name"]), list(df_val["normalized_transcription"])))
	validation_dataset = (
		validation_dataset.map(encode_single_sample, num_parallel_calls=tf.data.AUTOTUNE)
		.padded_batch(batch_size)
		.prefetch(buffer_size=tf.data.AUTOTUNE))
	fig = plt.figure(figsize=(8, 5))
	for batch in train_dataset.take(1):
		spectrogram = batch[0][0].numpy()
		spectrogram = np.array([np.trim_zeros(x) for x in np.transpose(spectrogram)])
		# spectrogram = np.array(spectrogram)
		label = batch[1][0]
		label = tf.strings.reduce_join(num_to_char(label)).numpy().decode("utf-8")
		ax = plt.subplot(2, 1, 1)
		ax.imshow(spectrogram, vmax=1)
		ax.set_title(label)
		ax.axis("off")
		file = tf.io.read_file(wavs_path + list(df_train["file_name"])[0] + ".wav")
		audio, _ = tf.audio.decode_wav(file)
		audio = audio.numpy()
		ax = plt.subplot(2, 1, 2)
		plt.plot(audio)
		ax.set_title("Signal Wave")
		ax.set_xlim(0, len(audio))
		# display.display(display.Audio(np.transpose(audio), rate=16000))
	plt.savefig(google_drive + "Spectrogram_and_wav.jpg", dpi = 200) # plt.show()
	# model = deep_speech2_model(
		# input_dim=fft_length // 2 + 1,
		# output_dim=char_to_num.vocabulary_size(),
		# rnn_units=512)
	model = СNN_bi_LSTM_model()
	decoder = decode_batch_predictions
	DisplayAccuracyCallback = DisplayAccuracy(validation_dataset, decoder, num_to_char, interval=1)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	start=datetime.now()
	history = model.fit(
		train_dataset,
		callbacks=[DisplayAccuracyCallback],
		validation_data = validation_dataset,
		epochs=count_of_epochs)
	model_path = google_drive + 'Custom_СNN_bi_LSTM_LJSpeech_tf_' + str(count_of_epochs)+'_epochs.keras'
	model.save(model_path)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of training: ",hours,":",minutes,":",seconds)
	predictions = []
	targets = []
	for batch in validation_dataset:
		X, y = batch
		batch_predictions = model.predict(X, verbose=False)
		batch_predictions = decode_batch_predictions(batch_predictions)
		predictions.extend(batch_predictions)
		for label in y:
			label = tf.strings.reduce_join(num_to_char(label)).numpy().decode("utf-8")
			targets.append(label)
	wer_score = wer(targets, predictions)
	print("-" * 90)
	print(f"Word Error Rate: {wer_score:.4f}")
	print("-" * 90)
	for i in np.random.randint(0, len(predictions), 5):
		print(f"Target    : {targets[i]}")
		print(f"Prediction: {predictions[i]}")
		print("-" * 90)
def evaluate(model_path):
	metadata_df = pd.read_csv(metadata_path, sep="|", header=None, quoting=3)
	metadata_df.columns = ["file_name", "transcription", "normalized_transcription"]
	metadata_df = metadata_df[["file_name", "normalized_transcription"]]
	metadata_df = metadata_df.sample(frac=1).reset_index(drop=True)
	split = int(len(metadata_df) * 0.90)
	df_train = metadata_df[:split]
	df_val = metadata_df[split:]
	validation_dataset = tf.data.Dataset.from_tensor_slices(
		(list(df_val["file_name"]), list(df_val["normalized_transcription"])))
	validation_dataset = (
		validation_dataset.map(encode_single_sample, num_parallel_calls=tf.data.AUTOTUNE)
		.padded_batch(batch_size)
		.prefetch(buffer_size=tf.data.AUTOTUNE))
	model = tf.keras.models.load_model(model_path)
	total_chars = 0
	correct_chars = 0
	for batch in validation_dataset:
		X, y = batch
		y_pred = model.predict(X, verbose=False)
		decoded = decode_batch_predictions(y_pred)
		for i in range(len(decoded)):
			true = tf.gather(y[i], tf.where(tf.not_equal(y[i], -1)))
			true_text = tf.strings.reduce_join(num_to_char(tf.squeeze(true, axis=-1))).numpy().decode("utf-8")
			pred_text = decoded[i]
			compare_len = min(len(true_text), len(pred_text))
			correct = sum([true_text[j] == pred_text[j] for j in range(compare_len)])
			total_chars += len(true_text)
			correct_chars += correct
	acc = 100 * correct_chars / total_chars if total_chars else 0
	print(f"accuracy: {acc:.5f}%")
def speech_to_text(model_path):
	model = tf.keras.models.load_model(model_path)
	metadata_df = pd.read_csv(metadata_path, sep="|", header=None, quoting=3)
	metadata_df.columns = ["file_name", "transcription", "normalized_transcription"]
	metadata_df = metadata_df[["file_name", "normalized_transcription"]]
	sample_index=randrange(len(metadata_df))
	test_sample = metadata_df.iloc[sample_index]
	wav_file = test_sample["file_name"]
	true_text = test_sample["normalized_transcription"]
	file_path = tf.strings.join([wavs_path, "/", wav_file, ".wav"])
	print(file_path)
	file = tf.io.read_file(file_path)
	audio, _ = tf.audio.decode_wav(file)
	audio = tf.squeeze(audio, axis=-1)
	audio = tf.cast(audio, tf.float32)
	spectrogram = tf.signal.stft(audio, frame_length=256, frame_step=160, fft_length=384)
	spectrogram = tf.abs(spectrogram) ** 0.5
	means = tf.math.reduce_mean(spectrogram, 1, keepdims=True)
	stddevs = tf.math.reduce_std(spectrogram, 1, keepdims=True)
	spectrogram = (spectrogram - means) / (stddevs + 1e-10)
	spectrogram = tf.expand_dims(spectrogram, -1)
	y_pred = model.predict(tf.expand_dims(spectrogram, axis=0), verbose=False)
	decoded = decode_batch_predictions(y_pred)
	print("TRUE TEXT: ", true_text)
	print("PREDICTED TEXT: ", decoded[0])