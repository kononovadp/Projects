import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
from sklearn.metrics import confusion_matrix
import pandas as pd
import random
from sklearn.utils import shuffle
import os
from datetime import datetime
from datetime import timedelta
class LogisticRegression:
	def __init__(self,
		items=[]
		# alpha1
		# alpha2,
		# learning_rate,
		# batch_size,
		# train_steps
	):
		self.l = items
		# self.alpha1 = alpha1
		# self.alpha2 = alpha2
		# self.learning_rate = learning_rate
		# self.batch_size = batch_size
		# self.train_steps = train_steps
	def onehot(self, y):
		OnehotY=np.zeros((len(y),10))
		for i in range(len(y)):
			OnehotY[i][y[i]]=1		
		return OnehotY
	def preprocess(self, x, poly_deg): # TODO
		PolynomialX = [x]
		for degree in range(2, poly_deg + 1):
			PolynomialX.append(x ** degree)
		newx_poly = np.concatenate((PolynomialX[0], np.ones((x.shape[0], 1))), axis = 1)
		newx_poly[:, :1:] = 1
		return newx_poly
		# previous preprocess (it works slowly)
		"""CountOfRows=len(x)
		CountOfColumns=len(x[0])		
		NewX=np.zeros((CountOfRows,CountOfColumns*poly_deg+1))
		for i in range(CountOfRows):
			NewX[i][0]=1
			l=1			
			for j in range(CountOfColumns):
				NewX[i][j+l]=x[i][j]
			k=CountOfColumns+1
			for j in range(2,poly_deg+1):
				for l in range(CountOfColumns):
					NewX[i][k]=x[i][l]**j
					k+=1
		return NewX"""
	def normalize(self, x): # TODO
		# Z-масштабування даних на основі середнього значення та стандартного відхилення: ділення різниці між змінною та середнім значенням на стандартне відхилення.
		CountOfRows=len(x)
		CountOfColumns=len(x[0])		
		VerySmallNumber=pow(10,-8)
		for i in range(CountOfRows):
			for j in range(CountOfColumns):
				x[i][j]=((x[i][j]-self.mu[j]))/(self.sigma[j]+VerySmallNumber)
		return x
	def moments(self, x): # TODO
		CountOfRows=len(x)		
		CountOfColumns=len(x[0])
		MeanDeviations=[0]
		StandardDeviations=[1]
		for i in range(1,CountOfColumns):
			column=[]
			for j in range(CountOfRows):
				column.append(x[j][i])
			MeanDeviations.append(np.mean(column,axis=0))
			StandardDeviations.append(np.std(column,axis=0))
		return [MeanDeviations,StandardDeviations]		
	def get_batch(self, x, y, batch_size): # TODO
		RandomIndexes=np.random.randint(len(x),size=batch_size)
		return x[RandomIndexes],y[RandomIndexes]
		# previous get_batch 2 (it works faster)
		"""XSize=len(x)				
		RandomIndexes=np.array([i for i in range(XSize)])
		random.shuffle(RandomIndexes)
		return np.array([x[RandomIndexes[i]] for i in range(batch_size)]),np.array([y[RandomIndexes[i]] for i in range(batch_size)])"""
		# previous get_batch 1 (it works slowly)
		"""XSize=len(x)
		YSize=len(y)
		XBatch=np.zeros((batch_size,len(x[0])))
		YBatch=np.zeros((batch_size,len(y[0])))
		RandomIndexes=[]
		for i in range(XSize):
			RandomIndexes.append(i);
		for i in range(XSize):
			j=random.randrange(0,XSize)
			t=RandomIndexes[i]
			RandomIndexes[i]=RandomIndexes[j]
			RandomIndexes[j]=t
		for i in range(batch_size):
			XBatch[i]=x[RandomIndexes[i]]
			YBatch[i]=y[RandomIndexes[i]]
		return [XBatch,YBatch]"""
	def PrepareX(self,x,poly_deg):
		x = self.preprocess(x,poly_deg)
		self.mu, self.sigma = self.moments(x)
		return self.normalize(x)		
	def J(self, x, y, theta): # TODO
		return 0
	def sigmoid(self,x):
		return 1/(1+np.exp(-x))
	def h(self, x, theta): # TODO
		return self.sigmoid(x@theta)
	def grad(self, x, y, theta, alpha1, alpha2): # TODO
		return ((1/len(x)*-1)*x.T@(y-self.h(x,theta)))+(alpha1*np.sign(theta)+2*alpha2*theta)
	def fit(self, x, y, alpha1, alpha2, learning_rate, batch_size, train_steps):
		(m, n), (_, c) = x.shape, y.shape
		theta = np.zeros(shape=(n, c))
		gamma = 0.9
		v_1 = np.zeros(shape=(n, c)) #TODO
		v_t = v_1		
		for step in range(train_steps):
			x_batch, y_batch = self.get_batch(x, y, batch_size)
			theta_grad = self.grad(x_batch, y_batch, theta, alpha1, alpha2)
			# TODO Update v_t and theta
			v_t = gamma * v_t + learning_rate * theta_grad
			theta = theta - v_t
		self.theta = theta
		return self
	def predict(self, x):
		x = self.preprocess(x,1)
		x = self.normalize(x)
		return self.h(x, self.theta).argmax(axis=1)
	def score(self, x, y):
		y_pred = self.predict(x)
		return (y == y_pred).mean() * 100
def ConvertTimeDelta(duration):
    days, seconds = duration.days, duration.seconds
    hours = days * 24 + seconds // 3600
    minutes = (seconds % 3600) // 60
    seconds = (seconds % 60)
    return str(hours), str(minutes), str(seconds)		
with np.load('mnist.npz') as npz:
	x_train, y_train, x_test, y_test = [npz[k] for k in ['x_train', 'y_train', 'x_test', 'y_test']]
fig, ax = plt.subplots(figsize=(20, 4),  ncols=5)
for a in ax:
	i = np.random.randint(x_train.shape[0])
	a.matshow(x_train[i], cmap='gray')
	a.set_title(f'Label: {y_train[i]}')
	a.axis('off')
plt.savefig("Plots\\numbers.jpg")
plt.close()
# print(f'x_train shape: {x_train.shape}')
# print(f'x_test shape: {x_test.shape}')
x_train = x_train.reshape(-1, 28 * 28)
x_test = x_test.reshape(-1, 28 * 28)
# print(f'x_train shape after reshape: {x_train.shape}')
# print(f'x_test shape after reshape: {x_test.shape}')
x_train = x_train.astype(np.float32)
x_test = x_test.astype(np.float32)
# reg = LogisticRegression(0, 0, 1e-3, 32, 1000).fit(x_train, y_train)
# print(f'Test accuracy: {reg.accuracy(x_test, y_test) * 100}%')
alpha=[0]
alpha=np.hstack((alpha,10 ** np.linspace(-5, -1, 5)))
AlphaStr=[]
for AlphaFloat in alpha:
	AlphaStr.append(f'{AlphaFloat:.5f}')
TrainSteps=[100,500,1000,5000,10000]	
MinPolydeg=MaxPolydeg=1
MinAlpha1Index=MaxAlpha1Index=0
MinAlpha2Index=MaxAlpha2Index=0
MinLearningRate=MaxLearningRate=1e-3
MinBatchSize=MaxBatchSize=8
MinTrainSteps=MaxTrainSteps=1000
MinAccuracy=1000
MaxAccuracy=-1

"""print(end="Processing...",flush=True)
start=datetime.now()
reg=LogisticRegression()
OnehotY=reg.onehot(y_train)
PreparedX=reg.PrepareX(x_train,MinPolydeg)
accuracy=reg.fit(PreparedX,OnehotY,alpha[MaxAlpha1Index],alpha[MaxAlpha2Index],MaxLearningRate,MaxBatchSize,MaxTrainSteps).score(x_test,y_test)
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" accuracy: ",f'{accuracy:.5f}%',"; time: ",hours,":",minutes,":",seconds)"""

TotalTime=timedelta(hours=0,minutes=0,seconds=0)
LogFile = open("log.csv", "w",encoding='utf-8-sig')
BatchSize=8
BatchSizes=[]
BatchSizesAccuracies=[]
print(end="Preparing X for Polydeg 1...",flush=True)
LogFile.write("Preparing X for polydeg: 1...")
start=datetime.now()
reg=LogisticRegression()
OnehotY=reg.onehot(y_train)
PreparedX=reg.PrepareX(x_train,MinPolydeg)
duration=datetime.now()-start
TotalTime+=duration
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds)
LogFile.write(" Time: "+hours+":"+minutes+":"+seconds+"\n")
LogFile.write("Batch size;accuracy;Time\n")
while(BatchSize<2048):
	print("BatchSize: ",BatchSize,end="...",flush=True)	
	start=datetime.now()
	# accuracy=random.randrange(85,90)
	accuracy=reg.fit(PreparedX,OnehotY,alpha[MaxAlpha1Index],alpha[MaxAlpha2Index],MaxLearningRate,BatchSize,MaxTrainSteps).score(x_test,y_test)	
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" accuracy: ",f'{accuracy:.5f}',"; time: ",hours,":",minutes,":",seconds)
	LogFile.write(str(BatchSize)+";"+f'{accuracy:.5f}'+";"+hours+":"+minutes+":"+seconds+"\n")
	BatchSizes.append(BatchSize)
	BatchSizesAccuracies.append(accuracy)
	if(accuracy<MinAccuracy):
		MinAccuracy=accuracy
		MinBatchSize=BatchSize
	if(accuracy>MaxAccuracy):
		MaxAccuracy=accuracy
		MaxBatchSize=BatchSize
	BatchSize*=2
TrainStepsAccuracies=[]
LogFile.write("Train steps;accuracy;Time\n")
for i in range(len(TrainSteps)):
	print(i+1,". TrainSteps: ",TrainSteps[i],end="...",flush=True)
	start=datetime.now()
	# accuracy=random.randrange(85,90)
	accuracy=reg.fit(PreparedX,OnehotY,alpha[MaxAlpha1Index],alpha[MaxAlpha2Index],MaxLearningRate,MaxBatchSize,TrainSteps[i]).score(x_test,y_test)
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" accuracy: ",f'{accuracy:.5f}',"; time: ",hours,":",minutes,":",seconds)
	LogFile.write(str(TrainSteps[i])+";"+f'{accuracy:.5f}'+";"+hours+":"+minutes+":"+seconds+"\n")
	TrainStepsAccuracies.append(accuracy)
	if(accuracy>MaxAccuracy):
		MaxAccuracy=accuracy
		MaxTrainSteps=TrainSteps[i]
	if(accuracy<MinAccuracy):
		MinAccuracy=accuracy
		MinTrainSteps=TrainSteps[i]	
StartLearningRate=1e-3/10
LearningRate=StartLearningRate
LearningRates=[]
LearningRateAccuracies=[]
LogFile.write("Learning rate;accuracy;Time\n")
for i in range(13):	
	print(i+1,". LearningRate ",f'{LearningRate:.5f}',end="...",flush=True)
	start=datetime.now()
	# accuracy=random.randrange(85,90)
	accuracy=reg.fit(PreparedX,OnehotY,alpha[MaxAlpha1Index],alpha[MaxAlpha2Index],LearningRate,MaxBatchSize,MaxTrainSteps).score(x_test,y_test)
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" accuracy: ",f'{accuracy:.5f}',"; time: ",hours,":",minutes,":",seconds)
	LogFile.write(f'{LearningRate:.5f}'+";"+f'{accuracy:.5f}'+";"+hours+":"+minutes+":"+seconds+"\n")
	LearningRates.append(LearningRate)
	LearningRateAccuracies.append(accuracy)
	if(accuracy>MaxAccuracy):
		MaxAccuracy=accuracy
		MaxLearningRate=LearningRate
	if(accuracy<MinAccuracy):
		MinAccuracy=accuracy
		MinLearningRate=LearningRate	
	LearningRate+=StartLearningRate
LastPolydeg=8
CountOfExperiments=len(alpha)**2*LastPolydeg
NumberOfExperiment=1
scores=np.zeros((LastPolydeg,len(alpha),len(alpha)))
for polydeg in range(1,LastPolydeg+1):
	print("Preparing X for polydeg: ",polydeg,"...",end='',flush=True)
	LogFile.write("Preparing X for polydeg: "+str(polydeg)+"...")
	start=datetime.now()
	PreparedX=reg.PrepareX(x_train,polydeg)
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	LogFile.write(" Time: "+hours+":"+minutes+":"+seconds+"\n")
	LogFile.write("accuracy;Polydeg;Alpha 1;Alpha 2;Time\n")
	for Alpha1Index in range(len(alpha)):
		for Alpha2Index in range(len(alpha)):
			print(NumberOfExperiment," / ",CountOfExperiments,"; alpha1: ",AlphaStr[Alpha1Index],"; alpha2: ",AlphaStr[Alpha2Index],end="...",flush=True)
			start=datetime.now()
			# accuracy=random.randrange(85,90)
			accuracy=reg.fit(PreparedX,OnehotY,alpha[Alpha1Index],alpha[Alpha2Index],MaxLearningRate,MaxBatchSize,MaxTrainSteps).score(x_test,y_test)			
			duration=datetime.now()-start
			TotalTime+=duration
			hours,minutes,seconds=ConvertTimeDelta(duration)
			print(" Time: ",hours,":",minutes,":",seconds,"; accuracy: ",f'{accuracy:.4f}')
			LogFile.write(f'{accuracy:.5f};'+str(polydeg)+";"+AlphaStr[Alpha1Index]+";"+AlphaStr[Alpha2Index]+";"+hours+":"+minutes+":"+seconds+"\n")
			scores[polydeg-1,Alpha1Index,Alpha2Index]=f'{accuracy:.5f}'
			if(accuracy>MaxAccuracy):
				MaxAccuracy=accuracy
				MaxPolydeg=polydeg
				MaxAlpha1Index=Alpha1Index
				MaxAlpha2Index=Alpha2Index
			if(accuracy<MinAccuracy):
				MinAccuracy=accuracy
				MinPolydeg=polydeg
				MinAlpha1Index=Alpha1Index
				MinAlpha2Index=Alpha2Index
			NumberOfExperiment+=1
	for i in range(91):
		print('-',end="")
		LogFile.write('-')
	LogFile.write("\n")
print("Max accuracy: ",f'{MaxAccuracy:.5f}%',"; polydeg: ",MaxPolydeg,end="; ")
print("alpha 1: ",AlphaStr[MaxAlpha1Index],"; alpha 2: ",AlphaStr[MaxAlpha2Index])
print("learning rate: ",f'{MaxLearningRate:.4f}',"; batch size: ",MaxBatchSize,"; train steps: ",MaxTrainSteps)
for i in range(91):
	print('-',end="")
print("Min accuracy: ",f'{MinAccuracy:.5f}%',"; polydeg: ",MinPolydeg,end="; ")
print("alpha 1: ",AlphaStr[MinAlpha1Index],"; alpha 2: ",AlphaStr[MinAlpha2Index])
print("learning rate: ",f'{MinLearningRate:.4f}',"; batch size: ",MinBatchSize,"; train steps: ",MinTrainSteps)
for i in range(91):
	print('-',end="")
for alpha1 in range(len(alpha)):
	for alpha2 in range(len(alpha)):
		LogFile.write(AlphaStr[alpha1]+" - "+AlphaStr[alpha2]+";")
LogFile.write("\n")
for polydeg in range(LastPolydeg):
	LogFile.write(str(polydeg+1)+";")
	for alpha1 in range(len(alpha)):
		for alpha2 in range(len(alpha)):
			LogFile.write(f'{MaxAccuracy:.5f}'+";")
	LogFile.write("\n")
for i in range(91):
	LogFile.write('-')
LogFile.write("\nMax accuracy: "+f'{MaxAccuracy:.5f}%'+"; polydeg: "+str(MaxPolydeg)+"; ")
LogFile.write("alpha 1: "+AlphaStr[MaxAlpha1Index]+"; alpha 2: "+AlphaStr[MaxAlpha2Index]+"\n")
LogFile.write("learning rate: "+f'{MaxLearningRate:.4f}'+"; batch size: "+str(MaxBatchSize)+"; train steps: "+str(MaxTrainSteps)+"\n")
for i in range(91):
	LogFile.write('-')
LogFile.write("\nMin accuracy: "+f'{MinAccuracy:.5f}%'+"; polydeg: "+str(MinPolydeg)+"; ")
LogFile.write("alpha 1: "+AlphaStr[MinAlpha1Index]+"; alpha 2: "+AlphaStr[MinAlpha2Index]+"\n")
LogFile.write("learning rate: "+f'{MinLearningRate:.4f}'+"; batch size: "+str(MinBatchSize)+"; train steps: "+str(MinTrainSteps)+"\n")
for i in range(91):	
	LogFile.write('-')
LogFile.write("\n")
print(end="Best model...",flush=True)
LogFile.write("Best model...")
start=datetime.now()
PreparedX=reg.PrepareX(x_train,MaxPolydeg)
accuracy=reg.fit(PreparedX,OnehotY,alpha[MaxAlpha1Index],alpha[MaxAlpha2Index],MaxLearningRate,MaxBatchSize,MaxTrainSteps).score(x_test,y_test)
y_test_pred=reg.predict(x_test)
duration=datetime.now()-start
TotalTime+=duration
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds,f'; Test accuracy: {accuracy:.5f}%')
LogFile.write(" Time: "+hours+":"+minutes+":"+seconds+f'; Test accuracy: {accuracy:.5f}%\n')
hours,minutes,seconds=ConvertTimeDelta(TotalTime)
print("Total time of all calculations: ",hours,":",minutes,":",seconds)
LogFile.write("Total time of all calculations: "+hours+":"+minutes+":"+seconds+"\n")
print(end="Drawing plots...",flush=True)
LogFile.write("Drawing plots...")
start=datetime.now()
if not os.path.exists("Plots"):
	os.makedirs("Plots")
plt.rcParams['font.size'] = '18'
fig, ax = plt.subplots(figsize=(12, 12))
for label in (ax.get_xticklabels() + ax.get_yticklabels()):
	label.set_fontsize(14)
plt.title("Dependence of accuracy on batch size")
plt.plot([f'{BatchSizes[i]:.0f}'for i in range(len(BatchSizes))],BatchSizesAccuracies)
plt.xlabel('Batch size')
plt.ylabel("accuracy")
plt.savefig("Plots\\Batch size.jpg",dpi=200)
plt.close()
fig, ax = plt.subplots(figsize=(12, 12))
for label in (ax.get_xticklabels() + ax.get_yticklabels()):
	label.set_fontsize(14)
plt.title("Dependence of accuracy on train steps")
plt.plot([f'{TrainSteps[i]:.0f}'for i in range(len(TrainSteps))],TrainStepsAccuracies)
plt.xlabel('Train steps')
plt.ylabel("accuracy")
plt.savefig("Plots\\Train steps.jpg",dpi=200)
plt.close()
fig, ax = plt.subplots(figsize=(12, 12))
for label in (ax.get_xticklabels() + ax.get_yticklabels()):
	label.set_fontsize(14)
plt.title("Dependence of accuracy on learning rate")
plt.plot(LearningRates,LearningRateAccuracies)
plt.xlabel('Learning rate')
plt.ylabel("accuracy")
plt.savefig("Plots\\Learning rate.jpg",dpi=200)
plt.close()
for polydeg in range(1,LastPolydeg+1):
	for alpha1 in range(len(alpha)):
		filename="Polydeg "+str(polydeg)+" alpha1 "+AlphaStr[alpha1]+".jpg"
		fig,ax=plt.subplots(figsize=(12, 12))
		ax.set_xlabel('Polydeg')
		ax.set_ylabel('accuracy')
		fig.suptitle("Polydeg: "+str(polydeg)+"; alpha 1: "+AlphaStr[alpha1])
		ax.set_xlabel('Alpha 1')
		ax.set_ylabel('accuracy')
		ax.plot(AlphaStr,scores[polydeg-1,alpha1])
		plt.savefig("Plots\\"+filename,dpi=200)
		plt.close()		
	fig,ax=plt.subplots(ncols=2, figsize=(16, 6))
	fig.suptitle('Poly deg: '+str(polydeg))
	ax[0].set_xlabel('All combinations of alpha 1 and alpha 2')
	ax[0].set_ylabel('accuracy')
	ax[0].plot(np.arange(len(alpha)*len(alpha)),[i for j in range(len(scores[polydeg-1])) for i in scores[polydeg-1,j]])
	ax[1].set_xlabel('Alpha 2')
	ax[1].set_ylabel('accuracy')	
	for i in range(len(scores[polydeg-1])):
		ax[1].plot(np.arange(1,len(alpha)+1),scores[polydeg-1,i])
	plt.legend(bbox_to_anchor = (1.3,1),loc = 'upper right', title="Alpha",
	labels=[f'{str(i+1)+") "+AlphaStr[i]}'for i in range(len(AlphaStr))],fontsize=14)
	plt.savefig("Plots\\PolyDeg "+str(polydeg)+".jpg",dpi=200)
	plt.close()	
	plt.figure(figsize=(8,6))
	plt.matshow(scores[polydeg-1], cmap='GnBu',fignum=1)
	plt.colorbar(label='accuracy')
	plt.xticks(np.arange(len(alpha)),AlphaStr,fontsize=12)	
	plt.yticks(np.arange(len(alpha)),AlphaStr)
	plt.xlabel('alpha2')
	plt.ylabel('alpha1')
	plt.title('ALPHA 1 and ALPHA 2'+"; POLYDEG: "+str(polydeg))
	plt.savefig("Plots\\Matshow PolyDeg "+str(polydeg)+".jpg",dpi=200)
	plt.close()
fig,ax=plt.subplots(figsize=(24,12))
fig.suptitle("Plot of all scores")
ax.set_xlabel('Polydeg')
ax.set_ylabel('accuracy')
ax.xaxis.set_major_locator(ticker.MultipleLocator(base=CountOfExperiments/(LastPolydeg-1)))
ax.xaxis.set_major_locator(ticker.FixedLocator([i*(CountOfExperiments/(LastPolydeg-1)) for i in range(LastPolydeg)]))
ax.set_xticklabels([i+1 for i in range(LastPolydeg)])
plt.plot([k for j in range(LastPolydeg) for i in range(len(alpha)) for k in scores[j,i]])
plt.savefig("Plots\\PLOT OF ALL SCORES.JPG",dpi=200)
plt.close()
plt.figure(figsize=(14, 6))
plt.matshow(np.reshape(scores,(LastPolydeg,len(alpha)*len(alpha))), cmap='GnBu', fignum=1)
plt.colorbar(label='accuracy',orientation="horizontal", pad=0.1)
plt.xticks(np.arange(len(alpha)*len(alpha)),[])
plt.yticks(np.arange(LastPolydeg), [i+1 for i in range(LastPolydeg)], fontsize=12)
plt.xlabel('Combinations of alpha 1 and alpha 2')
plt.ylabel('Polydeg')
plt.title('All scores')
plt.savefig("Plots\\MATSHOW OF ALL SCORES.JPG",dpi=200)
plt.close()
cm = confusion_matrix(y_test, y_test_pred)
plt.figure(figsize=(10, 10))
plt.imshow(cm)
plt.xlabel('Predicted class')
plt.ylabel('True class')
plt.xticks(range(10))
plt.yticks(range(10))
plt.savefig("Plots\\CONFUSION MATRIX OF BEST MODEL.JPG",dpi=200)
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds)
LogFile.write(" Time: "+hours+":"+minutes+":"+seconds)
LogFile.close()