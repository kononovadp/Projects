import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import cv2
import json
import zipfile
import shutil
import random
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.utils import class_weight
from sklearn.metrics import classification_report, confusion_matrix
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
from tensorflow.keras.applications import InceptionV3
from tensorflow.keras.applications import Xception
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras import layers, models
from tensorflow.keras.layers import Dense, GlobalAveragePooling2D
from tensorflow.keras.models import Model
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing import image
import matplotlib.pyplot as plt
from tensorflow.keras.models import load_model
from keras.src import backend
from keras.src.engine import training
from keras.src.utils import data_utils
from keras.src.applications import imagenet_utils
from datetime import datetime
count_of_epochs = 12
batch_size = 32
learning_rate = 0.0001
image_size = 128
dagshub = ''
google_drive = ''
train_path = dagshub + 'train'
val_path = dagshub + 'test'
test_path = dagshub + 'test'
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def xception_model(count_of_classes):
	inputs = layers.Input(shape=(image_size, image_size, 3))
	channel_axis = 1 if backend.image_data_format() == "channels_first" else -1
	x = layers.Conv2D(32, (3, 3), strides=(2, 2), use_bias=False)(inputs)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	x = layers.Conv2D(64, (3, 3), use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	residual = layers.Conv2D(128, (1, 1), strides=(2, 2), padding="same", use_bias=False)(x)
	residual = layers.BatchNormalization(axis=channel_axis)(residual)
	x = layers.SeparableConv2D(128, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(128, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.MaxPooling2D((3, 3), strides=(2, 2), padding="same")(x)
	x = layers.add([x, residual])
	residual = layers.Conv2D(256, (1, 1), strides=(2, 2), padding="same", use_bias=False)(x)
	residual = layers.BatchNormalization(axis=channel_axis)(residual)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(256, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(256, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.MaxPooling2D((3, 3), strides=(2, 2), padding="same")(x)
	x = layers.add([x, residual])
	residual = layers.Conv2D(728, (1, 1), strides=(2, 2), padding="same", use_bias=False)(x)
	residual = layers.BatchNormalization(axis=channel_axis)(residual)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(728, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(728, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.MaxPooling2D((3, 3), strides=(2, 2), padding="same")(x)
	x = layers.add([x, residual])
	for i in range(8):
		residual = x
		prefix = "block" + str(i + 5)
		x = layers.Activation("relu")(x)
		x = layers.SeparableConv2D(728, (3, 3), padding="same", use_bias=False)(x)
		x = layers.BatchNormalization(axis=channel_axis)(x)
		x = layers.Activation("relu")(x)
		x = layers.SeparableConv2D(728, (3, 3), padding="same", use_bias=False)(x)
		x = layers.BatchNormalization(axis=channel_axis)(x)
		x = layers.Activation("relu")(x)
		x = layers.SeparableConv2D(728, (3, 3), padding="same", use_bias=False)(x)
		x = layers.BatchNormalization(axis=channel_axis)(x)
		x = layers.add([x, residual])
	residual = layers.Conv2D(1024, (1, 1), strides=(2, 2), padding="same", use_bias=False)(x)
	residual = layers.BatchNormalization(axis=channel_axis)(residual)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(728, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(1024, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.MaxPooling2D((3, 3), strides=(2, 2), padding="same")(x)
	x = layers.add([x, residual])
	x = layers.SeparableConv2D(1536, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	x = layers.SeparableConv2D(2048, (3, 3), padding="same", use_bias=False)(x)
	x = layers.BatchNormalization(axis=channel_axis)(x)
	x = layers.Activation("relu")(x)
	model = training.Model(inputs, x)
	WEIGHTS_PATH = (
		"https://storage.googleapis.com/tensorflow/keras-applications/"
		"xception/xception_weights_tf_dim_ordering_tf_kernels_notop.h5")
	weights_path = data_utils.get_file(
		"xception_weights_tf_dim_ordering_tf_kernels_notop.h5",
		WEIGHTS_PATH,
		cache_subdir="models",
		file_hash="b0042744bf5b25fce3cb969f33bebb97")
	model.load_weights(weights_path)
	x = GlobalAveragePooling2D()(model.output)
	x = Dense(1024, activation='relu')(x)
	output = Dense(count_of_classes, activation='softmax')(x)
	return Model(inputs, outputs=output)
def train():
	train_datagen = ImageDataGenerator(
		rescale=1.0/255,
		rotation_range=30,
		width_shift_range=0.2,
		height_shift_range=0.2,
		shear_range=0.2,
		zoom_range=0.2,
		horizontal_flip=True,
		fill_mode='nearest')
	val_datagen = ImageDataGenerator(rescale=1.0/255)
	train_generator = train_datagen.flow_from_directory(
		train_path,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical')
	val_generator = val_datagen.flow_from_directory(
		val_path,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical')	
	with open("class_names.json", "w") as f:
		json.dump([class_names for class_names in train_generator.class_indices], f)
	model = xception_model(count_of_classes=len(train_generator.class_indices))
	model.compile(optimizer=Adam(learning_rate=learning_rate), loss='categorical_crossentropy', metrics=['accuracy'])
	start=datetime.now()
	history = model.fit(train_generator,
		epochs=count_of_epochs,
		validation_data=val_generator)		
	model_path = google_drive + 'Xception_Logo-2K_tensorflow_' + str(count_of_epochs)+'_epochs.keras'
	model.save(model_path)
	plt.plot(history.history['accuracy'], label='train accuracy')
	plt.plot(history.history['val_accuracy'], label='validation accuracy')
	plt.xlabel('Epochs')
	plt.ylabel('Accuracy')
	plt.legend()
	plt.savefig(google_drive + "train_history_tensorflow.jpg", dpi = 200)
	plt.close()
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of training: ",hours,":",minutes,":",seconds)
	print("The model was saved as ",model_path)
	print("The history was saved as ",google_drive + "train_history_tensorflow.jpg")
def evaluate(model_path):
	print(end="Model evaluation...",flush=True)
	start=datetime.now()	
	test_datagen = ImageDataGenerator(rescale=1.0/255)
	test_generator = test_datagen.flow_from_directory(
		test_path,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='sparse',
		shuffle=False)
	model = tf.keras.models.load_model(google_drive + model_path, compile=False)
	model.compile(
		optimizer=tf.keras.optimizers.Adam(1e-4),
		loss='sparse_categorical_crossentropy',
		metrics=['accuracy'])
	test_loss, test_acc = model.evaluate(test_generator, verbose=False)
	true_labels = test_generator.classes
	class_names = list(test_generator.class_indices.keys())
	predictions = model.predict(test_generator, verbose=False)
	predicted_labels = np.argmax(predictions, axis=1)
	conf_matrix = confusion_matrix(true_labels, predicted_labels)
	class_accuracies = conf_matrix.diagonal() / conf_matrix.sum(axis=1)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	print("Total accuracy over the test set: ",f"{test_acc * 100:.4f}%")
	for i, class_name in enumerate(class_names):
		print(end="accuracy over the class ")
		print(': {: <{}}'.format(class_name,21),end="",sep='')
		print(f": {class_accuracies[i] * 100:.2f}%")
def preprocess_frame(frame):
	frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
	frame = cv2.resize(frame, (image_size, image_size))
	frame = frame / 255.0
	frame = np.expand_dims(frame, axis=0)
	return frame
def detect_logos_in_video(video_path, model_path, threshold=0.6):
	cap = cv2.VideoCapture(video_path)
	fps = cap.get(cv2.CAP_PROP_FPS)
	detected_times = []
	with open("class_names.json", "r") as f:
		classes = json.load(f)
	frame_number = 0
	model = tf.keras.models.load_model(model_path)
	predictions = []
	while cap.isOpened():
		ret, frame = cap.read()
		if not ret:
			break
		# cv2.imwrite(f"debug/frame_{frame_number}.jpg", frame)
		# if frame_number % int(fps) == 0:
		frame = preprocess_frame(frame)
		prediction = model.predict(frame, verbose = False)
		probabilities = prediction[0]
		sorted_indices = np.argsort(probabilities)[::-1]
		predicted_class_index = np.argmax(prediction, axis=1)[0]
		confidence = prediction[0][predicted_class_index]
		time_sec = frame_number / fps
		detected_times.append(time_sec)
		if classes[predicted_class_index]=="Apple":
			predictions.append(confidence)
			if confidence > threshold:
				print(f"LOGO DETECTED AT {time_sec:.2f}s (confidence: {confidence:.5f})")
		else:
			print(f"{time_sec:.2f}s (confidence: {confidence:.5f}); brand: ",classes[predicted_class_index])
		frame_number += 1
	cap.release()
	plt.plot(predictions)
	plt.xlabel('Time')
	plt.ylabel('Accuracy')
	plt.savefig(google_drive + "brand_predictions.jpg", dpi = 200)
	plt.close()