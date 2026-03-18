import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from sklearn.metrics import confusion_matrix
import sklearn.metrics as sk_metrics
import random
import seaborn as sns
from sklearn.utils import shuffle
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '1'
os.environ['CUDA_VISIBLE_DEVICES'] = '-1'
import tensorflow as tf
import tensorflow_datasets as tfds
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from keras.models import Sequential
from keras.layers import Dense
from keras import backend as K
import keras
import numpy as np
from sklearn.preprocessing import OneHotEncoder
from datetime import datetime
from datetime import timedelta
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def KerasLogisticRegression(x_train, y_train, x_test, y_test, CountOfEpochs, BatchSize, DetailedOutputOn):
	model = Sequential()
	model.add(Dense(512, input_dim=28 * 28, activation='relu', name='Hidden-1'))
	model.add(Dense(256, activation='relu', name='Hidden-2'))
	model.add(Dense(10, activation='softmax', name='Output'))
	model.compile('adam', loss='categorical_crossentropy', metrics=['accuracy'])
	history = model.fit(x_train, y_train, epochs=CountOfEpochs, batch_size=BatchSize, validation_split=0.2, verbose=0)
	AccuracyAndLoss = model.evaluate(x=x_test, y=y_test, verbose=0)	
	if DetailedOutputOn:
		train_pred = model.predict(x_train, verbose=0)
		test_pred = model.predict(x_test, verbose=0)
		return AccuracyAndLoss[1], AccuracyAndLoss[0], history, train_pred, test_pred
	return AccuracyAndLoss[1], AccuracyAndLoss[0]
with np.load('mnist.npz') as npz:
	x_train, y_train, x_test, y_test = [npz[k] for k in ['x_train', 'y_train', 'x_test', 'y_test']]
x_train = x_train.reshape(-1, 28 * 28)
x_test = x_test.reshape(-1, 28 * 28)
x_train = x_train/255
x_test = x_test/255
x_train = x_train.astype(np.float32)
x_test = x_test.astype(np.float32)
y_train_no_onehot = y_train
y_test_no_onehot = y_test
y_train = tf.one_hot(y_train, 10)
y_test = tf.one_hot(y_test, 10)
CountOfEpochs = 10
batches=[10, 50, 128, 200, 512, 800, 1024, 2000, 4096, 10000, 50000]
MaxAccuracy, MinAccuracy = 0.01, 10
MaxLoss, MinLoss = 0.01, 10
TotalTime=timedelta(hours=0,minutes=0,seconds=0)
CountOfExperiments = len(batches)
accuracies, losses = np.zeros((len(batches))), np.zeros((len(batches)))
"""CountOfEpochs = 10
BatchSize = 32
print("\n Count of epochs: ", CountOfEpochs, "; batch size: ", BatchSize, end = "...")
start=datetime.now()
accuracy, loss = KerasLogisticRegression(x_train, y_train, x_test, y_test, CountOfEpochs, BatchSize, False)
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(' Time: ',hours,":",minutes,":",seconds,"\n Accuracy: ",f'{accuracy:.5f}',"; loss: ",f'{loss:.5f}\n')"""
for BatchIndex in range(len(batches)):
	print(BatchIndex+1,"/",CountOfExperiments,". Count of epochs: ",CountOfEpochs,"; batch size: ",batches[BatchIndex],end="...",flush=True)
	start=datetime.now()
	# accuracy, loss = random.uniform(0.85, 0.99), random.uniform(0.85, 0.99)
	accuracy, loss = KerasLogisticRegression(x_train, y_train, x_test, y_test, CountOfEpochs, batches[BatchIndex], False)	
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(' Time: ',hours,":",minutes,":",seconds,"\nAccuracy: ",f'{accuracy:.5f}',"; loss: ",f'{loss:.5f}')
	for i in range(91):
		print(end='-')
	if(accuracy > MaxAccuracy):
		MaxAccuracy = accuracy
		MaxAccuracyBatchSize = batches[BatchIndex]	
	if(accuracy < MinAccuracy):
		MinAccuracy = accuracy
		MinAccuracyBatchSize = batches[BatchIndex]	
	if(loss < MinLoss):
		MinLoss = loss
		MinLossBatchSize = batches[BatchIndex]
	if(loss > MaxLoss):
		MaxLoss = loss
		MaxLossBatchSize = batches[BatchIndex]
	accuracies[BatchIndex] = accuracy
	losses[BatchIndex] = loss
hours,minutes,seconds=ConvertTimeDelta(TotalTime)
print("Max accuracy: ", f'{MaxAccuracy:.5f}', "; batch size: ", MaxAccuracyBatchSize, end = "; ")
print("Min accuracy: ", f'{MinAccuracy:.5f}', "; batch size: ", MinAccuracyBatchSize)
print("Max loss: ", f'{MaxLoss:.5f}', "; batch size: ", MaxLossBatchSize, end = "; ")
print("Min loss: ", f'{MinLoss:.5f}', "; batch size: ", MinLossBatchSize)
print("Time: ",hours,":",minutes,":",seconds)
for i in range(91):
	print(end='=')
CountOfEpochs = 1000
print("Count of epochs: ",CountOfEpochs,"; batch size: ",MaxAccuracyBatchSize,end="...",flush=True)
start=datetime.now()
accuracy, loss, history, train_pred, test_pred = KerasLogisticRegression(x_train, y_train, x_test, y_test, CountOfEpochs, MaxAccuracyBatchSize, True)
duration=datetime.now()-start
TotalTime+=duration
print(' Time: ',hours,":",minutes,":",seconds,"\nAccuracy: ",f'{accuracy:.5f}',"; loss: ",f'{loss:.5f}')
hours,minutes,seconds=ConvertTimeDelta(TotalTime)
print("Total time of all calculations: ",hours,":",minutes,":",seconds)
print(end="Building plots...",flush=True)
start = datetime.now()
plt.rcParams['font.size'] = '36'
plt.figure(figsize=(40, 25))
plt.plot([f'{i:.0f}' for i in batches], accuracies)
plt.xlabel("Batch sizes")
plt.ylabel("Accuracy")
plt.title("Plot of accuracy");
plt.savefig("Plots\\Accuracy.jpg")
plt.close()
plt.figure(figsize=(40, 25))
plt.plot([f'{i:.0f}' for i in batches], losses)
plt.xlabel("Batch sizes")
plt.ylabel("Loss")
plt.title("Plot of loss");
plt.savefig("Plots\\Loss.jpg")
plt.close()
plt.rcParams['font.size'] = '18'
fig,ax=plt.subplots(ncols=2, figsize=(20, 6))
ax[0].set_title('Accuracy and validation accuracy')
ax[0].set_xlabel('Epoch')
ax[0].set_ylabel('Accuracy')
ax[0].plot([i+1 for i in range(CountOfEpochs)],history.history['accuracy'], label = 'Train accuracy')
ax[0].plot([i+1 for i in range(CountOfEpochs)],history.history['val_accuracy'], label = 'Validation accuracy')
ax[0].legend(bbox_to_anchor = (0.0005,1.13),loc = 'upper right', title="Accuracy",labels=['Accuracy','Valid. accuracy'],fontsize=14)
ax[1].set_title('Loss and validation loss')
ax[1].set_xlabel('Epoch')
ax[1].set_ylabel('Loss')
ax[1].plot([i+1 for i in range(CountOfEpochs)],history.history['loss'], label = 'Train loss')
ax[1].plot([i+1 for i in range(CountOfEpochs)],history.history['val_loss'], label = 'Validation loss')
ax[1].legend(bbox_to_anchor = (1.263,1.13),loc = 'upper right', title="Loss",labels=['Loss','Valid. loss'],fontsize=14)
plt.savefig("Plots\\CountOfEpochs "+str(CountOfEpochs)+" BatchSize "+str(MaxAccuracyBatchSize)+".jpg",dpi=200)
plt.close()
plt.rcParams['font.size'] = '12'
def BuildConfusionMatrix(y_train_no_onehot, y_classes, type):
	plt.figure(figsize=(10,10))
	confusion = sk_metrics.confusion_matrix(y_train_no_onehot, np.argmax(y_classes, axis = 1))
	confusion_normalized = confusion / confusion.sum(axis=1, keepdims=True)
	axis_labels = range(1,11)
	plt.xticks(axis_labels)
	plt.yticks(axis_labels)
	ax = sns.heatmap(
		confusion_normalized, xticklabels=axis_labels, yticklabels=axis_labels,
		cmap='Blues', annot=True, fmt='.4f', square=True)
	plt.title(f"Confusion matrix: {type}")
	plt.ylabel("True label")
	plt.xlabel("Predicted label")  
	plt.savefig("Plots\\CONFUSION MATRIX OF "+type+".jpg")
	plt.close()
BuildConfusionMatrix(y_train_no_onehot, train_pred, 'TRAINING')
BuildConfusionMatrix(y_test_no_onehot, test_pred, 'TESTING')
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds)