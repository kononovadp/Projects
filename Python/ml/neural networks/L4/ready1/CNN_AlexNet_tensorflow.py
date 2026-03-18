import os
import shutil
import random
import tensorflow as tf
from tensorflow.keras import layers, models
from tensorflow.keras.preprocessing import image
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import numpy as np
from sklearn.utils import class_weight
from tensorflow.keras.callbacks import EarlyStopping, LearningRateScheduler
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.models import load_model
import matplotlib.pyplot as plt
from datetime import datetime
from datetime import timedelta
batch_size = 64
learning_rate = 0.0001
image_size = 227
dataset_path = 'animals10_dataset\\raw-img'
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '1'
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def lr_schedule(epoch, lr):
    if epoch > 10:
        lr = lr * 0.5
    return lr
def	train():
	start=datetime.now()
	train_dir = 'Animals10_train'
	test_dir = 'Animals10_test'	
	if(os.path.isdir(train_dir)):
		print("Removing the folder ", train_dir, end="...", flush=True)
		shutil.rmtree(train_dir)
		print(" Done.")
	if(os.path.isdir(test_dir)):	
		print("Removing the folder ", test_dir, end="...", flush=True)
		shutil.rmtree(test_dir)		
		print(" Done.")
	print("Preparing dataset and model...",flush=True,end="")
	os.makedirs(train_dir, exist_ok=True)
	os.makedirs(test_dir, exist_ok=True)
	test_size = 0.2
	class_names = os.listdir(dataset_path)
	for class_name in class_names:
		class_source = os.path.join(dataset_path, class_name)
		if os.path.isdir(class_source):
			image_files = [f for f in os.listdir(class_source)
						   if os.path.isfile(os.path.join(class_source, f))]
			train_files, test_files = train_test_split(image_files, test_size=test_size, random_state=42)
			class_train_dir = os.path.join(train_dir, class_name)
			class_test_dir = os.path.join(test_dir, class_name)
			os.makedirs(class_train_dir, exist_ok=True)
			os.makedirs(class_test_dir, exist_ok=True)
			for file_name in train_files:
				src_file = os.path.join(class_source, file_name)
				dst_file = os.path.join(class_train_dir, file_name)
				shutil.copy2(src_file, dst_file)        
			for file_name in test_files:
				src_file = os.path.join(class_source, file_name)
				dst_file = os.path.join(class_test_dir, file_name)
				shutil.copy2(src_file, dst_file)
	model = models.Sequential([
		layers.Conv2D(96, (11, 11), strides=4, activation='relu', input_shape=(image_size, image_size, 3)),
		layers.MaxPooling2D((3, 3), strides=2),
		layers.Conv2D(256, (5, 5), padding='same', activation='relu'),
		layers.MaxPooling2D((3, 3), strides=2),
		layers.Conv2D(384, (3, 3), padding='same', activation='relu'),
		layers.Conv2D(384, (3, 3), padding='same', activation='relu'),
		layers.Conv2D(256, (3, 3), padding='same', activation='relu'),
		layers.MaxPooling2D((3, 3), strides=2),
		layers.Flatten(),
		layers.Dense(4096, activation='relu'),
		layers.Dropout(0.5),
		layers.Dense(4096, activation='relu'),
		layers.Dropout(0.5),
		layers.Dense(len(class_names), activation='softmax')])
	train_datagen = ImageDataGenerator(
		rescale=1./255,
		rotation_range=40,
		width_shift_range=0.2,
		height_shift_range=0.2,
		shear_range=0.2,
		zoom_range=0.2,
		horizontal_flip=True,
		fill_mode='nearest')
	test_datagen = ImageDataGenerator(rescale=1./255)
	train_generator = train_datagen.flow_from_directory(
		train_dir,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical')
	test_generator = test_datagen.flow_from_directory(
		test_dir,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical',
		shuffle=False)
	class_labels = train_generator.classes
	class_weights = class_weight.compute_class_weight(
		'balanced', 
		classes=np.unique(class_labels), 
		y=class_labels)
	class_weight_dict = dict(zip(np.unique(class_labels), class_weights))
	early_stopping = EarlyStopping(monitor='val_loss', patience=5, restore_best_weights=True)
	optimizer = Adam(learning_rate=learning_rate)
	model.compile(
		loss='categorical_crossentropy',
		optimizer=optimizer,
		metrics=['accuracy'])
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	from main import count_of_epochs
	from main import tensorflow_model_path as model_path
	print("Time of data preparations: ",hours,":",minutes,":",seconds)
	start=datetime.now()
	lr_scheduler = LearningRateScheduler(lr_schedule)
	history = model.fit(
		train_generator,
		epochs=count_of_epochs,
		validation_data=test_generator,
		class_weight=class_weight_dict,
		callbacks=[early_stopping, lr_scheduler])
	if(os.path.isdir(model_path)):	
		print("Removing the existing model folder ", model_path, end="...", flush=True)
		shutil.rmtree(model_path)		
		print(" Done.")
	model.save(model_path)
	plt.plot(history.history['accuracy'], label='train accuracy')
	plt.plot(history.history['val_accuracy'], label='validation accuracy')
	plt.xlabel('Epochs')
	plt.ylabel('Accuracy')
	plt.legend()
	plt.savefig("train_history_tensorflow.jpg", dpi = 200)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of training: ",hours,":",minutes,":",seconds)
	print("The history was saved into the file train_history_tensorflow.jpg")
########################################PREDICTION########################################
def get_random_image(dataset):
    class_folders = [f for f in os.listdir(dataset_path) if os.path.isdir(os.path.join(dataset_path, f))]
    random_class_folder = random.choice(class_folders)
    class_folder_path = os.path.join(dataset_path, random_class_folder)
    all_files = os.listdir(class_folder_path)
    image_files = [f for f in all_files if f.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif'))]
    if not image_files:
        raise ValueError(f"No images found in the class folder: {random_class_folder}.")
    random_image = random.choice(image_files)
    return os.path.join(class_folder_path, random_image), random_class_folder
def evaluate_model(model_path):	
	start=datetime.now()
	test_datagen = ImageDataGenerator(rescale=1.0/255)
	test_generator = test_datagen.flow_from_directory(
		"Animals10_test",
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical',
		shuffle=False)
	print(end="Model evaluation...",flush=True)	
	model = load_model(model_path)
	test_loss, test_acc = model.evaluate(test_generator, verbose=False)
	true_labels = test_generator.classes
	class_names = list(test_generator.class_indices.keys())
	predictions = model.predict(test_generator, verbose=False)
	predicted_labels = np.argmax(predictions, axis=1)
	conf_matrix = confusion_matrix(true_labels, predicted_labels)
	class_accuracies = conf_matrix.diagonal() / conf_matrix.sum(axis=1)
	from main import dictionary
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	print("Total accuracy over the test set: ",f"{test_acc * 100:.4f}%")
	for i, class_name in enumerate(class_names):
		print(end="accuracy over the class ")
		if(class_name in dictionary):
			class_name+=" ("+dictionary[class_name]+")"
		print(': {: <{}}'.format(class_name,21),end="",sep='')
		print(f": {class_accuracies[i] * 100:.2f}%")		
def predict(model_path):	
	dataset = {}
	class_names = os.listdir(dataset_path)
	for class_name in class_names:
		class_folder = os.path.join(dataset_path, class_name)
		if not os.path.isdir(class_folder):
			continue
		image_files = [os.path.join(class_folder, img) for img in os.listdir(class_folder) 
					   if img.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif'))]
		dataset[class_name] = image_files	
	model = load_model(model_path)
	image_path, original_class = get_random_image(dataset)
	img = image.load_img(image_path, target_size=(image_size, image_size))
	img_array = image.img_to_array(img)
	img_array = np.expand_dims(img_array, axis=0)
	img_array /= 255.0
	predictions = model.predict(img_array, verbose = False)
	probabilities = predictions[0]
	sorted_indices = np.argsort(probabilities)[::-1]
	predicted_class_index = np.argmax(predictions, axis=1)[0]
	confidence = predictions[0][predicted_class_index]
	predicted_class = class_names[predicted_class_index]
	from main import dictionary
	title = "Prediction: "+predicted_class
	if(predicted_class in dictionary):
		title += " ("+dictionary[predicted_class]+")"
	title += "; original class: " + original_class
	if(original_class in dictionary):
		title += " ("+dictionary[original_class]+")"
	title += '\n'
	for j, i in enumerate(sorted_indices):
		title+=str(j+1)+". "+class_names[i]
		if(class_names[i] in dictionary):
			title+=" ("+str(dictionary[class_names[i]])+")"
		title+=f": {probabilities[i]*100:.4f}%\n"	
	plt.figure(figsize=(10, 6))
	plt.subplot(1, 1, 1)
	plt.imshow(img)
	plt.title(title)
	plt.axis('off')
	plt.tight_layout()
	plt.savefig('CNN_AlexNet_tensorflow_prediction_result.jpg')
	print("Results of prediction for the image\n"+image_path+":")
	print("Predicted class: ",end=predicted_class)
	if(predicted_class in dictionary):
		print(" ("+dictionary[predicted_class],end=")")
	print("; original class: ",end=original_class)
	if(original_class in dictionary):
		print(" ("+dictionary[original_class]+")")
	for j, i in enumerate(sorted_indices):
		output=str(j+1)+". "+class_names[i]
		if(class_names[i] in dictionary):
			output+=" ("+str(dictionary[class_names[i]])+")"
		print('{: <{}}'.format(output,24),end="",sep='')
		print(f": {probabilities[i]*100:.4f}%")
	print("The prediction was saved as CNN_AlexNet_tensorflow_prediction_result.jpg")