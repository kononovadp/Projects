import os
import zipfile
import importlib.util
from datetime import datetime
import CNN_AlexNet_pytorch
import CNN_AlexNet_tensorflow
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
zip_path = 'animals10.zip'
dataset_path = 'animals10_dataset'
count_of_epochs = 1
pytorch_model_path = 'alexnet_animals10_pytorch_' + str(count_of_epochs)+'_epochs.pth'
tensorflow_model_path = 'alexnet_animals10_tensorflow_' + str(count_of_epochs)+'_epochs'
if not os.path.exists(dataset_path) or len(os.listdir(dataset_path)) == 0:		
	print(end = "Dataset extraction...", flush = True)
	start=datetime.now()
	if not os.path.exists(dataset_path):
		os.makedirs(dataset_path)
	with zipfile.ZipFile(zip_path, 'r') as zip_ref:
		zip_ref.extractall(dataset_path)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)		
	print(" Time: ",hours,":",minutes,":",seconds)
# from animals10_dataset.translate import translate
translate_file_path = os.path.join(dataset_path, 'translate.py')
spec = importlib.util.spec_from_file_location("translate", translate_file_path)
translate_module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(translate_module)
dictionary = translate_module.translate
def main():
	print("----------AlexNet PYTORCH convolutional neural network----------")
	CNN_AlexNet_pytorch.train()
	CNN_AlexNet_pytorch.evaluate_model(pytorch_model_path)
	CNN_AlexNet_pytorch.predict(pytorch_model_path)
	print("----------AlexNet TENSORFLOW convolutional neural network----------")
	CNN_AlexNet_tensorflow.train()
	CNN_AlexNet_tensorflow.evaluate_model(tensorflow_model_path)
	CNN_AlexNet_tensorflow.predict(tensorflow_model_path)
if __name__ == "__main__":
	main()