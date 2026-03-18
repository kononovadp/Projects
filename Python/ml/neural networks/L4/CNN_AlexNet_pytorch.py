import os
import random
import numpy as np
from PIL import Image
import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
from torchvision import transforms
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from datetime import datetime
from datetime import timedelta
from main import dictionary
batch_size = 64
learning_rate = 0.0001
image_size = 227
dataset_path = 'animals10_dataset'
torch_device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
class AlexNet(nn.Module):
	def __init__(self, count_of_classes):
		super(AlexNet, self).__init__()
		self.features = nn.Sequential(
			nn.Conv2d(3, 64, kernel_size=11, stride=4, padding=2),
			nn.ReLU(inplace=True),
			nn.MaxPool2d(kernel_size=3, stride=2),
			nn.Conv2d(64, 192, kernel_size=5, padding=2),
			nn.ReLU(inplace=True),
			nn.MaxPool2d(kernel_size=3, stride=2),
			nn.Conv2d(192, 384, kernel_size=3, padding=1),
			nn.ReLU(inplace=True),
			nn.Conv2d(384, 256, kernel_size=3, padding=1),
			nn.ReLU(inplace=True),
			nn.Conv2d(256, 256, kernel_size=3, padding=1),
			nn.ReLU(inplace=True),
			nn.MaxPool2d(kernel_size=3, stride=2))
		self.avgpool = nn.AdaptiveAvgPool2d((6, 6))
		self.classifier = nn.Sequential(
			nn.Dropout(),
			nn.Linear(256 * 6 * 6, 4096),
			nn.ReLU(inplace=True),
			nn.Dropout(),
			nn.Linear(4096, 4096),
			nn.ReLU(inplace=True),
			nn.Linear(4096, count_of_classes))
	def forward(self, x):
		x = self.features(x)
		x = self.avgpool(x)
		x = torch.flatten(x, 1)
		x = self.classifier(x)
		return x
class Animals10Dataset(Dataset):
	def __init__(self, root_dir, transform=None):
		self.root_dir = root_dir
		self.transform = transform
		self.classes = []
		self.class_to_idx = {}		
		self.images = []
		self.labels = []
		if not os.path.exists(root_dir):
			print("The path "+root_dir+" doesn't exist")
			exit()
		for item in os.listdir(root_dir):
			item_path = os.path.join(root_dir, item)
			if os.path.isdir(item_path):
				self.classes.append(item)
		if not self.classes:
			for item in os.listdir(root_dir):
				item_path = os.path.join(root_dir, item)
				if os.path.isdir(item_path):
					for subitem in os.listdir(item_path):
						subitem_path = os.path.join(item_path, subitem)
						if os.path.isdir(subitem_path):
							self.root_dir = item_path
							self.classes.append(subitem)		
		if not self.classes:
			print("There are no classes in the folder "+root_dir)
			exit()
		self.class_to_idx = {cls: i for i, cls in enumerate(self.classes)}
		for class_name in self.classes:
			class_dir = os.path.join(self.root_dir, class_name)
			class_idx = self.class_to_idx[class_name]			
			if os.path.isdir(class_dir):
				for img_name in os.listdir(class_dir):
					img_path = os.path.join(class_dir, img_name)
					if os.path.isfile(img_path) and img_name.lower().endswith(('.png', '.jpg', '.jpeg')):
						self.images.append(img_path)
						self.labels.append(class_idx)		
		if not self.images:
			print("There are no images in the folder "+root_dir)
			exit()
	def __len__(self):
		return len(self.images)	
	def __getitem__(self, index):
		img_path = self.images[index]
		label = self.labels[index]
		image = Image.open(img_path).convert('RGB')
		if self.transform:
			image = self.transform(image)
		return image, label	
def train_model(train_loader, val_loader):
	model = AlexNet(len(train_loader.dataset.dataset.classes))
	model.to(torch_device)
	best_val_acc = 0.0
	train_losses = []
	val_losses = []
	train_accs = []
	val_accs = []
	criterion = nn.CrossEntropyLoss()
	optimizer = optim.Adam(model.parameters(), lr=learning_rate)
	TotalTime=timedelta(hours=0,minutes=0,seconds=0)
	from main import count_of_epochs
	from main import pytorch_model_path as model_path
	for epoch in range(count_of_epochs):
		start=datetime.now()
		print("Epoch ",epoch+1," / ",count_of_epochs,end="...",sep="",flush=True)
		model.train()
		train_loss = 0.0
		train_correct = 0
		train_total = 0
		for images, labels in train_loader:
			images, labels = images.to(torch_device), labels.to(torch_device)			
			optimizer.zero_grad()
			outputs = model(images)
			loss = criterion(outputs, labels)
			loss.backward()
			optimizer.step()			
			train_loss += loss.item() * images.size(0)
			_, predicted = torch.max(outputs, 1)
			train_total += labels.size(0)
			train_correct += (predicted == labels).sum().item()
		epoch_train_loss = train_loss / len(train_loader.dataset)
		epoch_train_acc = train_correct / train_total
		train_losses.append(epoch_train_loss)
		train_accs.append(epoch_train_acc)
		model.eval()
		val_loss = 0.0
		val_correct = 0
		val_total = 0		
		with torch.no_grad():
			for images, labels in val_loader:
				images, labels = images.to(torch_device), labels.to(torch_device)
				outputs = model(images)
				loss = criterion(outputs, labels)				
				val_loss += loss.item() * images.size(0)
				_, predicted = torch.max(outputs, 1)
				val_total += labels.size(0)
				val_correct += (predicted == labels).sum().item()
		epoch_val_loss = val_loss / len(val_loader.dataset)
		epoch_val_acc = val_correct / val_total
		val_losses.append(epoch_val_loss)
		val_accs.append(epoch_val_acc)
		if epoch_val_acc > best_val_acc:
			best_val_acc = epoch_val_acc
			torch.save(model.state_dict(), model_path)
		duration=datetime.now()-start
		TotalTime+=duration
		hours,minutes,seconds=ConvertTimeDelta(duration)		
		print(" Time: ",hours,":",minutes,":",seconds)
		print("Training accuracy: ",f'{epoch_train_acc:.4f}',sep='',end="; ")		
		print("testing accuracy: ",f'{epoch_val_acc:.4f}',sep='')
		print("Training loss	: ",f'{epoch_train_loss:.4f}',sep='',end="; ")
		print("testing loss	: ",f'{epoch_val_loss:.4f}',sep='')
		print('-' * 90)
	hours,minutes,seconds=ConvertTimeDelta(TotalTime)
	print("Total time of training: ",hours,":",minutes,":",seconds)
	return train_losses, val_losses, train_accs, val_accs
def plot_results(train_losses, val_losses, train_accs, val_accs):
	from main import count_of_epochs
	plt.rcParams['font.size'] = '18'
	fig,ax=plt.subplots(ncols=2, figsize=(16, 8))
	ax[0].set_xlabel('Epochs')
	ax[0].set_ylabel('Accuracy')
	ax[0].plot(np.arange(count_of_epochs),[i for i in train_accs])
	ax[0].plot(np.arange(count_of_epochs),[i for i in val_accs])
	ax[0].legend(bbox_to_anchor = (0.3,1.17),loc = 'upper right',labels=['Train accuracy','Validation accuracy'])	
	ax[1].set_xlabel('Epochs')
	ax[1].set_ylabel('Loss')
	ax[1].plot(np.arange(count_of_epochs),[i for i in train_losses])
	ax[1].plot(np.arange(count_of_epochs),[i for i in val_losses])
	ax[1].legend(bbox_to_anchor = (1.3,1.17),loc = 'upper right',labels=['Train loss','Validation loss'])	
	plt.savefig("train_history_pytorch.jpg", dpi = 200)
	plt.close()
def GetDatasets():
	print("Data preparation...",flush=True,end='')
	start=datetime.now()
	train_transform = transforms.Compose([
	transforms.Resize((image_size, image_size)),
	transforms.RandomHorizontalFlip(),
	transforms.RandomRotation(10),
	transforms.ColorJitter(brightness=0.2, contrast=0.2, saturation=0.2),
	transforms.ToTensor(),
	transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])])	
	test_transform = transforms.Compose([
	transforms.Resize((image_size, image_size)),
	transforms.ToTensor(),
	transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])])
	full_dataset = Animals10Dataset(root_dir=dataset_path+"\\raw-img", transform=train_transform)
	if len(full_dataset) == 0:
		print("The dataset doesn't contain images")
		exit()
	indices = list(range(len(full_dataset)))
	train_val_idx, test_idx = train_test_split(indices, test_size=0.2, random_state=42)
	train_idx, val_idx = train_test_split(train_val_idx, test_size=0.2, random_state=42)
	train_dataset = torch.utils.data.Subset(full_dataset, train_idx)
	val_dataset = torch.utils.data.Subset(full_dataset, val_idx)
	test_dataset = Animals10Dataset(root_dir=dataset_path+"\\raw-img", transform=test_transform)
	test_dataset = torch.utils.data.Subset(test_dataset, test_idx)
	train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=2)
	val_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False, num_workers=2)
	test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=False, num_workers=2)
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	print("Count of classes: ",len(full_dataset.classes),":",sep='',end="")
	for i in range(len(full_dataset.classes)):
		if i%4==0:
			print()
		print('{: <{}}'.format(full_dataset.classes[i],11),end="",sep='')
		if full_dataset.classes[i] in dictionary:
			print('{: <{}}'.format(dictionary[full_dataset.classes[i]],10),end="|",sep='')
		else:
			print('{: <{}}'.format("",10),end="|",sep='')
	if i-1%4:
		print()	
	print("Count of all images: ",len(full_dataset),"; training: ",len(train_idx),
		  "; validation: ",len(val_idx),"; testing: ",len(test_idx))
	print('-' * 90)
	return full_dataset, train_loader, val_loader, test_loader
def evaluate_model(model_path):
	full_dataset, train_loader, val_loader, test_loader = GetDatasets()
	print(end="Model evaluation...",flush=True)
	start=datetime.now()	
	model = AlexNet(len(full_dataset.classes))
	model.load_state_dict(torch.load(model_path, map_location=torch.device('cpu')))
	model.to(torch_device)
	model.eval()
	count_of_classes = len(test_loader.dataset.dataset.classes)
	correct = 0
	total = 0
	class_correct = [0] * count_of_classes
	class_total = [0] * count_of_classes	
	with torch.no_grad():
		for images, labels in test_loader:
			images, labels = images.to(torch_device), labels.to(torch_device)
			outputs = model(images)
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
			class_name=test_loader.dataset.dataset.classes[i]
			if(class_name in dictionary):
				class_name+=" ("+dictionary[class_name]+")"
			print('{: <{}}'.format(class_name,21),end="",sep='')
			print(f": {class_acc:.4f}%")	
def train():
	full_dataset, train_loader, val_loader, test_loader = GetDatasets()
	train_losses, val_losses, train_accs, val_accs = train_model(train_loader, 
	val_loader)
	plot_results(train_losses, val_losses, train_accs, val_accs)
	print("The history was saved into the file train_history_pytorch.jpg")
########################################PREDICTION########################################
def predict_image(model, image_tensor, classes):
    model.eval()
    with torch.no_grad():
        image_tensor = image_tensor.unsqueeze(0).to(torch_device)  # Додаємо розмірність batch
        outputs = model(image_tensor)
        probabilities = F.softmax(outputs, dim=1)
        top_prob, top_class = torch.topk(probabilities, 5, dim=1)
        result = {
            "top_classes": [classes[class_idx.item()] for class_idx in top_class[0]],
            "top_probs": [prob.item() for prob in top_prob[0]]}
        return result
def visualize_prediction(image_path, prediction, original_class):
	image = Image.open(image_path).convert('RGB')
	plt.figure(figsize=(10, 6))
	plt.subplot(1, 1, 1)
	plt.imshow(image)
	title = "Prediction: "+prediction["top_classes"][0]
	if(prediction["top_classes"][0] in dictionary):
		title += " ("+dictionary[prediction["top_classes"][0]]+")"
	title += "; original class: " + original_class
	if(original_class in dictionary):
		title += " ("+dictionary[original_class]+")"
	title += '\n'
	for i in range(len(prediction["top_classes"])):
		title += str(i+1) + ". " + prediction["top_classes"][i]
		if(prediction["top_classes"][i] in dictionary):
			title += " ("+dictionary[prediction["top_classes"][i]]+")"
		title += f': {prediction["top_probs"][i]*100:.2f}%\n'	
	plt.title(title)
	plt.axis('off')
	plt.tight_layout()
	plt.savefig('CNN_AlexNet_pytorch_prediction_result.jpg')
def get_random_image(dataset):
    random_idx = random.randint(0, len(dataset) - 1)
    return random_idx, dataset.images[random_idx], dataset.labels[random_idx]
def predict_random_image(model, dataset, transform, dictionary):
    idx, image_path, true_label = get_random_image(dataset)
    image = Image.open(image_path).convert('RGB')
    image_tensor = transform(image)
    prediction = predict_image(model, image_tensor, dataset.classes)
    visualize_prediction(image_path, prediction, dataset.classes[true_label])
    return image_path, prediction, dataset.classes[true_label]
def predict(model_path):
	transform = transforms.Compose([
		transforms.Resize((image_size, image_size)),
		transforms.ToTensor(),
		transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])])
	dataset = Animals10Dataset(root_dir=dataset_path+"\\raw-img", transform=None)
	model = AlexNet(len(dataset.classes))
	if not os.path.exists(model_path):
		print("The model file ", model_path, "doesn't exist.")
		exit()
	model.load_state_dict(torch.load(model_path, map_location=torch_device))
	model.to(torch_device)
	model.eval()
	image_path, prediction, original_class = predict_random_image(model, dataset, transform, dictionary)
	print("Results of prediction for the image\n"+image_path+":")
	print("Predicted class: ",end=prediction["top_classes"][0])
	if(prediction["top_classes"][0] in dictionary):
		print(" ("+dictionary[prediction["top_classes"][0]],end=")")
	print("; original class: ",end=original_class)
	if(original_class in dictionary):
		print(" ("+dictionary[original_class]+")")
	for i in range(len(prediction["top_classes"])):
		print(str(i+1)+". ",end=prediction["top_classes"][i])
		if(prediction["top_classes"][i] in dictionary):
			print(" ("+dictionary[prediction["top_classes"][i]],end=")")
		print(f': {prediction["top_probs"][i]*100:.2f}%')
	print("The prediction was saved as CNN_AlexNet_pytorch_prediction_result.jpg")