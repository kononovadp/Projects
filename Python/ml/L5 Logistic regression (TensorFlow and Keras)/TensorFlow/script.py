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
from sklearn.preprocessing import OneHotEncoder
from datetime import datetime
from datetime import timedelta
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
class LogisticRegression(tf.Module):
	def __init__(self, x):
		self.mean = tf.Variable(tf.math.reduce_mean(x, axis=0))
		self.std = tf.Variable(tf.math.reduce_std(x, axis=0)) + pow(10, -8)
	def normalize(self, x):
		return (x - self.mean)/self.std
	def GetTrainAndTestDataSets(self, BatchSize, x_train, y_train, x_test, y_test):
		TrainDataset = tf.data.Dataset.from_tensor_slices((x_train, y_train))
		TrainDataset = TrainDataset.shuffle(buffer_size=x_train.shape[0]).batch(BatchSize)
		TestDataset = tf.data.Dataset.from_tensor_slices((x_test, y_test))
		TestDataset = TestDataset.shuffle(buffer_size=x_test.shape[0]).batch(BatchSize)
		return TrainDataset, TestDataset		
	def ComputeTheModelOutput(self, x, w, b):
		return tf.nn.softmax(tf.add(tf.matmul(x, w), b))
	def GetAccuracy(self, y_pred, y):
		prediction = tf.equal(tf.argmax(y_pred, 1), tf.argmax(y, 1))
		return tf.reduce_mean(tf.cast(prediction, tf.float32))		
	def GetLoss(self, y_pred, y):
		return tf.nn.softmax_cross_entropy_with_logits(labels=y, logits=y_pred)
	def RunModel(self, CountOfEpochs, LearningRate, TrainDataset, TestDataset, DetailedOutputOn):
		w, b = tf.Variable(tf.zeros([784,10])), tf.Variable(tf.zeros([10]))
		if(DetailedOutputOn):
			TrainLosses, TestLosses = [], []
			TrainAccuracies, TestAccuracies = [], []
			for epoch in range(CountOfEpochs):
				print("Epoch ",epoch+1,"/",CountOfEpochs,end="...",flush=True)
				LogFile.write("Epoch "+str(epoch+1)+"/"+str(CountOfEpochs)+"...")
				BatchTrainLosses, BatchTrainAccuracies = [], []
				BatchTestLosses, BatchTestAccuracies = [], []				
				for XBatch, YBatch in TrainDataset:
					with tf.GradientTape() as tape:
						YPredBatch = self.ComputeTheModelOutput(XBatch, w, b)
						BatchLoss = self.GetLoss(YPredBatch, YBatch)
					BatchAccuracy = self.GetAccuracy(YPredBatch, YBatch)
					gradients = tape.gradient(BatchLoss, [w, b])
					for g, v in zip(gradients, [w, b]):
						v.assign_sub(LearningRate * g)					
					BatchTrainLosses.append(BatchLoss)
					BatchTrainAccuracies.append(BatchAccuracy)
					gradients=[]
					tape=[]				
				for XBatch, YBatch in TestDataset:
					YPredBatch = self.ComputeTheModelOutput(XBatch, w, b)
					BatchLoss = self.GetLoss(YPredBatch, YBatch)
					BatchAccuracy = self.GetAccuracy(YPredBatch, YBatch)				
				BatchTestLosses.append(BatchLoss)
				BatchTestAccuracies.append(BatchAccuracy)
				TrainLoss, TrainAccuracy = tf.reduce_mean(BatchTrainLosses), tf.reduce_mean(BatchTrainAccuracies)
				TestLoss, TestAccuracy = tf.reduce_mean(BatchTestLosses), tf.reduce_mean(BatchTestAccuracies)
				TrainLosses.append(TrainLoss)
				TrainAccuracies.append(TrainAccuracy)
				TestLosses.append(TestLoss)
				TestAccuracies.append(TestAccuracy)
				print(" Training accuracy.: ",f'{TrainAccuracy:.5f}',"; testing accuracy.: ",f'{TestAccuracy:.5f}')				
				print("Training loss: ",f'{TrainLoss:.5f}',"; testing loss: ",f'{TestLoss:.5f};')
				LogFile.write(" Training accuracy.: "+f'{TrainAccuracy:.5f}'+"; testing accuracy.: "+f'{TestAccuracy:.5f}\n')
				LogFile.write("Training loss: "+f'{TrainLoss:.5f}'+"; testing loss: "+f'{TestLoss:.5f};\n')
				for i in range(91):
					print('-',end="")
					LogFile.write('-')
				LogFile.write('\n')
			return TrainAccuracy, TestAccuracy, TrainLoss, TestLoss, TrainAccuracies, TestAccuracies, TrainLosses, TestLosses, w, b
		else:
			for epoch in range(CountOfEpochs):
				BatchTrainLosses, BatchTrainAccuracies = [], []
				BatchTestLosses, BatchTestAccuracies = [], []
				for XBatch, YBatch in TrainDataset:
					with tf.GradientTape() as tape:
						YPredBatch = self.ComputeTheModelOutput(XBatch, w, b)
						BatchLoss = self.GetLoss(YPredBatch, YBatch)
					BatchAccuracy = self.GetAccuracy(YPredBatch, YBatch)
					gradients = tape.gradient(BatchLoss, [w, b])
					for g, v in zip(gradients, [w, b]):
						v.assign_sub(LearningRate * g)
					BatchTrainLosses.append(BatchLoss)
					BatchTrainAccuracies.append(BatchAccuracy)
					gradients=[]
					tape=[]
				for XBatch, YBatch in TestDataset:
					YPredBatch = self.ComputeTheModelOutput(XBatch, w, b)
					BatchLoss = self.GetLoss(YPredBatch, YBatch)
					BatchAccuracy = self.GetAccuracy(YPredBatch, YBatch)
				BatchTestLosses.append(BatchLoss)
				BatchTestAccuracies.append(BatchAccuracy)
				TrainLoss, TrainAccuracy = tf.reduce_mean(BatchTrainLosses), tf.reduce_mean(BatchTrainAccuracies)
				TestLoss, TestAccuracy = tf.reduce_mean(BatchTestLosses), tf.reduce_mean(BatchTestAccuracies)
		return TrainAccuracy, TestAccuracy, TrainLoss, TestLoss
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
x_train, y_train = tf.convert_to_tensor(x_train, dtype=tf.float32), tf.convert_to_tensor(y_train, dtype=tf.float32)
x_test, y_test = tf.convert_to_tensor(x_test, dtype=tf.float32), tf.convert_to_tensor(y_test, dtype=tf.float32)
"""CountOfEpochs = 10
BatchSize = 32
LearningRate = 1e-3
print("\n Count of epochs: ", CountOfEpochs, "; batch size: ", BatchSize, "; learning rate: ", f'{LearningRate:.5f}', end = "...")
start=datetime.now()
LogReg = LogisticRegression(x_train)
x_train = LogReg.normalize(x_train)
x_test = LogReg.normalize(x_test)
TrainDataset, TestDataset = LogReg.GetTrainAndTestDataSets(BatchSize, x_train, y_train, x_test, y_test)
TrainAccuracy, TestAccuracy, TrainLoss, TestLoss = LogReg.RunModel(CountOfEpochs, LearningRate, TrainDataset, TestDataset, False)
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print("\n Training accuracy.: ",f'{TrainAccuracy:.5f}',"; testing accuracy.: ",f'{TestAccuracy:.5f};')
print(" Training loss: ",f'{TrainLoss:.5f}',"; testing loss: ",f'{TestLoss:.5f}; time: ',hours,":",minutes,":",seconds,"\n")"""
CountOfEpochs = 10
batches=[50, 200, 800, 1000, 3000, 10000]
LearningRates=[0.1/5, 0.1/8, 0.1/12, 0.1/16, 0.1/20, 0.1/50]
LearningRatesStr = [f'{LearningRates[i]:.5f}' for i in range(len(LearningRates))]
MinTrainAccuracy, MinTestAccuracy = 100, 100
MaxTrainAccuracy, MaxTestAccuracy = 0.01, 0.01
MinTrainLoss, MinTestLoss = 100, 100
MaxTrainLoss, MaxTestLoss = 0.01, 0.01
TotalTime=timedelta(hours=0,minutes=0,seconds=0)
LogFile = open("log.csv", "w",encoding='utf-8-sig')
ExperimentNumber, CountOfExperiments = 0, len(batches)*len(LearningRates)
TrainAccuracies, TestAccuracies = np.zeros((len(batches), len(LearningRates))), np.zeros((len(batches), len(LearningRates)))
TrainLosses, TestLosses = np.zeros((len(batches), len(LearningRates))), np.zeros((len(batches), len(LearningRates)))
LogReg = LogisticRegression(x_train)
x_train = LogReg.normalize(x_train)
x_test = LogReg.normalize(x_test)
for BatchIndex in range(len(batches)):
	TrainDataset, TestDataset = LogReg.GetTrainAndTestDataSets(batches[BatchIndex], x_train, y_train, x_test, y_test)
	for LearningRateIndex in range(len(LearningRates)):
		ExperimentNumber += 1
		print(ExperimentNumber,"/",CountOfExperiments,". Count of epochs: ",CountOfEpochs,"; batch size: ",batches[BatchIndex],"; learning rate: ",f'{LearningRates[LearningRateIndex]:.5f}',end="...",flush=True)		
		LogFile.write(str(ExperimentNumber)+"/"+str(CountOfExperiments)+". Count of epochs: "+str(CountOfEpochs)+"; batch size: "+str(batches[BatchIndex])+"; learning rate: "+f'{LearningRates[LearningRateIndex]:.5f}...')
		start=datetime.now()
		TrainAccuracy, TestAccuracy, TrainLoss, TestLoss = LogReg.RunModel(CountOfEpochs, LearningRates[LearningRateIndex], TrainDataset, TestDataset, False)
		# TrainAccuracy, TestAccuracy, TrainLoss, TestLoss = random.uniform(0.85, 0.99), random.uniform(0.85, 0.99), random.uniform(0.85, 0.99), random.uniform(0.85, 0.99)
		duration=datetime.now()-start
		TotalTime+=duration
		hours,minutes,seconds=ConvertTimeDelta(duration)
		print("\nTraining accuracy.: ",f'{TrainAccuracy:.5f}',"; testing accuracy.: ",f'{TestAccuracy:.5f};')
		print("Training loss: ",f'{TrainLoss:.5f}',"; testing loss: ",f'{TestLoss:.5f}; time: ',hours,":",minutes,":",seconds )		
		LogFile.write("\nTraining accuracy.: "+f'{TrainAccuracy:.5f}'+"; testing accuracy.: "+f'{TestAccuracy:.5f};\n')
		LogFile.write("Training loss: "+f'{TrainLoss:.5f}'+"; testing loss: "+f'{TestLoss:.5f}; time: '+hours+":"+minutes+":"+seconds+'\n')		
		for i in range(91):
			print('-',end="")
			LogFile.write('-')
		LogFile.write('\n')
		TrainAccuracies[BatchIndex, LearningRateIndex] = TrainAccuracy
		TestAccuracies[BatchIndex, LearningRateIndex] = TestAccuracy
		TrainLosses[BatchIndex, LearningRateIndex] = TrainLoss
		TestLosses[BatchIndex, LearningRateIndex] = TestLoss
		if(TrainAccuracy > MaxTrainAccuracy):
			MaxTrainAccuracy = TrainAccuracy
			MaxTrainAccBatchIndex = BatchIndex
			MaxTrainAccLearningRateIndex = LearningRateIndex
		if(TrainAccuracy < MinTrainAccuracy):
			MinTrainAccuracy = TrainAccuracy
			MinTrainAccBatchIndex = BatchIndex
			MinTrainAccLearningRateIndex = LearningRateIndex
		if(TestAccuracy > MaxTestAccuracy):
			MaxTestAccuracy = TestAccuracy
			MaxTestAccBatchIndex = BatchIndex
			MaxTestAccLearningRateIndex = LearningRateIndex
		if(TestAccuracy < MinTestAccuracy):
			MinTestAccuracy = TestAccuracy
			MinTestAccBatchIndex = BatchIndex
			MinTestAccLearningRateIndex = LearningRateIndex
		if(TrainLoss > MaxTrainLoss):
			MaxTrainLoss = TrainLoss
			MaxTrainLossBatchIndex = BatchIndex
			MaxTrainLossLearningRateIndex = LearningRateIndex
		if(TrainLoss < MinTrainLoss):
			MinTrainLoss = TrainLoss
			MinTrainLossBatchIndex = BatchIndex
			MinTrainLossLearningRateIndex = LearningRateIndex
		if(TestLoss > MaxTestLoss):
			MaxTestLoss = TestLoss
			MaxTestLossBatchIndex = BatchIndex
			MaxTestLossLearningRateIndex = LearningRateIndex
		if(TestLoss < MinTestLoss):
			MinTestLoss = TestLoss
			MinTestLossBatchIndex = BatchIndex
			MinTestLossLearningRateIndex = LearningRateIndex
print("Max training accuracy: ", f'{MaxTrainAccuracy:.5f}', end = "")
print("; batch size: ", batches[MaxTrainAccBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MaxTrainAccLearningRateIndex]:.5f}')
print("Max testing accuracy: ", f'{MaxTestAccuracy:.5f}', end = "")
print("; batch size: ", batches[MaxTestAccBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MaxTestAccLearningRateIndex]:.5f}')
print("Min training accuracy: ", f'{MinTrainAccuracy:.5f}', end = "")
print("; batch size: ", batches[MinTrainAccBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MinTrainAccLearningRateIndex]:.5f}')
print("Min testing accuracy: ", f'{MinTestAccuracy:.5f}', end = "")
print("; batch size: ", batches[MinTestAccBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MinTestAccLearningRateIndex]:.5f}')
print("Max training loss: ", f'{MaxTrainLoss:.5f}', end = "")
print("; batch size: ", batches[MaxTrainLossBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MaxTrainLossLearningRateIndex]:.5f}')
print("Max testing loss: ", f'{MaxTestLoss:.5f}', end = "")
print("; batch size: ", batches[MaxTestLossBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MaxTestLossLearningRateIndex]:.5f}')
print("Min training loss: ", f'{MinTrainLoss:.5f}', end = "")
print("; batch size: ", batches[MinTrainLossBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MinTrainLossLearningRateIndex]:.5f}')
print("Min testing loss: ", f'{MinTestLoss:.5f}', end = "")
print("; batch size: ", batches[MinTestLossBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MinTestLossLearningRateIndex]:.5f}')
LogFile.write("Max training accuracy: "+ f'{MaxTrainAccuracy:.5f}')
LogFile.write("; batch size: "+ str(batches[MaxTrainAccBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MaxTrainAccLearningRateIndex]:.5f}\n')
LogFile.write("Max testing accuracy: "+ f'{MaxTestAccuracy:.5f}')
LogFile.write("; batch size: "+ str(batches[MaxTestAccBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MaxTestAccLearningRateIndex]:.5f}\n')
LogFile.write("Min training accuracy: "+ f'{MinTrainAccuracy:.5f}')
LogFile.write("; batch size: "+ str(batches[MinTrainAccBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MinTrainAccLearningRateIndex]:.5f}\n')
LogFile.write("Min testing accuracy: "+ f'{MinTestAccuracy:.5f}')
LogFile.write("; batch size: "+ str(batches[MinTestAccBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MinTestAccLearningRateIndex]:.5f}\n')
LogFile.write("Max training loss: "+ f'{MaxTrainLoss:.5f}')
LogFile.write("; batch size: "+ str(batches[MaxTrainLossBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MaxTrainLossLearningRateIndex]:.5f}\n')
LogFile.write("Max testing loss: "+ f'{MaxTestLoss:.5f}')
LogFile.write("; batch size: "+ str(batches[MaxTestLossBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MaxTestLossLearningRateIndex]:.5f}\n')
LogFile.write("Min training loss: "+ f'{MinTrainLoss:.5f}')
LogFile.write("; batch size: "+ str(batches[MinTrainLossBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MinTrainLossLearningRateIndex]:.5f}\n')
LogFile.write("Min testing loss: "+ f'{MinTestLoss:.5f}')
LogFile.write("; batch size: "+ str(batches[MinTestLossBatchIndex]))
LogFile.write("; learning rate: "+ f'{LearningRates[MinTestLossLearningRateIndex]:.5f}\n')
hours,minutes,seconds=ConvertTimeDelta(TotalTime)
print("Time: ",hours,":",minutes,":",seconds)
LogFile.write("Time: "+hours+":"+minutes+":"+seconds+"\n")
for i in range(91):
	print('=',end="")
	LogFile.write('=')
LogFile.write('\n')
print("Count of epochs: ", CountOfEpochs, end = "")
print("; batch size: ", batches[MaxTrainAccBatchIndex], end = "")
print("; learning rate: ", f'{LearningRates[MaxTrainAccLearningRateIndex]:.5f}')
LogFile.write("Count of epochs: "+str(CountOfEpochs))
LogFile.write("; batch size: "+str(batches[MaxTrainAccBatchIndex]))
LogFile.write("; learning rate: "+f'{LearningRates[MaxTrainAccLearningRateIndex]:.5f}\n')
CountOfEpochs = 1000
start = datetime.now()
TrainDataset, TestDataset = LogReg.GetTrainAndTestDataSets(batches[MaxTrainAccBatchIndex], x_train, y_train, x_test, y_test)
TrainAccuracy, TestAccuracy, TrainLoss, TestLoss, TrainAccuraciesEpochsTest, TestAccuraciesEpochsTest, TrainLossesEpochsTest, TestLossesEpochsTest, w, b = LogReg.RunModel(CountOfEpochs, LearningRates[MaxTrainAccLearningRateIndex], TrainDataset, TestDataset, True)
duration=datetime.now()-start
TotalTime+=duration
hours,minutes,seconds=ConvertTimeDelta(duration)
print("Training accuracy.: ",f'{TrainAccuracy:.5f}',"; testing accuracy.: ",f'{TestAccuracy:.5f};')
print("Training loss: ",f'{TrainLoss:.5f}',"; testing loss: ",f'{TestLoss:.5f}; time: ',hours,":",minutes,":",seconds)
LogFile.write("Training accuracy.: "+f'{TrainAccuracy:.5f}'+"; testing accuracy.: "+f'{TestAccuracy:.5f};\n')
LogFile.write("Training loss: "+f'{TrainLoss:.5f}'+"; testing loss: "+f'{TestLoss:.5f}; time: '+hours+":"+minutes+":"+seconds+"\n")
hours,minutes,seconds=ConvertTimeDelta(TotalTime)
print("Total time of all calculations: ",hours,":",minutes,":",seconds)
LogFile.write("Total time of all calculations: "+hours+":"+minutes+":"+seconds+"\n")
print(end="Building plots...",flush=True)
LogFile.write("Building plots...")
start = datetime.now()
plt.rcParams['font.size'] = '36'
for BatchIndex in range(len(batches)):
	plt.figure(figsize=(40, 25))
	plt.plot(LearningRatesStr, TrainAccuracies[BatchIndex], label = "Training")
	plt.plot(LearningRatesStr, TestAccuracies[BatchIndex], label = "Testing")
	plt.xlabel("Learning rates")
	plt.ylabel("Accuracy")
	plt.legend(bbox_to_anchor = (1.135,1),loc = 'upper right', title = "Accuracy")
	plt.title("Plot of accuracy; batch size: " + str(batches[BatchIndex]));
	plt.savefig("Plots\\Accuracy with batch " + str(batches[BatchIndex]) + ".jpg")
	plt.close()	
	plt.figure(figsize=(40, 25))
	plt.plot(LearningRatesStr, TrainLosses[BatchIndex], label = "Training")
	plt.plot(LearningRatesStr, TestLosses[BatchIndex], label = "Testing")
	plt.xlabel("Learning rates")
	plt.ylabel("Loss")
	plt.legend(bbox_to_anchor = (1.135,1),loc = 'upper right', title = "Loss")
	plt.title("Plot of loss; batch size: " + str(batches[BatchIndex]));
	plt.savefig("Plots\\Loss with batch " + str(batches[BatchIndex]) + ".jpg")
	plt.close()
plt.figure(figsize=(40, 25))
plt.plot(range(1,CountOfExperiments+1), [accuracy for i in range(len(TrainAccuracies)) for accuracy in TrainAccuracies[i]], label = "Training")
plt.plot(range(1,CountOfExperiments+1), [accuracy for i in range(len(TestAccuracies)) for accuracy in TestAccuracies[i]], label = "Testing")
plt.xlabel("All combinations of batch sizes and learning rates")
plt.ylabel("Accuracy")
plt.legend(bbox_to_anchor = (1.135,1),loc = 'upper right', title = "Accuracy")
plt.title("Plot of all accuracies");
plt.savefig("Plots\\PLOT OF ALL ACCURACIES.jpg")
plt.close()	
plt.figure(figsize=(40, 25))
plt.plot(range(1,CountOfExperiments+1), [loss for i in range(len(TrainLosses)) for loss in TrainLosses[i]], label = "Training")
plt.plot(range(1,CountOfExperiments+1), [loss for i in range(len(TestLosses)) for loss in TestLosses[i]], label = "Testing")
plt.xlabel("All combinations of batch sizes and learning rates")
plt.ylabel("Loss")
plt.legend(bbox_to_anchor = (1.135,1),loc = 'upper right', title = "Loss")
plt.title("Plot of all losses");
plt.savefig("Plots\\PLOT OF ALL LOSSES.jpg")
plt.close()
plt.figure(figsize=(20,15))
plt.matshow(TrainAccuracies, cmap='GnBu',fignum=1)
plt.colorbar(label='accuracy')
plt.xticks(np.arange(len(LearningRatesStr)),LearningRatesStr,fontsize=28)	
plt.yticks(np.arange(len(batches)),batches)
plt.xlabel('Learning rate')
plt.ylabel('Batch size')
plt.title("MATSHOW OF ALL TRAINING ACCURACIES")
plt.savefig("Plots\\MATSHOW OF ALL TRAIN ACCURACIES.jpg",dpi=200)
plt.close()
plt.figure(figsize=(20,15))
plt.matshow(TestAccuracies, cmap='GnBu',fignum=1)
plt.colorbar(label='accuracy')
plt.xticks(np.arange(len(LearningRatesStr)),LearningRatesStr,fontsize=28)	
plt.yticks(np.arange(len(batches)),batches)
plt.xlabel('Learning rate')
plt.ylabel('Batch size')
plt.title("MATSHOW OF ALL TESTING ACCURACIES")
plt.savefig("Plots\\MATSHOW OF ALL TEST ACCURACIES.jpg",dpi=200)
plt.close()
plt.figure(figsize=(20,15))
plt.matshow(TrainLosses, cmap='GnBu',fignum=1)
plt.colorbar(label='accuracy')
plt.xticks(np.arange(len(LearningRatesStr)),LearningRatesStr,fontsize=28)	
plt.yticks(np.arange(len(batches)),batches)
plt.xlabel('Learning rate')
plt.ylabel('Batch size')
plt.title("MATSHOW OF ALL TRAINING LOSSES")
plt.savefig("Plots\\MATSHOW OF ALL TRAIN LOSSES.jpg",dpi=200)
plt.close()
plt.figure(figsize=(20,15))
plt.matshow(TestLosses, cmap='GnBu',fignum=1)
plt.colorbar(label='accuracy')
plt.xticks(np.arange(len(LearningRatesStr)),LearningRatesStr,fontsize=28)	
plt.yticks(np.arange(len(batches)),batches)
plt.xlabel('Learning rate')
plt.ylabel('Batch size')
plt.title("MATSHOW OF ALL TESTING LOSSES")
plt.savefig("Plots\\MATSHOW OF ALL TEST LOSSES.jpg",dpi=200)
plt.close()
plt.figure(figsize=(40, 25))
plt.plot(range(CountOfEpochs), TrainAccuraciesEpochsTest, label = "Training")
plt.plot(range(CountOfEpochs), TestAccuraciesEpochsTest, label = "Testing")
plt.xlabel("Epoch")
plt.ylabel("Accuracy")
plt.legend(bbox_to_anchor = (1.135,1),loc = 'upper right', title = "Accuracy")
plt.title("Accuracy vs training and testing iterations. Count of epochs: "+str(CountOfEpochs))
plt.savefig("Plots\\Accuracy with "+str(CountOfEpochs)+" epochs.jpg")
plt.close()
plt.figure(figsize=(40, 25))
plt.plot(range(CountOfEpochs), TrainLossesEpochsTest, label = "Training")
plt.plot(range(CountOfEpochs), TestLossesEpochsTest, label = "Testing")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.legend(bbox_to_anchor = (1.135,1),loc = 'upper right', title = "Loss")
plt.title("Loss vs training and testing iterations. Count of epochs: "+str(CountOfEpochs))
plt.savefig("Plots\\Loss with "+str(CountOfEpochs)+" epochs.jpg")
plt.close()
plt.rcParams['font.size'] = '12'
def BuildConfusionMatrix(y, y_classes, type):
    plt.figure(figsize=(10,10))
    confusion = sk_metrics.confusion_matrix(y, np.argmax(y_classes, axis = 1))
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
x_train_model_output = LogReg.ComputeTheModelOutput(x_train, w, b)
x_test_model_output = LogReg.ComputeTheModelOutput(x_test, w, b)
TrainClasses = tf.cast(x_train_model_output > 0.5, tf.float32)
TestClasses = tf.cast(x_test_model_output > 0.5, tf.float32)
BuildConfusionMatrix(y_train_no_onehot, TrainClasses, 'TRAINING')
BuildConfusionMatrix(y_test_no_onehot, TestClasses, 'TESTING')
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds)
LogFile.write(" Time: "+hours+":"+minutes+":"+seconds)
LogFile.close()