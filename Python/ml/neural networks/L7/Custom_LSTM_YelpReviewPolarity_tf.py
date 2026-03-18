import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
import matplotlib.pyplot as plt
import zipfile
import re
from datetime import datetime
google_drive = "/content/drive/MyDrive/Colab Notebooks/L7/"
count_of_epochs = 10
batch_size = 128
learning_rate = 0.0001
max_words_in_vocab = 20000
max_reviews_length = 300
embedding_dimension = 128
lstm_units = 128
np.random.seed(42)
tf.random.set_seed(42)
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
class lstm_cell(tf.keras.layers.Layer):
	def __init__(self, units, **kwargs):
		self.units = units
		self.state_size = [units, units]  # [h, c]
		super(lstm_cell, self).__init__(**kwargs)
	def build(self, input_shape):
		input_dim = input_shape[-1]
		self.W_i = self.add_weight(shape=(input_dim, self.units), initializer='glorot_uniform')
		self.U_i = self.add_weight(shape=(self.units, self.units), initializer='glorot_uniform')
		self.b_i = self.add_weight(shape=(self.units,), initializer='zeros')
		self.W_f = self.add_weight(shape=(input_dim, self.units), initializer='glorot_uniform')
		self.U_f = self.add_weight(shape=(self.units, self.units), initializer='glorot_uniform')
		self.b_f = self.add_weight(shape=(self.units,), initializer='zeros')
		self.W_c = self.add_weight(shape=(input_dim, self.units), initializer='glorot_uniform')
		self.U_c = self.add_weight(shape=(self.units, self.units), initializer='glorot_uniform')
		self.b_c = self.add_weight(shape=(self.units,), initializer='zeros')
		self.W_o = self.add_weight(shape=(input_dim, self.units), initializer='glorot_uniform')
		self.U_o = self.add_weight(shape=(self.units, self.units), initializer='glorot_uniform')
		self.b_o = self.add_weight(shape=(self.units,), initializer='zeros')			
		self.built = True
	def call(self, inputs, states):
		h_prev, c_prev = states
		i = tf.sigmoid(tf.matmul(inputs, self.W_i) + tf.matmul(h_prev, self.U_i) + self.b_i)
		f = tf.sigmoid(tf.matmul(inputs, self.W_f) + tf.matmul(h_prev, self.U_f) + self.b_f)
		o = tf.sigmoid(tf.matmul(inputs, self.W_o) + tf.matmul(h_prev, self.U_o) + self.b_o)
		g = tf.tanh(tf.matmul(inputs, self.W_c) + tf.matmul(h_prev, self.U_c) + self.b_c)
		c = f * c_prev + i * g
		h = o * tf.tanh(c)
		return h, [h, c]
	def get_config(self):
		config = super(lstm_cell, self).get_config()
		config.update({"units": self.units})
		return config
	@classmethod
	def from_config(cls, config):
		return cls(**config)
def lstm_model(vocab_size):
	tf.keras.utils.get_custom_objects()['lstm_cell'] = lstm_cell
	model = tf.keras.Sequential([
		tf.keras.layers.Embedding(vocab_size, embedding_dimension, input_length=max_reviews_length),
		tf.keras.layers.RNN(lstm_cell(lstm_units), return_sequences=True),
		tf.keras.layers.RNN(lstm_cell(lstm_units)),
		tf.keras.layers.Dense(64, activation='relu'),
		tf.keras.layers.Dropout(0.5),
		tf.keras.layers.Dense(1, activation='sigmoid')])
	model.compile(
		optimizer=tf.keras.optimizers.Adam(1e-3),
		loss='binary_crossentropy',
		metrics=['accuracy'])
	return model
def clean_text(text):
	if isinstance(text, str):
		text = text.lower()
		text = re.sub(r'<.*?>', '', text)
		text = re.sub(r'http\S+|www\S+|https\S+', '', text)
		text = re.sub(r'[^\w\s]', '', text)
		text = re.sub(r'\d+', '', text)
		text = re.sub(r'\s+', ' ', text).strip()
		return text
	return ""
def test_model_on_samples(model, tokenizer, samples):
	print("\nTesting model on sample texts:")
	sequences = tokenizer.texts_to_sequences(samples)
	padded_sequences = pad_sequences(sequences, maxlen=max_reviews_length)
	predictions = model.predict(padded_sequences)
	for i, text in enumerate(samples):
		sentiment = "Positive" if predictions[i][0] > 0.5 else "Negative"
		confidence = predictions[i][0] if predictions[i][0] > 0.5 else 1 - predictions[i][0]
		print(f"Sample: '{text[:100]}...'")
		print(f"Sentiment: {sentiment} (confidence: {confidence:.2f})\n")
def train():
	print("Preparing datasets...",flush=True,end="")
	start=datetime.now()
	train_df = pd.read_csv(google_drive + "train.csv", header=None)
	test_df = pd.read_csv(google_drive + "test.csv", header=None)
	x_train = train_df[1].values
	y_train = train_df[0].values - 1
	x_train = [clean_text(text) for text in x_train]
	x_test = test_df[1].values
	y_test = test_df[0].values - 1
	x_test = [clean_text(text) for text in x_test]
	tokenizer = Tokenizer(num_words=max_words_in_vocab)
	tokenizer.fit_on_texts(x_train)
	X_train_seq = tokenizer.texts_to_sequences(x_train)
	X_test_seq = tokenizer.texts_to_sequences(x_test)
	X_train_padded = pad_sequences(X_train_seq, maxlen=max_reviews_length)
	X_test_padded = pad_sequences(X_test_seq, maxlen=max_reviews_length)
	model = lstm_model(min(len(tokenizer.word_index) + 1, max_words_in_vocab))
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time of datasets preparation: ",hours,":",minutes,":",seconds)
	start=datetime.now()
	history = model.fit(
		X_train_padded, y_train,
		validation_data=(X_test_padded, y_test),
		epochs=count_of_epochs,
		batch_size=batch_size)
	model_path = google_drive + 'Custom_LSTM_YelpReviewPolarity_tf_' + str(count_of_epochs)+'_epochs.keras'
	model.save(model_path)
	plt.figure(figsize=(12, 5))
	plt.subplot(1, 2, 1)
	plt.plot(history.history['accuracy'])
	plt.plot(history.history['val_accuracy'])
	plt.title('Model Accuracy')
	plt.ylabel('Accuracy')
	plt.xlabel('Epoch')
	plt.legend(['Train', 'Validation'], loc='lower right')
	plt.subplot(1, 2, 2)
	plt.plot(history.history['loss'])
	plt.plot(history.history['val_loss'])
	plt.title('Model Loss')
	plt.ylabel('Loss')
	plt.xlabel('Epoch')
	plt.legend(['Train', 'Validation'], loc='upper right')    
	plt.tight_layout()
	plt.savefig(google_drive + 'Custom_LSTM_tf_history.jpg', dpi = 200)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of training: ",hours,":",minutes,":",seconds)
	print("The model was saved as ",model_path)
	print("The history was saved as ",google_drive + "Custom_LSTM_tf_history.jpg")
def evaluate(model_path):
	print("Model evaluation... Preparing datasets...",flush=True,end="")
	start=datetime.now()
	test_df = pd.read_csv(google_drive + "test.csv", header=None)
	x_test = test_df[1].values
	y_test = test_df[0].values - 1
	x_test = [clean_text(text) for text in x_test]
	tokenizer = Tokenizer(num_words=max_words_in_vocab)
	X_test_seq = tokenizer.texts_to_sequences(x_test)
	X_test_padded = pad_sequences(X_test_seq, maxlen=max_reviews_length)
	tf.keras.utils.get_custom_objects()['lstm_cell'] = lstm_cell
	model = tf.keras.models.load_model(google_drive + model_path, compile=True)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time of datasets preparation: ",hours,":",minutes,":",seconds)
	test_loss, test_acc = model.evaluate(X_test_padded, y_test, verbose=False)
	print("Test accuracy: ",f"{test_acc:.4f}","; test loss: ",f"{test_loss:.4f}")
def predict(model_path, sample_texts):
	print("Preparing datasets...",flush=True,end="")
	start=datetime.now()
	train_df = pd.read_csv(google_drive + "train.csv", names=['label', 'text'])
	test_df = pd.read_csv(google_drive + "test.csv", names=['label', 'text'])
	train_df.dropna(inplace=True)
	test_df.dropna(inplace=True)
	train_df['label'] = train_df['label'].map({1: 0, 2: 1})
	test_df['label'] = test_df['label'].map({1: 0, 2: 1})
	X_train = train_df['text'].values
	y_train = train_df['label'].values
	X_test = test_df['text'].values
	y_test = test_df['label'].values
	tokenizer = Tokenizer(num_words=max_words_in_vocab, oov_token="<OOV>")
	tokenizer.fit_on_texts(X_train)
	sequences = tokenizer.texts_to_sequences(sample_texts)
	padded_sequences = pad_sequences(sequences, maxlen=max_reviews_length)
	tf.keras.utils.get_custom_objects()['lstm_cell'] = lstm_cell
	model = tf.keras.models.load_model(google_drive + model_path, compile=True)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time of datasets preparation: ",hours,":",minutes,":",seconds)
	predictions = model.predict(padded_sequences, verbose=False)
	print("Testing model on sample texts:")
	for i, text in enumerate(sample_texts):
		sentiment = "Positive" if predictions[i][0] > 0.5 else "Negative"
		confidence = predictions[i][0] if predictions[i][0] > 0.5 else 1 - predictions[i][0]
		print(text[:85],"...")
		print("Sentiment: ",sentiment, f"(confidence: {confidence:.2f})")
		print('-'*90)