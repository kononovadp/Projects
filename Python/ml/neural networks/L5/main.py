import os
import zipfile
import importlib.util
from datetime import datetime
# import CNN_Inception_pytorch
# import CNN_Inception_tensorflow
import CNN_CustomInception_tensorflow
zip_path = 'Cats67Dataset.zip' #https://www.kaggle.com/datasets/ma7555/cat-breeds-dataset
dataset_path = 'Cats67Dataset'
data_storage = ''
train_path = data_storage + 'Cats67_train'
val_path = data_storage + 'Cats67_val'
test_path = data_storage + 'Cats67_test'
# dagshub upload --bucket maksymkononov11/lab5 "D:\\Desktop\\L5\Cats67_test"
# dagshub upload --bucket maksymkononov11/lab5 "D:\\Desktop\\L5\Cats67_val"
# dagshub upload --bucket maksymkononov11/lab5 "D:\\Desktop\\L5\Cats67_train"
# dagshub upload --bucket maksymkononov11/lab8 "D:\\Desktop\\LJSpeech-1.1"
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def check_images(root_dir):
	import cv2
	from PIL import Image
	for folder, _, files in os.walk(root_dir):  # Recursively go through all subfolders
		print("Folder: ",folder)
		for filename in files:
			filepath = os.path.join(folder, filename)
			img = cv2.imread(filepath, cv2.IMREAD_UNCHANGED)
			if img is None:
				print(filepath," is CORRUPTED (opencv)")
			try:
				with Image.open(filepath) as img:
					img.verify()
			except Exception as e:
				print(filepath," is CORRUPTED (Pillow)")
if not os.path.exists(dataset_path) or len(os.listdir(dataset_path)) == 0:		
	print(end = "Dataset extraction...", flush = True)
	start=datetime.now()
	os.makedirs(dataset_path)
	with zipfile.ZipFile(zip_path, 'r') as zip_ref:
		zip_ref.extractall(dataset_path)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)		
	print(" Time: ",hours,":",minutes,":",seconds)
if not os.path.exists(train_path) or not os.path.exists(val_path) or not os.path.exists(test_path):
	print("Preparing data for training, validation and testing...")
	start=datetime.now()
	dataset_path += '\\images'
	from dataset_splitter import split_dataset
	split_dataset(
		dataset_path,
		train_path,
		val_path,
		test_path,
		train_ratio=0.7,
		val_ratio=0.15,
		test_ratio=0.15)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)		
	print("Time: ",hours,":",minutes,":",seconds)
def main():
	# print("----------Inception PYTORCH convolutional neural network----------")
	# CNN_Inception_pytorch.train()
	# CNN_Inception_pytorch.evaluate_model('inception_Cats67_pytorch_3_epochs.pth')
	# CNN_Inception_pytorch.predict('inception_Cats67_pytorch_3_epochs.pth')
	# print("----------Inception TENSORFLOW convolutional neural network----------")
	# CNN_Inception_tensorflow.train()
	# CNN_Inception_tensorflow.evaluate_model('inception_Cats67_tensorflow_1_epochs.keras')
	# CNN_Inception_tensorflow.predict('inception_Cats67_tensorflow_1_epochs.keras')
	print("----------Custom inception TENSORFLOW convolutional neural network----------")
	# CNN_CustomInception_tensorflow.train()
	CNN_CustomInception_tensorflow.evaluate_model('custom_inception_Cats67_tensorflow_5_epochs.keras')
	# CNN_CustomInception_tensorflow.predict('custom_inception_Cats67_tensorflow_5_epochs.keras')
if __name__ == "__main__":
	main()