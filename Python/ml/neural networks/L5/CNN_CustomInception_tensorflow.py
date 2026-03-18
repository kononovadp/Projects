import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import tensorflow as tf
tf.get_logger().setLevel('ERROR')
from tensorflow import keras
from tensorflow.keras import layers
import numpy as np
import matplotlib.pyplot as plt
import requests
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
from tensorflow.keras.preprocessing import image
from tensorflow.keras.preprocessing.image import ImageDataGenerator
import pandas as pd
from PIL import Image
import glob
import cv2
from datetime import datetime
count_of_epochs = 5
batch_size = 32
learning_rate = 0.0001
image_size = 224
dagshub = ''
google_drive = ''
train_path = dagshub + 'Cats67_train'
val_path = dagshub + 'Cats67_val'
test_path = dagshub + 'Cats67_test'
tf.random.set_seed(42)
np.random.seed(42)
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
class InceptionBlock(layers.Layer):
    """Custom Inception Block implementation"""
    
    def __init__(self, filters_1x1, filters_3x3_reduce, filters_3x3, 
                 filters_5x5_reduce, filters_5x5, filters_pool_proj, **kwargs):
        super(InceptionBlock, self).__init__(**kwargs)
        
        # Store filter parameters for serialization
        self.filters_1x1 = filters_1x1
        self.filters_3x3_reduce = filters_3x3_reduce
        self.filters_3x3 = filters_3x3
        self.filters_5x5_reduce = filters_5x5_reduce
        self.filters_5x5 = filters_5x5
        self.filters_pool_proj = filters_pool_proj
        
        # 1x1 convolution branch
        self.conv_1x1 = layers.Conv2D(filters_1x1, (1, 1), padding='same', activation='relu')
        
        # 3x3 convolution branch
        self.conv_3x3_reduce = layers.Conv2D(filters_3x3_reduce, (1, 1), padding='same', activation='relu')
        self.conv_3x3 = layers.Conv2D(filters_3x3, (3, 3), padding='same', activation='relu')
        
        # 5x5 convolution branch
        self.conv_5x5_reduce = layers.Conv2D(filters_5x5_reduce, (1, 1), padding='same', activation='relu')
        self.conv_5x5 = layers.Conv2D(filters_5x5, (5, 5), padding='same', activation='relu')
        
        # Max pooling branch
        self.maxpool = layers.MaxPooling2D((3, 3), strides=1, padding='same')
        self.conv_pool_proj = layers.Conv2D(filters_pool_proj, (1, 1), padding='same', activation='relu')
        
        self.concat = layers.Concatenate(axis=-1)
    
    def get_config(self):
        config = super().get_config()
        config.update({
            'filters_1x1': self.filters_1x1,
            'filters_3x3_reduce': self.filters_3x3_reduce,
            'filters_3x3': self.filters_3x3,
            'filters_5x5_reduce': self.filters_5x5_reduce,
            'filters_5x5': self.filters_5x5,
            'filters_pool_proj': self.filters_pool_proj,
        })
        return config
    
    @classmethod
    def from_config(cls, config):
        return cls(**config)
        
    def call(self, inputs):
        # 1x1 branch
        branch_1x1 = self.conv_1x1(inputs)
        
        # 3x3 branch
        branch_3x3 = self.conv_3x3_reduce(inputs)
        branch_3x3 = self.conv_3x3(branch_3x3)
        
        # 5x5 branch  
        branch_5x5 = self.conv_5x5_reduce(inputs)
        branch_5x5 = self.conv_5x5(branch_5x5)
        
        # Pooling branch
        branch_pool = self.maxpool(inputs)
        branch_pool = self.conv_pool_proj(branch_pool)
        
        # Concatenate all branches
        return self.concat([branch_1x1, branch_3x3, branch_5x5, branch_pool])

def create_inception_model(input_shape, num_classes):
    """Create custom Inception model for cat breed classification"""
    
    inputs = keras.Input(shape=input_shape)
    
    # Initial convolution layers
    x = layers.Conv2D(64, (7, 7), strides=2, padding='same', activation='relu')(inputs)
    x = layers.MaxPooling2D((3, 3), strides=2, padding='same')(x)
    x = layers.BatchNormalization()(x)
    
    x = layers.Conv2D(64, (1, 1), padding='same', activation='relu')(x)
    x = layers.Conv2D(192, (3, 3), padding='same', activation='relu')(x)
    x = layers.MaxPooling2D((3, 3), strides=2, padding='same')(x)
    x = layers.BatchNormalization()(x)
    
    # Inception blocks
    x = InceptionBlock(64, 96, 128, 16, 32, 32)(x)
    x = InceptionBlock(128, 128, 192, 32, 96, 64)(x)
    x = layers.MaxPooling2D((3, 3), strides=2, padding='same')(x)
    
    x = InceptionBlock(192, 96, 208, 16, 48, 64)(x)
    x = InceptionBlock(160, 112, 224, 24, 64, 64)(x)
    x = InceptionBlock(128, 128, 256, 24, 64, 64)(x)
    x = InceptionBlock(112, 144, 288, 32, 64, 64)(x)
    x = InceptionBlock(256, 160, 320, 32, 128, 128)(x)
    x = layers.MaxPooling2D((3, 3), strides=2, padding='same')(x)
    
    x = InceptionBlock(256, 160, 320, 32, 128, 128)(x)
    x = InceptionBlock(384, 192, 384, 48, 128, 128)(x)
    
    # Global average pooling and classification head
    x = layers.GlobalAveragePooling2D()(x)
    x = layers.Dropout(0.4)(x)
    x = layers.Dense(1024, activation='relu')(x)
    x = layers.Dropout(0.5)(x)
    outputs = layers.Dense(num_classes, activation='softmax')(x)
    
    model = keras.Model(inputs, outputs, name='custom_inception')
    return model
def load_and_preprocess_data():
	train_datagen = ImageDataGenerator(
		rescale=1./255,
		rotation_range=20,
		width_shift_range=0.2,
		height_shift_range=0.2,
		horizontal_flip=True,
		zoom_range=0.2,
		validation_split=0.2)    
	train_generator = train_datagen.flow_from_directory(
		train_path,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical',
		subset='training')    
	validation_generator = train_datagen.flow_from_directory(
		val_path,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical',
		subset='validation')    
	num_classes = len(train_generator.class_indices)    
	return train_generator, validation_generator, num_classes
def train():	
	print("Preparing the model...",flush=True,end="")
	start=datetime.now()
	train_gen, val_gen, num_classes = load_and_preprocess_data()
	model = create_inception_model((224, 224, 3), num_classes)
	model.compile(
		optimizer=keras.optimizers.Adam(learning_rate=learning_rate),
		loss='categorical_crossentropy',
		metrics=['accuracy', keras.metrics.TopKCategoricalAccuracy(k=3)])
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of model preparations: ",hours,":",minutes,":",seconds)
	start=datetime.now()
	history = model.fit(
		train_gen,
		epochs=count_of_epochs,
		validation_data=val_gen,
		verbose=2)
	model_path = google_drive + 'custom_inception_Cats67_tensorflow_' + str(count_of_epochs)+'_epochs.keras'
	model.save(model_path)
	plt.plot(history.history['accuracy'], label='train accuracy')
	plt.plot(history.history['val_accuracy'], label='validation accuracy')
	plt.xlabel('Epochs')
	plt.ylabel('Accuracy')
	plt.legend()
	plt.savefig(google_drive + "train_history_tensorflow_custom_model.jpg", dpi = 200)
	plt.close()
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("Time of training: ",hours,":",minutes,":",seconds)
	print("The model was saved as ",model_path)
	print("The history was saved as ",google_drive + "train_history_tensorflow_custom_model.jpg")
def evaluate_model(model_path):
	print(end="Model evaluation...",flush=True)
	start=datetime.now()	
	test_datagen = ImageDataGenerator(rescale=1.0/255)
	test_data = test_datagen.flow_from_directory(
		test_path,
		target_size=(image_size, image_size),
		batch_size=batch_size,
		class_mode='categorical',
		shuffle=False)
	custom_objects = {
        'InceptionBlock': InceptionBlock,
        'TopKCategoricalAccuracy': keras.metrics.TopKCategoricalAccuracy}
	model = tf.keras.models.load_model(google_drive + model_path, custom_objects=custom_objects, compile=False)
	model.compile(
		optimizer=keras.optimizers.Adam(learning_rate=learning_rate),
		loss='categorical_crossentropy',
		metrics=['accuracy', keras.metrics.TopKCategoricalAccuracy(k=3)])
	y_true_classes = []
	y_pred_classes = []
	y_pred = []
	class_names = list(test_data.class_indices.keys())
	for i in range(len(test_data)):
		batch_x, batch_y = test_data[i]
		batch_pred = model.predict(batch_x, verbose=0)		
		y_true_classes.extend(np.argmax(batch_y, axis=1))
		y_pred_classes.extend(np.argmax(batch_pred, axis=1))
		y_pred.extend(batch_pred)	
	y_true_classes = np.array(y_true_classes)
	y_pred_classes = np.array(y_pred_classes)
	y_pred = np.array(y_pred)
	overall_accuracy = accuracy_score(y_true_classes, y_pred_classes)	
	report = classification_report(
		y_true_classes, 
		y_pred_classes, 
		target_names=class_names,
		output_dict=True,
		zero_division=0)
	report_df = pd.DataFrame(report).transpose()
	print("CLASSIFICATION REPORT:\n",report_df.round(4).to_string())
	print("PER-CLASS ACCURACY BREAKDOWN:")
	per_class_accuracy = {}
	for i, class_name in enumerate(class_names):
		class_mask = (y_true_classes == i)
		if np.sum(class_mask) > 0:
			class_correct = np.sum((y_true_classes == i) & (y_pred_classes == i))
			class_total = np.sum(class_mask)
			class_accuracy = class_correct / class_total
			per_class_accuracy[class_name] = class_accuracy			
			print(f"{class_name:20s}: {class_accuracy:.4f} ({class_correct}/{class_total})")
		else:
			per_class_accuracy[class_name] = 0.0
			print(f"{class_name:20s}: No samples")
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print("OVERALL ACCURACY: ",f"{overall_accuracy:.4f}")
	print("Time: ",hours,":",minutes,":",seconds)
def predict(model_path):	
	print(end="Making predictions...")
	custom_objects = {
        'InceptionBlock': InceptionBlock,
        'TopKCategoricalAccuracy': keras.metrics.TopKCategoricalAccuracy}
	model = tf.keras.models.load_model(google_drive + model_path, custom_objects=custom_objects, compile=False)
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
		axes[i].set_title(f"{pred}", fontsize=20)
		axes[i].axis("off")
	for j in range(i + 1, len(axes)):
		fig.delaxes(axes[j])
	plt.tight_layout(pad=2.0)
	plt.savefig(google_drive + "CNN_Inception_tensorflow_custom_model_prediction.jpg", dpi = 200)
	plt.close()
	print("\nPredictions were saved as CNN_Inception_tensorflow_custom_model_prediction.jpg")