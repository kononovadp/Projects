import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Embedding, LSTM, Dense, Dropout
from tensorflow.keras.optimizers import Adam
import matplotlib.pyplot as plt
from datetime import datetime
google_drive = "/content/drive/MyDrive/Colab Notebooks/L7/"
count_of_epochs = 10
batch_size = 128
learning_rate = 0.0001
max_words_in_vocab = 20000
max_reviews_length = 300
embedding_dimension = 128
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def prepare_datasets():
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
	X_train_seq = tokenizer.texts_to_sequences(X_train)
	X_test_seq = tokenizer.texts_to_sequences(X_test)
	X_train_pad = pad_sequences(X_train_seq, maxlen=max_reviews_length, padding='post', truncating='post')
	X_test_pad = pad_sequences(X_test_seq, maxlen=max_reviews_length, padding='post', truncating='post')
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time of datasets preparation: ",hours,":",minutes,":",seconds)
	return X_train_pad, y_train, X_test_pad, y_test
def train():	
	X_train_pad, y_train, X_test_pad, y_test, tokenizer = prepare_datasets()
	start=datetime.now()
	model = Sequential([
		Embedding(input_dim=max_words_in_vocab, output_dim=embedding_dimension, input_length=max_reviews_length),
		LSTM(128, return_sequences=True),
		Dropout(0.5),
		LSTM(64),
		Dropout(0.5),
		Dense(64, activation='relu'),
		Dense(1, activation='sigmoid')])
	model.compile(loss='binary_crossentropy', optimizer=Adam(learning_rate=learning_rate), metrics=['accuracy'])
	history = model.fit(X_train_pad, y_train, epochs=count_of_epochs, batch_size=batch_size, validation_split=0.1)
	model_path = google_drive + 'LSTM_YelpReviewPolarity_tf_' + str(count_of_epochs)+'_epochs.keras'
	model.save(model_path)
	plt.plot(history.history['accuracy'], label='train accuracy')
	plt.plot(history.history['val_accuracy'], label='validation accuracy')
	plt.xlabel('Epochs')
	plt.ylabel('Accuracy')
	plt.legend()
	plt.savefig(google_drive + "LSTM_tf_history.jpg", dpi = 200)
	plt.close()
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of training: ",hours,":",minutes,":",seconds)
	print("The model was saved as ",model_path)
	print("The history was saved as ",google_drive + "LSTM_tf_history.jpg")
def evaluate(model_path):
	X_train_pad, y_train, X_test_pad, y_test = prepare_datasets()
	print("Model evaluation...",flush=True,end="")
	model = tf.keras.models.load_model(google_drive + model_path, compile=False)
	model.compile(loss='binary_crossentropy', optimizer=Adam(learning_rate=learning_rate), metrics=['accuracy'])
	test_loss, test_acc = model.evaluate(X_test_pad, y_test, verbose=False)
	print(" Test accuracy: ",f"{test_acc:.4f}","; test loss: ",f"{test_loss:.4f}")
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