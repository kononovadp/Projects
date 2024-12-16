import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from sklearn.metrics import confusion_matrix
import random
from sklearn.utils import shuffle
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '1'
os.environ['CUDA_VISIBLE_DEVICES'] = '-1'
import tensorflow as tf
import tensorflow_datasets as tfds
from sklearn.preprocessing import OneHotEncoder
from datetime import datetime
from datetime import timedelta
def preprocess(dataset):
	image = tf.cast(dataset['image'], dtype=tf.float32) / 255.
	label = tf.cast(dataset['label'], dtype=tf.float32)
	return image, label
def SimpleConvolutionalNeuralNetworkModel(NumberOfClasses):
	input_ = tf.keras.layers.Input(shape=(28, 28, 1,))
	x = tf.keras.layers.Conv2D(64, (3, 3), padding='same', activation='relu')(input_)
	x = tf.keras.layers.MaxPool2D(2, 2)(x)
	x = tf.keras.layers.Dropout(0.5)(x)
	x = tf.keras.layers.Conv2D(32, (3, 3), padding='same', activation='relu')(x)
	x = tf.keras.layers.MaxPool2D(2, 2)(x)
	x = tf.keras.layers.Dropout(0.5)(x)
	x = tf.keras.layers.Conv2D(16, (3, 3), padding='same', activation='relu')(x)
	x = tf.keras.layers.MaxPool2D(2, 2)(x)
	x = tf.keras.layers.Dropout(0.5)(x)
	x = tf.keras.layers.Flatten()(x)
	x = tf.keras.layers.Dense(128, activation='relu')(x)
	output_ = tf.keras.layers.Dense(NumberOfClasses, activation='softmax')(x)
	return tf.keras.models.Model(input_, output_, name='Classifier')
def RunLogisticRegression(CountOfEpochs,BatchSize,LearningRate,TrainData,ValidationData,TestData,MetaData):
	TrainData = TrainData.map(preprocess).shuffle(buffer_size=1024).batch(BatchSize)
	ValidationData = ValidationData.map(preprocess).batch(BatchSize)
	TestData = TestData.map(preprocess).batch(BatchSize)
	NumberOfClasses = MetaData.features['label'].num_classes
	model = SimpleConvolutionalNeuralNetworkModel(NumberOfClasses)
	lr_schedule = tf.keras.optimizers.schedules.ExponentialDecay(LearningRate,decay_steps=100000,decay_rate=0.96)
	model.compile(optimizer = tf.keras.optimizers.Adam(learning_rate=lr_schedule),loss = tf.keras.losses.SparseCategoricalCrossentropy(),metrics = ['accuracy'])
	history = model.fit(TrainData, epochs=CountOfEpochs, validation_data=ValidationData,verbose=0)
	if(CountOfEpochs>1):
		fig,ax=plt.subplots(ncols=2, figsize=(20, 6))
		ax[0].set_title('Accuracy and validation accuracy')
		ax[0].set_xlabel('Epoch')
		ax[0].set_ylabel('Accuracy')
		ax[0].plot([i+1 for i in range(CountOfEpochs)],history.history['accuracy'], label = 'Train accuracy')
		ax[0].plot([i+1 for i in range(CountOfEpochs)],history.history['val_accuracy'], label = 'Validation accuracy')
		ax[0].legend(bbox_to_anchor = (0.0005,1.13),loc = 'upper right', title="Accuracy",labels=['Accuracy','Valid. accuracy'],fontsize=14)
		ax[1].set_title('Loss and validation loss')
		ax[1].set_xlabel('Epoch')
		ax[1].set_ylabel('Accuracy')
		ax[1].plot([i+1 for i in range(CountOfEpochs)],history.history['loss'], label = 'Train loss')
		ax[1].plot([i+1 for i in range(CountOfEpochs)],history.history['val_loss'], label = 'Validation loss')
		ax[1].legend(bbox_to_anchor = (1.263,1.13),loc = 'upper right', title="Loss",labels=['Loss','Valid. loss'],fontsize=14)
		plt.savefig("Plots\\CountOfEpochs "+str(CountOfEpochs)+" BatchSize "+str(BatchSize)+" LearningRate "+f'{LearningRate:.5f}'+".jpg",dpi=200)
		plt.close()	
	return model
def ConvertTimeDelta(duration):
    days, seconds = duration.days, duration.seconds
    hours = days * 24 + seconds // 3600
    minutes = (seconds % 3600) // 60
    seconds = (seconds % 60)
    return str(hours), str(minutes), str(seconds)
tf.config.threading.set_intra_op_parallelism_threads(4)
(TrainData, ValidationData, TestData), MetaData = tfds.load('mnist',split=['train[:70%]', 'train[70%:85%]', 'train[85%:]'],with_info=True)
LastEpoch=5
batches=[8,32,64,128,512,1024]
LearningRates=[0.1/5, 0.1/8, 0.1/12, 0.1/16, 0.1/20, 0.1/50]
MinCountOfEpochs=MaxCountOfEpochs=1
MinBatchSize=MaxBatchSize=batches[0]
MinLearningRate=MaxLearningRate=LearningRates[0]
MinAccuracy=1000
MaxAccuracy=-1
accuracies=np.zeros((LastEpoch,len(batches),len(LearningRates)))
ExperimentNumber=0
CountOfExperiments=LastEpoch*len(batches)*len(LearningRates)

"""CountOfEpochs=10
BatchSize=32
LearningRate=1e-3
print("\n Count of epochs: ",CountOfEpochs,"; batch size: ",BatchSize,"; learning rate: ",f'{LearningRate:.5f}')
print(end=" Processing...",flush=True)
start=datetime.now()
model=RunLogisticRegression(CountOfEpochs,BatchSize,LearningRate,TrainData,ValidationData,TestData,MetaData)
TestData = TestData.map(preprocess).batch(MaxBatchSize)
metrics=model.evaluate(TestData, batch_size=MaxBatchSize, verbose=0)
predictions=model.predict(TestData, batch_size=MaxBatchSize, verbose=0)
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds,"; accuracy: ",f'{metrics[1]:.5f}\n')"""

LogFile = open("log.csv", "w",encoding='utf-8-sig')
TotalTime=timedelta(hours=0,minutes=0,seconds=0)
for epoch in range(1,LastEpoch+1):
	for BatchNumber in range(len(batches)):
		TestDataBatched = TestData.map(preprocess).batch(batches[BatchNumber])
		for LearningRateNumber in range(len(LearningRates)):
			print(ExperimentNumber+1,"/",CountOfExperiments,". Count of epochs: ",epoch,"; batch size: ",batches[BatchNumber],"; learning rate: ",f'{LearningRates[LearningRateNumber]:.5f}')
			print(end="Processing...",flush=True)			
			LogFile.write(str(ExperimentNumber+1)+"/"+str(CountOfExperiments)+". Count of epochs: "+str(epoch)+"; batch size: "+str(batches[BatchNumber])+"; learning rate: "+f'{LearningRates[LearningRateNumber]:.5f}\n')
			LogFile.write("Processing...")
			start=datetime.now()
			# metrics=[0.2,0.1]
			# metrics[1]=random.uniform(0.2,0.99)
			model=RunLogisticRegression(epoch,batches[BatchNumber],LearningRates[LearningRateNumber],TrainData,ValidationData,TestData,MetaData)
			metrics=model.evaluate(TestDataBatched, batch_size=batches[BatchNumber], verbose=0)
			duration=datetime.now()-start
			TotalTime+=duration
			hours,minutes,seconds=ConvertTimeDelta(duration)
			accuracies[epoch-1,BatchNumber,LearningRateNumber]=metrics[1]
			if(metrics[1]>MaxAccuracy):
				MaxAccuracy=metrics[1]
				MaxCountOfEpochs=epoch
				MaxBatchSize=batches[BatchNumber]
				MaxLearningRate=LearningRates[LearningRateNumber]
			if(metrics[1]<MinAccuracy):
				MinAccuracy=metrics[1]
				MinCountOfEpochs=epoch
				MinBatchSize=batches[BatchNumber]
				MinLearningRate=LearningRates[LearningRateNumber]
			print(" Time: ",hours,":",minutes,":",seconds,"; accuracy: ",f'{metrics[1]:.5f}')
			LogFile.write(" Time: "+hours+":"+minutes+":"+seconds+"; accuracy: "+f'{metrics[1]:.5f}\n')
			for i in range(91):
				print(end="-")
				LogFile.write("-")
			LogFile.write("\n")
			ExperimentNumber+=1
for i in range(91):
	print(end="=")
print("Max accuracy: ",f'{MaxAccuracy:.5f}',"; Count of epochs: ",MaxCountOfEpochs,end="; ")
print("batch size: ",MaxBatchSize,"; learning rate: ",f'{MaxLearningRate:.5f}')
print("Min accuracy: ",f'{MinAccuracy:.5f}',"; Count of epochs: ",MinCountOfEpochs,end="; ")
print("batch size: ",MinBatchSize,"; learning rate: ",f'{MinLearningRate:.5f}')
hours,minutes,seconds=ConvertTimeDelta(TotalTime)
print("Total time of all calculations: ",hours,":",minutes,":",seconds)
LogFile.write("Count of epochs;Batch size;Learning rate;Accuracy\n")
for epoch in range(1,LastEpoch+1):
	for BatchNumber in range(len(batches)):		
		for LearningRateNumber in range(len(LearningRates)):
			LogFile.write(str(epoch)+";"+str(batches[BatchNumber])+";"+f'{LearningRates[LearningRateNumber]:.5f};'+f'{accuracies[epoch-1,BatchNumber,LearningRateNumber]:.5f}\n')
for i in range(91):
	LogFile.write("-")
LogFile.write("\nMax accuracy: "+f'{MaxAccuracy:.5f}'+"; Count of epochs: "+str(MaxCountOfEpochs)+"; ")
LogFile.write("batch size: "+str(MaxBatchSize)+"; learning rate: "+f'{MaxLearningRate:.5f}\n')
LogFile.write("Min accuracy: "+f'{MinAccuracy:.5f}'+"; Count of epochs: "+str(MinCountOfEpochs)+"; ")
LogFile.write("batch size: "+str(MinBatchSize)+"; learning rate: "+f'{MinLearningRate:.5f}\n')
hours,minutes,seconds=ConvertTimeDelta(TotalTime)
LogFile.write("Total time of all calculations: "+hours+":"+minutes+":"+seconds)
print(end="Drawing plots...",flush=True)
LogFile.write("\nDrawing plots...")
start=datetime.now()
plt.rcParams['font.size'] = '18'
for epoch in range(1,LastEpoch+1):
	fig,ax=plt.subplots(figsize=(12, 12))
	fig.suptitle("Count of epochs: "+str(epoch))
	ax.set_xlabel('All combinations of learning rate and batch size')
	ax.set_ylabel('Accuracy')
	ax.plot([i for i in range(len(batches)*len(LearningRates))],[i for j in range(len(accuracies[epoch-1])) for i in accuracies[epoch-1,j]])
	plt.savefig("Plots\\"+"Plot Count of epochs "+str(epoch)+".jpg",dpi=200)
	plt.close()	
	plt.figure(figsize=(8,6))
	plt.matshow(accuracies[epoch-1], cmap='GnBu',fignum=1)
	plt.colorbar(label='Accuracy')
	plt.xticks(np.arange(len(batches)),batches,fontsize=12)
	plt.yticks(np.arange(len(LearningRates)),[f'{LearningRates[i]:.5f}'for i in range(len(LearningRates))])
	plt.xlabel('Batch size')
	plt.ylabel('Learning rate')
	plt.title("Count of epochs: "+str(epoch))
	plt.savefig("Plots\\Matshow Count of epochs "+str(epoch)+".jpg",dpi=200)
	plt.close()
fig,ax=plt.subplots(figsize=(24,12))
fig.suptitle("Plot of all accuracies")
ax.set_xlabel('Count of epochs')
ax.set_ylabel('Accuracy')
ax.xaxis.set_major_locator(ticker.MultipleLocator(base=CountOfExperiments/(LastEpoch-1)))
ax.xaxis.set_major_locator(ticker.FixedLocator([i*(CountOfExperiments/(LastEpoch-1)) for i in range(LastEpoch)]))
ax.set_xticklabels([i+1 for i in range(LastEpoch)])
plt.plot([k for j in range(LastEpoch) for i in range(len(batches)) for k in accuracies[j,i]])
plt.savefig("Plots\\PLOT OF ALL ACCURACIES.JPG",dpi=200)
plt.close()
plt.figure(figsize=(14, 6))
plt.matshow(np.reshape(accuracies,(LastEpoch,len(batches)*len(LearningRates))), cmap='GnBu', fignum=1)
plt.colorbar(label='Accuracy',orientation="horizontal", pad=0.1)
plt.xticks(np.arange(len(batches)*len(LearningRates)),[])
plt.yticks(np.arange(LastEpoch), [i+1 for i in range(LastEpoch)], fontsize=12)
plt.xlabel('Combinations of learning rate and batch size')
plt.ylabel('Count of epochs')
plt.title('All accuracies')
plt.savefig("Plots\\MATSHOW OF ALL ACCURACIES.JPG",dpi=200)
plt.close()
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds)
LogFile.write(" Time: "+hours+":"+minutes+":"+seconds)
LogFile.close()