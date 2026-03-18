import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import cv2
import zipfile
import shutil
import random
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications import InceptionV3
from tensorflow.keras.layers import Dense, GlobalAveragePooling2D
from tensorflow.keras.models import Model
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing import image
import matplotlib.pyplot as plt
from tensorflow.keras.models import load_model
from datetime import datetime
count_of_epochs = 1
batch_size = 32
learning_rate = 0.0001
image_size = 299
dagshub = ''
google_drive = ''
train_path = dagshub + 'Cats67_train'
val_path = dagshub + 'Cats67_val'
test_path = dagshub + 'Cats67_test'
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def train():	
	print("Preparing the model...",flush=True,end="")
	start=datetime.now()
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
	base_model = InceptionV3(weights='imagenet', include_top=False)
	x = base_model.output
	x = GlobalAveragePooling2D()(x)
	x = Dense(1024, activation='relu')(x)
	predictions = Dense(len(train_generator.class_indices), activation='softmax')(x)
	model = Model(inputs=base_model.input, outputs=predictions)
	for layer in base_model.layers:
		layer.trainable = False
	model.compile(optimizer=Adam(learning_rate=learning_rate), loss='categorical_crossentropy', metrics=['accuracy'])
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of model preparations: ",hours,":",minutes,":",seconds)
	start=datetime.now()
	history = model.fit(train_generator,
		epochs=count_of_epochs,
		validation_data=val_generator)
	model_path = google_drive + 'inception_Cats67_tensorflow_' + str(count_of_epochs)+'_epochs.keras'
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
def evaluate_model(model_path):
	print(end="Model evaluation...",flush=True)
	start=datetime.now()	
	test_datagen = ImageDataGenerator(rescale=1.0/255)
	test_generator = test_datagen.flow_from_directory(
		test_path,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical',
		shuffle=False)
	model = tf.keras.models.load_model(google_drive + model_path, compile=False)
	model.compile(
		optimizer='adam',
		loss='categorical_crossentropy',
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
def predict(model_path):	
	print(end="Making predictions...")
	model = tf.keras.models.load_model(google_drive + model_path, compile=False)
	model.compile(
		optimizer='adam',
		loss='categorical_crossentropy',
		metrics=['accuracy'])
	image_paths = os.listdir('my_cats')
	classes = os.listdir(train_path)
	predictions = []
	for i in range(len(image_paths)):
		img = image.load_img("my_cats\\"+image_paths[i], target_size=(image_size, image_size))
		img_array = image.img_to_array(img)
		img_array = np.expand_dims(img_array, axis=0)
		img_array /= 255.0
		prediction = model.predict(img_array, verbose = False)
		probabilities = prediction[0]
		sorted_indices = np.argsort(probabilities)[::-1]
		predicted_class_index = np.argmax(prediction, axis=1)[0]
		predictions.append(classes[predicted_class_index]+": "+str(f": {prediction[0][predicted_class_index]*100:.4f}%"))
	columns = 2
	rows = (len(image_paths) + columns - 1) // columns
	fig, axes = plt.subplots(rows, columns, figsize=(16, 12))
	axes = axes.flatten()
	for i, (img_path, pred) in enumerate(zip(image_paths, predictions)):
		img = cv2.imread("my_cats\\" + img_path)
		img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
		axes[i].imshow(img)
		axes[i].set_title(f"{pred}", fontsize=10)
		axes[i].axis("off")
	for j in range(i + 1, len(axes)):
		fig.delaxes(axes[j])
	plt.tight_layout(pad=2.0)
	plt.savefig(google_drive + "CNN_Inception_tensorflow_prediction.jpg", dpi = 200)
	plt.close()
	print(" Predictions were saved as CNN_Inception_tensorflow_prediction.jpg")