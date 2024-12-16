import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import seaborn as sns
import pandas as pd
import random
from sklearn.utils import shuffle
import os
from datetime import datetime
from datetime import timedelta
class PolynomialRegression:
	def __init__(
		self,
		# alpha1,
		# alpha2,
		poly_deg,
		# learning_rate,
		# batch_size,
		# train_steps
	):
		# self.alpha1 = alpha1
		# self.alpha2 = alpha2
		self.poly_deg = poly_deg
		# self.learning_rate = learning_rate
		# self.batch_size = batch_size		
		# self.train_steps = train_steps	
	def preprocess(self, x): # TODO
		PolynomialX = [x]
		for degree in range(2, self.poly_deg + 1):
			PolynomialX.append(x ** degree)
		newx_poly = np.concatenate((PolynomialX[0], np.ones((x.shape[0], 1))), axis = 1)
		newx_poly[:, :1:] = 1
		return newx_poly
		# previous preprocess (it works slowly)
		"""CountOfRows=len(x)
		CountOfColumns=len(x[0])		
		NewX=np.zeros((CountOfRows,CountOfColumns*self.poly_deg+1))
		for i in range(CountOfRows):
			NewX[i][0]=1
			l=1			
			for j in range(CountOfColumns):
				NewX[i][j+l]=x[i][j]
			k=CountOfColumns+1
			for j in range(2,self.poly_deg+1):
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
		XBatch=np.zeros((self.batch_size,len(x[0])))
		YBatch=np.zeros((self.batch_size,len(y[0])))
		RandomIndexes=[]
		for i in range(XSize):
			RandomIndexes.append(i);
		for i in range(XSize):
			j=random.randrange(0,XSize)
			t=RandomIndexes[i]
			RandomIndexes[i]=RandomIndexes[j]
			RandomIndexes[j]=t
		for i in range(self.batch_size):
			XBatch[i]=x[RandomIndexes[i]]
			YBatch[i]=y[RandomIndexes[i]]
		return [XBatch,YBatch]"""
	def grad(self, x, y, theta, alpha1, alpha2): # TODO
		return ((2/len(x)*-1)*x.T@(y-(x@theta)))+(alpha1*np.sign(theta)+2*alpha2*theta)	
	def J(self, x, y, theta, alpha1, alpha2): # TODO
		prev_y=x@theta
		mse=np.square(np.subtract(y,prev_y)).mean()
		return mse+self.alpha1*sum(sum(abs(theta)))+self.alpha2*sum(sum(theta**2))	
	def PrepareX(self,x,batch_size):
		x = self.preprocess(x)		
		self.mu, self.sigma = self.moments(x)
		x = self.normalize(x)
		try:
			assert np.allclose(x[:, 1:].mean(axis=0), 0, atol=1e-3)
			assert np.all((np.abs(x[:, 1:].std(axis=0)) < 1e-2) | (np.abs(x[:, 1:].std(axis=0) - 1) < 1e-2))
		except AssertionError as e:
			print('Something wrong with normalization')
			raise e
		x_batch, y_batch = self.get_batch(x, y, batch_size)
		try:
			assert x_batch.shape[0] == batch_size
			assert y_batch.shape[0] == batch_size
		except AssertionError as e:
			print('Something wrong with get_batch')
			raise e
		return x
	def fit(self, x, y, alpha1, alpha2, learning_rate, batch_size, train_steps):
		(m, N), (_, k) = x.shape, y.shape
		theta = np.zeros(shape=(N, k))		
		gamma = 0.9
		v_1 = np.zeros(shape=(N, k)) # TODO
		v_t = v_1		
		for step in range(train_steps):
			x_batch, y_batch = self.get_batch(x, y, batch_size)
			theta_grad = self.grad(x_batch, y_batch, theta,alpha1, alpha2)
			# TODO Update v_t and theta
			v_t = gamma * v_t + learning_rate * theta_grad
			theta = theta - v_t
		self.theta = theta
		return self
	def predict(self, x):
		x = self.preprocess(x)
		x = self.normalize(x)
		return x @ self.theta
	def score(self, x, y):
		y_pred = self.predict(x)
		return np.abs(y - y_pred).mean()
def ConvertTimeDelta(duration):
    days, seconds = duration.days, duration.seconds
    hours = days * 24 + seconds // 3600
    minutes = (seconds % 3600) // 60
    seconds = (seconds % 60)
    return str(hours), str(minutes), str(seconds)
data = pd.read_csv('data.csv')
x, y = data.values[:, :-2].astype(np.float32), data.values[:, -2:-1].astype(np.float32)
np.random.seed(1337)
is_train = np.random.uniform(size=(x.shape[0],)) < 0.95
x_train, y_train = x[is_train], y[is_train]
x_test, y_test = x[~is_train], y[~is_train]
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
MinBatchSize=MaxBatchSize=1024
MinTrainSteps=MaxTrainSteps=1000
MinScore=1000
MaxScore=-1
# Test one single model
"""print(end="Processing...",flush=True)
start=datetime.now()
reg=PolynomialRegression(MinPolydeg)
PreparedX=reg.PrepareX(x_train,MinBatchSize)
score=reg.fit(PreparedX,y_train,alpha[MinAlpha1Index],alpha[MinAlpha2Index],MinLearningRate,MinBatchSize,MinTrainSteps).score(x_test,y_test)
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Score: ",f'{score:.5f}',"; time: ",hours,":",minutes,":",seconds)"""
TotalTime=timedelta(hours=0,minutes=0,seconds=0)
LogFile = open("log.csv", "w",encoding='utf-8-sig')
BatchSize=128
BatchSizes=[]
BatchSizesScores=[]
print(end="Preparing X for Polydeg 1...",flush=True)
LogFile.write("Preparing X for polydeg: 1...")
start=datetime.now()
reg=PolynomialRegression(MinPolydeg)
PreparedX=reg.PrepareX(x_train,BatchSize)
duration=datetime.now()-start
TotalTime+=duration
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds)
LogFile.write(" Time: "+hours+":"+minutes+":"+seconds+"\n")
LogFile.write("Batch size;Score;Time\n")
while(BatchSize<len(x_train)):
	print("BatchSize: ",BatchSize,end="...",flush=True)	
	start=datetime.now()
	# score=random.randrange(10,13)
	score=reg.fit(PreparedX,y_train,alpha[MinAlpha1Index],alpha[MinAlpha2Index],MinLearningRate,BatchSize,MinTrainSteps).score(x_test,y_test)	
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Score: ",f'{score:.5f}',"; time: ",hours,":",minutes,":",seconds)
	LogFile.write(str(BatchSize)+";"+f'{score:.5f}'+";"+hours+":"+minutes+":"+seconds+"\n")
	BatchSizes.append(BatchSize)
	BatchSizesScores.append(score)
	if(score<MinScore):
		MinScore=score
		MinBatchSize=BatchSize
	if(score>MaxScore):
		MaxScore=score
		MaxBatchSize=BatchSize
	BatchSize*=2
TrainStepsScores=[]
LogFile.write("Train steps;Score;Time\n")
for i in range(len(TrainSteps)):
	print(i+1,". TrainSteps: ",TrainSteps[i],end="...",flush=True)
	start=datetime.now()
	# score=random.randrange(10,13)
	score=reg.fit(PreparedX,y_train,alpha[MinAlpha1Index],alpha[MinAlpha2Index],MinLearningRate,MinBatchSize,TrainSteps[i]).score(x_test,y_test)	
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Score: ",f'{score:.5f}',"; time: ",hours,":",minutes,":",seconds)
	LogFile.write(str(TrainSteps[i])+";"+f'{score:.5f}'+";"+hours+":"+minutes+":"+seconds+"\n")
	TrainStepsScores.append(score)
	if(score<MinScore):
		MinScore=score
		MinTrainSteps=TrainSteps[i]
	if(score>MaxScore):
		MaxScore=score
		MaxTrainSteps=TrainSteps[i]
StartLearningRate=1e-3/10
LearningRate=StartLearningRate
LearningRates=[]
LearningRateScores=[]
LogFile.write("Learning rate;Score;Time\n")
for i in range(13):	
	print(i+1,". LearningRate ",f'{LearningRate:.5f}',end="...",flush=True)
	start=datetime.now()
	# score=random.randrange(10,13)
	score=reg.fit(PreparedX,y_train,alpha[MinAlpha1Index],alpha[MinAlpha2Index],LearningRate,MinBatchSize,MinTrainSteps).score(x_test,y_test)	
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Score: ",f'{score:.5f}',"; time: ",hours,":",minutes,":",seconds)
	LogFile.write(f'{LearningRate:.5f}'+";"+f'{score:.5f}'+";"+hours+":"+minutes+":"+seconds+"\n")
	LearningRates.append(LearningRate)
	LearningRateScores.append(score)
	if(score<MinScore):
		MinScore=score
		MinLearningRate=LearningRate
	if(score>MaxScore):
		MaxScore=score
		MaxLearningRate=LearningRate
	LearningRate+=StartLearningRate
LastPolydeg=8
CountOfExperiments=len(alpha)**2*LastPolydeg
NumberOfExperiment=1
scores=np.zeros((LastPolydeg,len(alpha),len(alpha)))
for polydeg in range(1,LastPolydeg+1):
	print("Preparing X for polydeg: ",polydeg,"...",end='',flush=True)
	LogFile.write("Preparing X for polydeg: "+str(polydeg)+"...")
	start=datetime.now()
	reg=PolynomialRegression(polydeg)
	PreparedX=reg.PrepareX(x_train,MinBatchSize)
	duration=datetime.now()-start
	TotalTime+=duration
	hours,minutes,seconds=ConvertTimeDelta(duration)
	print(" Time: ",hours,":",minutes,":",seconds)
	LogFile.write(" Time: "+hours+":"+minutes+":"+seconds+"\n")
	LogFile.write("Score;Polydeg;Alpha 1;Alpha 2;Time\n")
	for Alpha1Index in range(len(alpha)):
		for Alpha2Index in range(len(alpha)):
			print(NumberOfExperiment," / ",CountOfExperiments,"; alpha1: ",AlphaStr[Alpha1Index],"; alpha2: ",AlphaStr[Alpha2Index],end="...",flush=True)
			start=datetime.now()
			# score=random.randrange(10,13)
			score=reg.fit(PreparedX,y_train,alpha[Alpha1Index],alpha[Alpha2Index],MinLearningRate,MinBatchSize,MinTrainSteps).score(x_test,y_test)			
			duration=datetime.now()-start
			TotalTime+=duration
			hours,minutes,seconds=ConvertTimeDelta(duration)
			print(" Time: ",hours,":",minutes,":",seconds,"; score: ",f'{score:.5f}')
			LogFile.write(f'{score:.5f};'+str(polydeg)+";"+AlphaStr[Alpha1Index]+";"+AlphaStr[Alpha2Index]+";"+hours+":"+minutes+":"+seconds+"\n")
			scores[polydeg-1,Alpha1Index,Alpha2Index]=f'{score:.5f}'
			if(score<MinScore):
				MinScore=score
				MinPolydeg=polydeg
				MinAlpha1Index=Alpha1Index
				MinAlpha2Index=Alpha2Index
			if(score>MaxScore):
				MaxScore=score
				MaxPolydeg=polydeg
				MaxAlpha1Index=Alpha1Index
				MaxAlpha2Index=Alpha2Index
			NumberOfExperiment+=1
	for i in range(91):
		print('-',end="")
		LogFile.write('-')
	LogFile.write("\n")
print("Min score: ",f'{MinScore:.5f}',"; polydeg: ",MinPolydeg,end="; ")
print("alpha 1: ",AlphaStr[MinAlpha1Index],"; alpha 2: ",AlphaStr[MinAlpha2Index])
print("learning rate: ",f'{MinLearningRate:.4f}',"; batch size: ",MinBatchSize,"; train steps: ",MinTrainSteps)
for i in range(91):
	print('-',end="")
print("Max score: ",f'{MaxScore:.5f}',"; polydeg: ",MaxPolydeg,end="; ")
print("alpha 1: ",AlphaStr[MaxAlpha1Index],"; alpha 2: ",AlphaStr[MaxAlpha2Index])
print("learning rate: ",f'{MaxLearningRate:.4f}',"; batch size: ",MaxBatchSize,"; train steps: ",MaxTrainSteps)
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
			LogFile.write(f'{MaxScore:.5f}'+";")
	LogFile.write("\n")
for i in range(91):	
	LogFile.write('-')
LogFile.write("\nMin score: "+f'{MinScore:.5f}'+"; polydeg: "+str(MinPolydeg)+"; ")
LogFile.write("alpha 1: "+AlphaStr[MinAlpha1Index]+"; alpha 2: "+AlphaStr[MinAlpha2Index]+"\n")
LogFile.write("learning rate: "+f'{MinLearningRate:.4f}'+"; batch size: "+str(MinBatchSize)+"; train steps: "+str(MinTrainSteps)+"\n")
for i in range(91):	
	LogFile.write('-')
LogFile.write("\nMax score: "+f'{MaxScore:.5f}'+"; polydeg: "+str(MaxPolydeg)+"; ")
LogFile.write("alpha 1: "+AlphaStr[MaxAlpha1Index]+"; alpha 2: "+AlphaStr[MaxAlpha2Index]+"\n")
LogFile.write("learning rate: "+f'{MaxLearningRate:.4f}'+"; batch size: "+str(MaxBatchSize)+"; train steps: "+str(MaxTrainSteps)+"\n")
for i in range(91):	
	LogFile.write('-')
print(end="Calculation the dependence of the predicted critical temperature on the true one...",flush=True)
LogFile.write("\nCalculation the dependence of the predicted critical temperature on the true one...")
start=datetime.now()
reg=PolynomialRegression(MinPolydeg)
PreparedX=reg.PrepareX(x_train,MinBatchSize)
score=reg.fit(PreparedX,y_train,alpha[MinAlpha1Index],alpha[MinAlpha2Index],MinLearningRate,MinBatchSize,MinTrainSteps).score(x_test, y_test)
y_test_pred=reg.predict(x_test)
duration=datetime.now()-start
TotalTime+=duration
hours,minutes,seconds=ConvertTimeDelta(duration)
print("\nTime: ",hours,":",minutes,":",seconds,f'; Test MAE: {score:.5f}')
LogFile.write("\nTime: "+hours+":"+minutes+":"+seconds+f'; Test MAE: {score:.5f}\n')
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
plt.title("Dependence of score on batch size")
plt.plot([f'{BatchSizes[i]:.0f}'for i in range(len(BatchSizes))],BatchSizesScores)
plt.xlabel('Batch size')
plt.ylabel("Score")
plt.savefig("Plots\\Batch size.jpg",dpi=200)
plt.close()
fig, ax = plt.subplots(figsize=(12, 12))
for label in (ax.get_xticklabels() + ax.get_yticklabels()):
	label.set_fontsize(14)
plt.title("Dependence of score on train steps")
plt.plot([f'{TrainSteps[i]:.0f}'for i in range(len(TrainSteps))],TrainStepsScores)
plt.xlabel('Train steps')
plt.ylabel("Score")
plt.savefig("Plots\\Train steps.jpg",dpi=200)
plt.close()
fig, ax = plt.subplots(figsize=(12, 12))
for label in (ax.get_xticklabels() + ax.get_yticklabels()):
	label.set_fontsize(14)
plt.title("Dependence of score on learning rate")
plt.plot(LearningRates,LearningRateScores)
plt.xlabel('Learning rate')
plt.ylabel("Score")
plt.savefig("Plots\\Learning rate.jpg",dpi=200)
plt.close()
for polydeg in range(1,LastPolydeg+1):
	for alpha1 in range(len(alpha)):
		filename="Polydeg "+str(polydeg)+" alpha1 "+AlphaStr[alpha1]+".jpg"
		fig,ax=plt.subplots(figsize=(12, 12))
		ax.set_xlabel('Polydeg')
		ax.set_ylabel('score')
		fig.suptitle("Polydeg: "+str(polydeg)+"; alpha 1: "+AlphaStr[alpha1])
		ax.set_xlabel('Alpha 1')
		ax.set_ylabel('score')
		ax.plot(AlphaStr,scores[polydeg-1,alpha1])
		plt.savefig("Plots\\"+filename,dpi=200)
		plt.close()		
	fig,ax=plt.subplots(ncols=2, figsize=(16, 6))
	fig.suptitle('Poly deg: '+str(polydeg))
	ax[0].set_xlabel('All combinations of alpha 1 and alpha 2')
	ax[0].set_ylabel('score')
	ax[0].plot(np.arange(len(alpha)*len(alpha)),[i for j in range(len(scores[polydeg-1])) for i in scores[polydeg-1,j]])
	ax[1].set_xlabel('Alpha 2')
	ax[1].set_ylabel('score')	
	for i in range(len(scores[polydeg-1])):
		ax[1].plot(np.arange(1,len(alpha)+1),scores[polydeg-1,i])
	plt.legend(bbox_to_anchor = (1.3,1),loc = 'upper right', title="Alpha",
	labels=[f'{str(i+1)+") "+AlphaStr[i]}'for i in range(len(AlphaStr))],fontsize=14)
	plt.savefig("Plots\\PolyDeg "+str(polydeg)+".jpg",dpi=200)
	plt.close()	
	plt.figure(figsize=(8,6))
	plt.matshow(scores[polydeg-1], cmap='GnBu',fignum=1)
	plt.colorbar(label='score')
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
ax.set_ylabel('Score')
ax.xaxis.set_major_locator(ticker.MultipleLocator(base=CountOfExperiments/(LastPolydeg-1)))
ax.xaxis.set_major_locator(ticker.FixedLocator([i*(CountOfExperiments/(LastPolydeg-1)) for i in range(LastPolydeg)]))
ax.set_xticklabels([i+1 for i in range(LastPolydeg)])
plt.plot([k for j in range(LastPolydeg) for i in range(len(alpha)) for k in scores[j,i]])
plt.savefig("Plots\\PLOT OF ALL SCORES.JPG",dpi=200)
plt.close()
plt.figure(figsize=(14, 6))
plt.matshow(np.reshape(scores,(LastPolydeg,len(alpha)*len(alpha))), cmap='GnBu', fignum=1)
plt.colorbar(label='Score',orientation="horizontal", pad=0.1)
plt.xticks(np.arange(len(alpha)*len(alpha)),[])
plt.yticks(np.arange(LastPolydeg), [i+1 for i in range(LastPolydeg)], fontsize=12)
plt.xlabel('Combinations of alpha 1 and alpha 2')
plt.ylabel('Polydeg')
plt.title('All scores')
plt.savefig("Plots\\MATSHOW OF ALL SCORES.JPG",dpi=200)
plt.close()
plt.figure(figsize=(12, 10))
plt.title("Dependence of the predicted critical temperature on the true one\n(parameters of the best model)")
plt.scatter(y_test[:, 0], y_test_pred[:, 0], marker='.', c='r')
plt.xlabel('True Y')
plt.ylabel('Predicted Y')
plt.savefig("Plots\\DEPENDENCE OF THE PRED. CRIT. TEMP.JPG")
plt.close()
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds)
LogFile.write(" Time: "+hours+":"+minutes+":"+seconds)
LogFile.close()