import os
import cv2
import numpy as np
from PIL import Image
import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader
from torchvision import datasets, transforms, models
import matplotlib.pyplot as plt
from datetime import datetime
from datetime import timedelta
count_of_epochs = 3
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
class InceptionModel:
	def __init__(self, count_of_classes):
		self.device = torch.device(device if torch.cuda.is_available() else 'cpu')
		print(" Using device: ",self.device,end="...")
		self.model = models.inception_v3(pretrained=True)
		self.model.aux_logits = False
		for param in self.model.parameters():
			param.requires_grad = False
		num_features = self.model.fc.in_features
		self.model.fc = nn.Sequential(
			nn.Linear(num_features, 1024),
			nn.ReLU(),
			nn.Dropout(0.5),
			nn.Linear(1024, count_of_classes))
		for param in self.model.fc.parameters():
			param.requires_grad = True		
		self.model.to(self.device)
		self.criterion = nn.CrossEntropyLoss()
		self.optimizer = optim.Adam(
			filter(lambda p: p.requires_grad, self.model.parameters()), 
			lr=learning_rate)
		self.scheduler = optim.lr_scheduler.ReduceLROnPlateau(
			self.optimizer, 
			mode='min', 
			patience=3, 
			factor=0.1)
def train():
	print(end="Preparing the model...")
	start=datetime.now()
	train_transforms = transforms.Compose([
		transforms.Resize((image_size, image_size)),
		transforms.RandomRotation(20),
		transforms.RandomHorizontalFlip(),
		transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2),
		transforms.ToTensor(),
		transforms.Normalize(
			mean=[0.485, 0.456, 0.406],
			std=[0.229, 0.224, 0.225])])
	val_transforms = transforms.Compose([
		transforms.Resize((image_size, image_size)),
		transforms.ToTensor(),
		transforms.Normalize(
			mean=[0.485, 0.456, 0.406],
			std=[0.229, 0.224, 0.225])])
	train_dataset = datasets.ImageFolder(train_path, transform=train_transforms)
	val_dataset = datasets.ImageFolder(val_path, transform=val_transforms)
	train_loader = DataLoader(
		train_dataset, 
		batch_size=batch_size, 
		shuffle=True,
		num_workers=4)		
	val_loader = DataLoader(
		val_dataset, 
		batch_size=batch_size, 
		shuffle=False,
		num_workers=4)	
	inception_model = InceptionModel(len(os.listdir(train_path)))	
	history = {
		'train_loss': [],
		'train_accuracy': [],
		'val_loss': [],
		'val_accuracy': []}
	best_val_accuracy = 0.0
	TotalTime=timedelta(hours=0,minutes=0,seconds=0)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	for epoch in range(count_of_epochs):
		start=datetime.now()
		print("Epoch ",epoch+1," / ",count_of_epochs,end="...",sep="",flush=True)
		inception_model.model.train()
		train_loss = 0.0
		train_correct = 0
		train_total = 0
		for inputs, labels in train_loader:
			inputs, labels = inputs.to(inception_model.device), labels.to(inception_model.device)
			inception_model.optimizer.zero_grad()
			outputs = inception_model.model(inputs)
			if isinstance(outputs, tuple):
				outputs = outputs[0]
			loss = inception_model.criterion(outputs, labels)
			loss.backward()
			inception_model.optimizer.step()
			train_loss += loss.item()
			_, predicted = torch.max(outputs.data, 1)
			train_total += labels.size(0)
			train_correct += (predicted == labels).sum().item()
		inception_model.model.eval()
		val_loss = 0.0
		val_correct = 0
		val_total = 0
		with torch.no_grad():
			for inputs, labels in val_loader:
				inputs, labels = inputs.to(inception_model.device), labels.to(inception_model.device)
				outputs = inception_model.model(inputs)
				if isinstance(outputs, tuple):
					outputs = outputs[0]						
				loss = inception_model.criterion(outputs, labels)					
				val_loss += loss.item()
				_, predicted = torch.max(outputs.data, 1)
				val_total += labels.size(0)
				val_correct += (predicted == labels).sum().item()
		train_epoch_loss = train_loss / len(train_loader)
		train_epoch_accuracy = 100 * train_correct / train_total
		val_epoch_loss = val_loss / len(val_loader)
		val_epoch_accuracy = 100 * val_correct / val_total
		inception_model.scheduler.step(val_epoch_loss)
		if val_epoch_accuracy > best_val_accuracy:
			best_val_accuracy = val_epoch_accuracy
			torch.save(inception_model.model.state_dict(),
			google_drive + 'inception_Cats67_pytorch_' + str(epoch+1)+'_epochs.pth')
		history['train_loss'].append(train_epoch_loss)
		history['train_accuracy'].append(train_epoch_accuracy)
		history['val_loss'].append(val_epoch_loss)
		history['val_accuracy'].append(val_epoch_accuracy)		
		# print(f'Epoch {epoch+1}/{count_of_epochs}')
		# print(f'Train Loss: {train_epoch_loss:.4f}, Train Accuracy: {train_epoch_accuracy:.2f}%')
		# print(f'Val Loss: {val_epoch_loss:.4f}, Val Accuracy: {val_epoch_accuracy:.2f}%')
		# print('-' * 50)
		duration=datetime.now()-start
		TotalTime+=duration
		hours,minutes,seconds=ConvertTimeDelta(duration)		
		print(" Time: ",hours,":",minutes,":",seconds)
		print("Training accuracy: ",f'{train_epoch_accuracy:.4f}',sep='',end="; ")		
		print("testing accuracy: ",f'{val_epoch_accuracy:.4f}',sep='')
		print("Training loss	: ",f'{train_epoch_loss:.4f}',sep='',end="; ")
		print("testing loss	: ",f'{val_epoch_loss:.4f}',sep='')
		print('-' * 90)
	plt.rcParams['font.size'] = '18'
	fig,ax=plt.subplots(ncols=2, figsize=(16, 8))
	ax[0].set_xlabel('Epochs')
	ax[0].set_ylabel('Accuracy')
	ax[0].plot(np.arange(count_of_epochs),[i for i in history['train_accuracy']])
	ax[0].plot(np.arange(count_of_epochs),[i for i in history['val_accuracy']])
	ax[0].legend(bbox_to_anchor = (0.3,1.17),loc = 'upper right',labels=['Train accuracy','Validation accuracy'])	
	ax[1].set_xlabel('Epochs')
	ax[1].set_ylabel('Loss')
	ax[1].plot(np.arange(count_of_epochs),[i for i in history['train_loss']])
	ax[1].plot(np.arange(count_of_epochs),[i for i in history['val_loss']])
	ax[1].legend(bbox_to_anchor = (1.3,1.17),loc = 'upper right',labels=['Train loss','Validation loss'])	
	plt.savefig(google_drive + "train_history_pytorch.jpg", dpi = 200)
	plt.close()
	hours,minutes,seconds=ConvertTimeDelta(TotalTime)
	print("Total time of training: ",hours,":",minutes,":",seconds)
def evaluate_model(model_path):
	print(end="Model evaluation...",flush=True)
	start=datetime.now()
	test_transforms = transforms.Compose([
		transforms.Resize((image_size, image_size)),
		transforms.ToTensor(),
		transforms.Normalize(
			mean=[0.485, 0.456, 0.406],
			std=[0.229, 0.224, 0.225])])		
	test_dataset = datasets.ImageFolder(test_path, transform=test_transforms)
	test_loader = DataLoader(
		test_dataset, 
		batch_size=batch_size, 
		shuffle=False,
		num_workers=4)
	correct = 0
	total = 0		
	all_predictions = []
	all_labels = []
	inception_model = InceptionModel(len(test_loader.dataset.classes))
	inception_model.model.load_state_dict(torch.load(google_drive + model_path))
	inception_model.model.eval()
	count_of_classes = len(test_loader.dataset.classes)
	correct = 0
	total = 0
	class_correct = [0] * count_of_classes
	class_total = [0] * count_of_classes	
	with torch.no_grad():
		for images, labels in test_loader:
			images, labels = images.to(inception_model.device), labels.to(inception_model.device)
			outputs = inception_model.model(images)
			_, predicted = torch.max(outputs, 1)
			total += labels.size(0)
			correct += (predicted == labels).sum().item()
			for i in range(len(labels)):
				label = labels[i].item()
				class_correct[label] += (predicted[i] == label).item()
				class_total[label] += 1
	accuracy = 100 * correct / total
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	print("Total accuracy over the test set: ",f"{accuracy:.4f}%")	
	for i in range(count_of_classes):
		if class_total[i] > 0:
			class_acc = 100 * class_correct[i] / class_total[i]
			print(end="accuracy over the class ")
			class_name=test_loader.dataset.classes[i]
			print('{: <{}}'.format(class_name,37),end="",sep='')
			print(f": {class_acc:.4f}%")
def predict_image(inception_model, image_tensor, classes):
	inception_model.model.eval()
	with torch.no_grad():
		image_tensor = image_tensor.unsqueeze(0).to(inception_model.device)  # Додаємо розмірність batch
		outputs = inception_model.model(image_tensor)
		probabilities = F.softmax(outputs, dim=1)
		top_prob, top_class = torch.topk(probabilities, 5, dim=1)
		result = {
			"top_classes": [classes[class_idx.item()] for class_idx in top_class[0]],
			"top_probs": [prob.item() for prob in top_prob[0]]}
		probability = result["top_probs"][0]*100
		return result["top_classes"][0]+": "+str(f": {probability:.4f}%")
def predict(model_path):
	print(end="Making predictions...")
	image_paths = os.listdir('my_cats')
	classes = os.listdir(train_path)
	inception_model = InceptionModel(len(classes))
	inception_model.model.load_state_dict(torch.load(google_drive + model_path))
	transform = transforms.Compose([
		transforms.Resize((image_size, image_size)),
		transforms.ToTensor(),
		transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])])
	predictions = []
	for i in range(len(image_paths)):
		image = Image.open("my_cats\\" + image_paths[i]).convert('RGB')
		image_tensor = transform(image)
		predictions.append(predict_image(inception_model, image_tensor, classes))
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
	plt.savefig(google_drive + "CNN_Inception_pytorch_prediction.jpg", dpi = 200)
	plt.close()
	print("\nPredictions were saved as CNN_Inception_pytorch_prediction.jpg")