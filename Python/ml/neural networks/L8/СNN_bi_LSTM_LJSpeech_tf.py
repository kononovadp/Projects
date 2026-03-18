import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import numpy as np
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
from tensorflow.keras import layers, models
from tensorflow.keras.optimizers import Adam
from tensorflow.keras import backend as K
import librosa
import pandas as pd
from datetime import datetime
dagshub = '/content/lab8/dagshub_storage/'
google_drive = '/content/drive/MyDrive/Colab Notebooks/L8/'
wavs_path = dagshub + "LJSpeech-1.1/wavs/"
metadata_path = dagshub + "LJSpeech-1.1/metadata.csv"
sampling_rate = 22050
max_audio_len = 1600
batch_size = 8
count_of_epochs = 10
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def load_audio(file_path):
	audio, _ = librosa.load(file_path, sr=sampling_rate)
	spectrogram = librosa.feature.melspectrogram(y=audio, sr=sampling_rate, n_mels=128)
	log_spec = librosa.power_to_db(spectrogram)
	log_spec = log_spec.T
	if log_spec.shape[0] > max_audio_len:
		log_spec = log_spec[:max_audio_len, :]
	else:
		pad_width = max_audio_len - log_spec.shape[0]
		log_spec = np.pad(log_spec, ((0, pad_width), (0, 0)), mode='constant')
	return log_spec
def text_to_sequence(text, char_to_num):
	return [char_to_num[c] for c in text.lower() if c in char_to_num]
def sequence_to_text(seq, num_to_char):
	return ''.join([num_to_char[i] for i in seq])
def decode_prediction(pred, num_to_char):
	input_len = np.ones(pred.shape[0]) * pred.shape[1]
	decoded, _ = K.ctc_decode(pred, input_length=input_len, greedy=True)
	decoded = K.get_value(decoded[0])
	return ["".join([num_to_char.get(i, '') for i in seq if i != -1]) for seq in decoded]
def ctc_loss_fn(args):
	y_pred, labels, input_len, label_len = args
	return K.ctc_batch_cost(labels, y_pred, input_len, label_len)
def dummy_ctc_loss(y_true, y_pred):
	return y_pred
def train():
	print("Preparing datasets...",flush=True,end="")
	start=datetime.now()
	vocab = sorted(set("abcdefghijklmnopqrstuvwxyz '"))
	char_to_num = {c: i for i, c in enumerate(vocab)}
	vocab_size = len(vocab)
	num_classes = vocab_size + 1	
	num_to_char = {i: c for c, i in char_to_num.items()}
	audio_files = [f for f in os.listdir(dataset_path) if f.endswith('.wav')]
	# texts = ["example transcription"] * len(audio_files)
	metadata = pd.read_csv(metadata_path, sep='|', header=None, names=["file_id", "text", "norm_text"])
	texts_dict = {f"{row['file_id']}.wav": row['text'] for _, row in metadata.iterrows()}
	texts = [texts_dict[f] for f in audio_files]
	X = np.array([load_audio(os.path.join(dataset_path, f)) for f in audio_files])
	y = [text_to_sequence(t, char_to_num) for t in texts]
	downsample_factor = 4
	output_lengths = np.ones((len(X), 1)) * (max_audio_len // downsample_factor)
	clean_X = []
	clean_y = []
	clean_label_lengths = []
	clean_input_lengths = []
	for i in range(len(y)):
		label_len = len(y[i])
		input_len = output_lengths[i][0]
		if label_len <= input_len:
			clean_X.append(X[i])
			clean_y.append(y[i])
			clean_label_lengths.append([label_len])
			clean_input_lengths.append([input_len])
		else:
			print(f"Skipping sample {i}: label len {label_len}, input len {input_len}")
	X = np.array(clean_X)
	label_lengths = np.array(clean_label_lengths)
	input_lengths = np.array(clean_input_lengths)
	max_label_len = max(len(seq) for seq in clean_y)
	y_padded = np.ones((len(clean_y), max_label_len)) * -1
	for i, seq in enumerate(clean_y):
		y_padded[i, :len(seq)] = seq
	class CTCAccuracyCallback(tf.keras.callbacks.Callback):
		def __init__(self, pred_model, X_val, y_val, input_lengths, label_lengths):
			super().__init__()
			self.pred_model = pred_model
			self.X_val = X_val
			self.y_val = y_val
			self.input_lengths = input_lengths
			self.label_lengths = label_lengths
		def on_epoch_end(self, epoch, logs=None):
			preds = self.pred_model.predict(self.X_val)
			input_len = np.ones(preds.shape[0]) * preds.shape[1]
			decoded, _ = K.ctc_decode(preds, input_length=input_len, greedy=True)
			decoded_sequences = K.get_value(decoded[0])
			total_chars = 0
			correct_chars = 0
			for i in range(len(decoded_sequences)):
				pred_seq = decoded_sequences[i]
				true_seq = self.y_val[i][:int(self.label_lengths[i][0])]
				pred_seq = pred_seq[pred_seq != -1]
				compare_len = min(len(pred_seq), len(true_seq))
				total_chars += compare_len
				correct_chars += np.sum(pred_seq[:compare_len] == true_seq[:compare_len])
			acc = (correct_chars / total_chars) * 100 if total_chars > 0 else 0
			print("Epoch ", epoch+1, "accuracy: ", f"{acc:.2f}%")
	inputs = layers.Input(shape=(max_audio_len, 128))
	x = layers.Conv1D(256, 11, activation='relu', padding='same')(inputs)
	x = layers.MaxPooling1D(2)(x)
	x = layers.Conv1D(256, 11, activation='relu', padding='same')(x)
	x = layers.MaxPooling1D(2)(x)
	x = layers.BatchNormalization()(x)
	x = layers.Bidirectional(layers.LSTM(256, return_sequences=True))(x)
	x = layers.Bidirectional(layers.LSTM(256, return_sequences=True))(x)
	# x = layers.Dense(num_classes, activation='softmax')(x)
	y_pred = layers.Dense(num_classes, activation='softmax')(x)
	pred_model = models.Model(inputs=inputs, outputs=y_pred)
	labels = layers.Input(shape=(None,), dtype='int32', name='labels')
	input_len = layers.Input(shape=(1,), dtype='int64', name='input_length')
	label_len = layers.Input(shape=(1,), dtype='int64', name='label_length')
	loss_out = layers.Lambda(ctc_loss_fn, output_shape=(1,), name='ctc')(
		[y_pred, labels, input_len, label_len])
	model = models.Model(inputs=[inputs, labels, input_len, label_len], outputs=loss_out)
	# model.compile(optimizer=Adam(), loss={'ctc': lambda y_true, y_pred: y_pred})
	# model.compile(optimizer=Adam(), loss='sparse_categorical_crossentropy')
	# model.compile(optimizer=Adam(), loss={'ctc': dummy_ctc_loss})
	model.compile(optimizer=Adam(), loss=dummy_ctc_loss)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time of datasets preparation: ",hours,":",minutes,":",seconds)
	start=datetime.now()
	model.fit(
		x=[X, y_padded, input_lengths, label_lengths],
		y=np.zeros(len(X)),
		batch_size=batch_size,
		epochs=count_of_epochs,
		callbacks=[CTCAccuracyCallback(pred_model, X, y_padded, input_lengths, label_lengths)])
	# model_path = google_drive + 'СNN_bi_LSTM_LJSpeech_tf_' + str(count_of_epochs)+'_epochs.keras'
	# model.save(model_path)
	pred_model = models.Model(inputs=inputs, outputs=y_pred)
	model_path = google_drive + 'СNN_bi_LSTM_LJSpeech_tf_' + str(count_of_epochs)+'_epochs.keras'
	pred_model.save(model_path)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of training: ",hours,":",minutes,":",seconds)
	pred_model = models.Model(inputs=inputs, outputs=x)
	sample_pred = pred_model.predict(X[:2])
	decoded_texts = decode_prediction(sample_pred, num_to_char)
	for i, txt in enumerate(decoded_texts):
		print("Predicted Text ",i+1,": ",txt)
def eval_and_pred(model_path):
	metadata = pd.read_csv(metadata_path, sep='|', header=None, names=["file_id", "text", "norm_text"])
	test_rows = metadata.sample(n=10, random_state=42)
	X_test = []
	y_test = []
	input_lengths_test = []
	label_lengths_test = []
	vocab = sorted(set("abcdefghijklmnopqrstuvwxyz '"))
	char_to_num = {c: i for i, c in enumerate(vocab)}
	num_to_char = {i: c for c, i in char_to_num.items()}
	for _, row in test_rows.iterrows():
		file_path = os.path.join(dataset_path, f"{row['file_id']}.wav")
		spectrogram = load_audio(file_path)
		text_seq = text_to_sequence(row['text'], char_to_num)
		input_len = spectrogram.shape[0] // 4
		if len(text_seq) > input_len:
			continue
		X_test.append(spectrogram)
		y_test.append(text_seq)
		input_lengths_test.append([input_len])
		label_lengths_test.append([len(text_seq)])
	X_test = np.array(X_test)
	input_lengths_test = np.array(input_lengths_test)
	label_lengths_test = np.array(label_lengths_test)
	max_len = max(len(seq) for seq in y_test)
	y_test_padded = np.ones((len(y_test), max_len)) * -1
	for i, seq in enumerate(y_test):
		y_test_padded[i, :len(seq)] = seq
	loaded_pred_model = tf.keras.models.load_model(google_drive+model_path)
	preds = loaded_pred_model.predict(X_test, verbose=False)
	decoded = decode_prediction(preds, num_to_char)
	total_chars = 0
	correct_chars = 0
	for i in range(len(decoded)):
		pred_seq = [char_to_num.get(c, -1) for c in decoded[i]]
		true_seq = y_test[i][:int(label_lengths_test[i][0])]
		compare_len = min(len(pred_seq), len(true_seq))
		total_chars += compare_len
		correct_chars += np.sum(
			np.array(pred_seq[:compare_len]) == np.array(true_seq[:compare_len]))
	accuracy = (correct_chars / total_chars) * 100 if total_chars > 0 else 0
	print("Accuracy: ", f"{accuracy:.3f}%")
	for i in range(len(decoded)):
		text = sequence_to_text(y_test[i][:int(label_lengths_test[i][0])], num_to_char)
		print("Text: ", text)
		print("Pred: ", decoded[i])
		print("-" * 90)