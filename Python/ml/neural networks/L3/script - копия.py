import torch
import torch.nn as nn
from torch.utils.data import Dataset, DataLoader
from torch.autograd import Variable
import torchvision.datasets as dsets
import torchvision.transforms as transforms
import numpy as np
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import random
import torchvision.models as models
from datetime import datetime
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
image_size = 784
hidden_layer_size = 500
count_of_classes = 10
count_of_epochs = 5
batch_size = 100
learning_rate = 0.001
def train_model():
	print(end="Training the model...")
	start = datetime.now()

	mnist_data = np.load('mnist.npz')
	# Extract the data
	x_train = mnist_data['x_train']
	y_train = mnist_data['y_train']
	x_test = mnist_data['x_test']
	y_test = mnist_data['y_test']
	# Convert the data to PyTorch tensors
	x_train = torch.tensor(x_train, dtype=torch.float32)
	y_train = torch.tensor(y_train, dtype=torch.long)
	x_test = torch.tensor(x_test, dtype=torch.float32)
	y_test = torch.tensor(y_test, dtype=torch.long)
	# Normalize the images
	x_train = x_train / 255.0
	x_test = x_test / 255.0
	# Create a custom Dataset class
	class MNISTDataset(Dataset):
		def __init__(self, images, labels):
			self.images = images
			self.labels = labels
		def __len__(self):
			return len(self.images)
		def __getitem__(self, idx):
			return self.images[idx], self.labels[idx]
	# Create Dataset objects for train and test
	train_dataset = MNISTDataset(x_train, y_train)
	test_dataset = MNISTDataset(x_test, y_test)
	# Create DataLoader objects
	train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
	test_loader = DataLoader(test_dataset, batch_size=64, shuffle=False)
	class Net(nn.Module):
		def __init__(self, image_size, hidden_layer_size, count_of_classes):
			super(Net, self).__init__()
			self.fc1 = nn.Linear(image_size, hidden_layer_size)
			self.relu = nn.ReLU()
			self.fc2 = nn.Linear(hidden_layer_size, count_of_classes)		
		def forward(self, x):
			out = self.fc1(x)
			out = self.relu(out)
			out = self.fc2(out)
			return out
	net = Net(image_size, hidden_layer_size, count_of_classes)
	criterion = nn.CrossEntropyLoss()
	optimizer = torch.optim.Adam(net.parameters(), lr=learning_rate)
	for epoch in range(count_of_epochs):
		for i, (images, labels) in enumerate(train_loader):
			images = Variable(images.view(-1, 28*28))
			labels = Variable(labels)        
			optimizer.zero_grad()
			outputs = net(images)
			loss = criterion(outputs, labels)
			loss.backward()
			optimizer.step()        
			# if (i+1) % 100 == 0:
				# print('Epoch [%d/%d], Step [%d/%d], Loss: %.4f'
					 # %(epoch+1, count_of_epochs, i+1, len(train_dataset)//batch_size, loss.item()))
	correct = 0
	total = 0
	for images, labels in test_loader:
		images = Variable(images.view(-1, 28*28))
		outputs = net(images)
		_, predicted = torch.max(outputs.data, 1)
		total += labels.size(0)
		correct += (predicted == labels).sum()
	torch.save(net.state_dict(), 'trained_model.pkl')
	duration=datetime.now()-start
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	print('Accuracy of the network on the 10K test images: %d %%' % (100 * correct // total))
# train_model()




import torch
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
import matplotlib.pyplot as plt
import random

# 1. Define the same neural network architecture that you used for training
class NeuralNetwork(nn.Module):
	def __init__(self):
		super(NeuralNetwork, self).__init__()
		self.fc1 = nn.Linear(image_size, hidden_layer_size)
		self.relu = nn.ReLU()
		self.fc2 = nn.Linear(hidden_layer_size, count_of_classes)		
	def forward(self, x):
		out = self.fc1(x)
		out = self.relu(out)
		out = self.fc2(out)
		return out

# 2. Load the MNIST test dataset
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.1307,), (0.3081,))  # MNIST normalization values
])

# test_dataset = torchvision.datasets.MNIST(
    # root='./data',
    # train=False,
    # download=True,
    # transform=transform
# )

mnist_data = np.load('mnist.npz')
# Extract the data
x_train = mnist_data['x_train']
y_train = mnist_data['y_train']
x_test = mnist_data['x_test']
y_test = mnist_data['y_test']
# Convert the data to PyTorch tensors
x_train = torch.tensor(x_train, dtype=torch.float32)
y_train = torch.tensor(y_train, dtype=torch.long)
x_test = torch.tensor(x_test, dtype=torch.float32)
y_test = torch.tensor(y_test, dtype=torch.long)
# Normalize the images
x_train = x_train / 255.0
x_test = x_test / 255.0
# Create a custom Dataset class
class MNISTDataset(Dataset):
	def __init__(self, images, labels):
		self.images = images
		self.labels = labels
	def __len__(self):
		return len(self.images)
	def __getitem__(self, idx):
		return self.images[idx], self.labels[idx]
# Create Dataset objects for train and test
train_dataset = MNISTDataset(x_train, y_train)
test_dataset = MNISTDataset(x_test, y_test)


# 3. Initialize the model
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
model = NeuralNetwork().to(device)

# 4. Load the trained model weights
model.load_state_dict(torch.load('trained_model.pkl'))
model.eval()  # Set to evaluation mode

# 5. Select a random image from the test dataset
def predict_random_image():
    # Choose a random index
    idx = random.randint(0, len(test_dataset) - 1)
    
    # Get the image and true label
    image, true_label = test_dataset[idx]
    
    # Display the image
    plt.figure(figsize=(3, 3))
    plt.imshow(image.squeeze().numpy(), cmap='gray')
    plt.title(f"True Label: {true_label}")
    plt.axis('off')
    plt.show()
    
    # Prepare for model prediction (add batch dimension)
    # image = image.unsqueeze(0).to(device)
    image = image.reshape(-1, 28*28).to(device)
    # Make prediction
    with torch.no_grad():
        outputs = model(image)
        predicted = torch.argmax(outputs, 1)
    
    print(f"Predicted Label: {predicted.item()}")
    
    # If you want to see the confidence for each digit:
    probabilities = torch.nn.functional.softmax(outputs, dim=1)
    print("Confidence for each digit:")
    for digit, prob in enumerate(probabilities[0]):
        print(f"Digit {digit}: {prob.item()*100:.2f}%")

# Call the function to predict a random image
predict_random_image()