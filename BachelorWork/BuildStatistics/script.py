import pandas as pd
import numpy as np
from sklearn import preprocessing
import matplotlib.pyplot as plt
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
import seaborn as sns
from sklearn.ensemble import RandomForestClassifier
from sklearn import svm
def GetArrayFromLinesOfCSVFormat(FileName):	
	lines=[]
	file=open(FileName,'r',encoding='UTF8')
	file.readline()
	for line in file:
		lines.append(line)
	file.close()
	arr=[]
	LineNumber=0
	j=0
	for line in lines:
		i=0
		PrevI=0
		arr.append([])
		for j in range(0,5):
			while(line[i]!=';'):
				i+=1
			arr[LineNumber].append(line[PrevI:i])
			i+=1
			PrevI=i	
		arr[LineNumber].append([])		
		while True:		
			while(line[i]!=',' and line[i]!=';'):
				i+=1
			arr[LineNumber][5].append(line[PrevI:i])
			if(line[i]==';'):
				break			
			i+=1
			PrevI=i
		for j in range(0,4):
			i+=1
			PrevI=i
			while(line[i]!=';' and line[i]!='\n'):
				i+=1
			arr[LineNumber].append(line[PrevI:i])			
		if(arr[LineNumber][9]=="Невдала будівля"):
			arr[LineNumber].append(0)
		else:
			arr[LineNumber].append(1)
		LineNumber+=1
	# arr.sort(key = lambda x: x[10])	
	return arr
def AddToDictionary(dict,value):
	if (value not in dict):
		dict[value]=1
	else:
		dict[value]+=1
def LoadFromDictionaryToArray(dict):
	arr=[]
	arr.append([])
	arr.append([])
	for key, value in dict.items():
		arr[0].append(key)
		arr[1].append(value)
	return arr
def DrawHorizontalPlot(data,title,FileName):
	fig, ax = plt.subplots()
	sns.barplot(x=data[1], y=data[0])
	fig.set_size_inches(15,10)
	plt.rcParams['font.size'] = '20'
	plt.title(title,fontsize=20)
	plt.tight_layout()
	plt.savefig(FileName)
def DrawPieChart(data,title,FileName):	
	for i in range(0,len(data[0])):
		data[0][i]=data[0][i]+" ("+str(data[1][i])+")"
	fig, ax = plt.subplots()
	ax.pie(data[1],autopct='%1.1f%%',pctdistance=1.4,explode=[0.15] + [0 for _ in range(len(data[0]) - 1)],textprops={'fontsize': 20})
	plt.legend(bbox_to_anchor = (0.22,1),loc = 'upper right', labels = data[0],fontsize=20)
	plt.title(title,fontsize=20)
	ax.axis("equal")
	fig.set_size_inches(15,10)
	plt.savefig(FileName)
def GetPredictions(DataForPrediction,x_train, x_test, y_train, y_test):
	lgc = LogisticRegression(solver='lbfgs',random_state=0)
	lgc.fit(x_train, y_train)
	LGCPredictions = lgc.predict(DataForPrediction)
	rfc = RandomForestClassifier()
	rfc.fit(x_train,y_train)
	RFPredictions = rfc.predict(DataForPrediction)
	SVM = svm.SVC()
	SVM.fit(x_train, y_train)
	SVMPredictions = SVM.predict(DataForPrediction)
	LgsAccuracy=lgc.score(x_test,y_test)
	RfcAccuracy=rfc.score(x_test,y_test)
	SvmAccuracy=SVM.score(x_test,y_test)
	if LgsAccuracy>RfcAccuracy and LgsAccuracy>SvmAccuracy:
		return LGCPredictions
	else:
		if RfcAccuracy>LgsAccuracy and RfcAccuracy>SvmAccuracy:
			return RFPredictions
	return SVMPredictions
def GetBestPredictions(DataForPrediction,x_train, x_test, y_train, y_test):
	predictions=GetPredictions(DataForPrediction,x_train, x_test, y_train, y_test)
	CountOfFinishedConstructions=0
	CountOfUnfinishedConstructions=0	
	for i in predictions:
		if i==0:
			CountOfUnfinishedConstructions+=1
		else:
			CountOfFinishedConstructions+=1	
	return (CountOfUnfinishedConstructions*100.0)/len(DataForPrediction)
def BuildPlotOfPredictions(DataForPrediction,x_train,x_test,y_train,y_test,steps,title,ColumnName,LabelY,FileName):
	predictions=[]
	AverageChangedValuesForPlot=[]
	ChangedDataForPrediction=[]
	for j in range(0,len(steps)):
		DataFrameCopy = DataForPrediction.copy()
		ChangedDataForPrediction.append(DataFrameCopy)
		predictions.append([])
	for i in range(0,10):	
		AverageChangedValues=[]
		for j in range(0,len(steps)):
			AverageChangedValue=0.0
			for k in range(0,len(ChangedDataForPrediction[j])):
				AverageChangedValue+=float(ChangedDataForPrediction[j][ColumnName][k])
			AverageChangedValues.append(AverageChangedValue/len(ChangedDataForPrediction[j]))
		AverageChangedValueForPlot=0.0
		for j in range(0,len(steps)):
			AverageChangedValueForPlot+=AverageChangedValues[j]
		AverageChangedValuesForPlot.append(AverageChangedValueForPlot/len(steps))
		for j in range(0,len(steps)):
			predictions[j].append(GetBestPredictions(ChangedDataForPrediction[j],x_train, x_test, y_train, y_test))
		for j in range(0,len(steps)):
			for k in range(0,len(ChangedDataForPrediction[j])):
				ChangedDataForPrediction[j][ColumnName][k]=str(float(ChangedDataForPrediction[j][ColumnName][k])+float(steps[j]))
	plt.figure(figsize=(15,15))
	for i in range(0,len(steps)):
		plt.plot(predictions[i],AverageChangedValuesForPlot,label="step "+str(steps[i]))	
	plt.title(title,fontsize=30)
	plt.xlabel('Процент недобудов',fontsize=30)
	plt.ylabel(LabelY,fontsize=30)
	plt.rcParams['font.size'] = '30'
	plt.tick_params(axis='both', which='major', labelsize=30)
	plt.legend()
	plt.savefig("Plot "+FileName)
	plt.clf()
	AverageX=[]
	AverageY=[]
	LegendTitles=[]
	EqualX={}
	for i in range(0,len(steps)):
		AverageValue=0		
		for j in range(0,len(predictions[i])):
			AverageValue+=predictions[i][j]
		AverageX.append(float(str("{:.2f}".format(float(AverageValue/len(predictions[i]))))))
		if(AverageX[i] not in EqualX):
			EqualX[int(AverageValue/len(predictions[i]))]=AverageX[i]
		AverageValue=0
		for j in range(0,len(ChangedDataForPrediction[i])):
			AverageValue+=float(ChangedDataForPrediction[i][ColumnName][j])
		AverageY.append(float(str("{:.2f}".format(float(AverageValue/len(ChangedDataForPrediction[i]))))))
		LegendTitles.append("step "+str(steps[i]))	
	while len(AverageY)>len(EqualX):
		AverageX.pop(0)
		AverageY.pop(0)
		LegendTitles.pop(0)
	fig, ax = plt.subplots()
	sns.barplot(x=AverageX,y=AverageY,label=LegendTitles)
	fig.set_size_inches(15,15)
	plt.rcParams['font.size'] = '30'
	plt.title(title,fontsize=30)
	plt.tick_params(axis='both', which='major', labelsize=30)
	plt.legend()
	ax.set_xlabel('Процент недобудов',fontsize=30)
	ax.set_ylabel(LabelY,fontsize=30)	
	plt.savefig("Barplot "+FileName)
	plt.clf()
DataForLearning=GetArrayFromLinesOfCSVFormat("DataForLearning.csv")
DataForPrediction=GetArrayFromLinesOfCSVFormat("DataForPrediction.csv")
DataFrameForLearning=pd.DataFrame(DataForLearning,columns=['Вулиця','Кількість недобудов на вулиці','№ буд.','Рік','Кількість недобудов за рік','Матеріали','Рейтинг матеріалів','Кількість поверхів','Висота стелі','Стан','Стан (bool)'])
DataFrameForPrediction=pd.DataFrame(DataForPrediction,columns=['Вулиця','Кількість недобудов на вулиці','№ буд.','Рік','Кількість недобудов за рік','Матеріали','Рейтинг матеріалів','Кількість поверхів','Висота стелі','Стан','Стан (bool)'])
y = DataFrameForLearning.iloc[:,10].values
DataFrameForLearning.drop(DataFrameForLearning.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
x = DataFrameForLearning.iloc[:,0:]
DataFrameForPrediction.drop(DataFrameForPrediction.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
x_train,x_test,y_train,y_test,=train_test_split(x,y,random_state=0)
BuildPlotOfPredictions(DataFrameForPrediction,x_train,x_test,y_train,y_test,[1,2,3],"Залежність процентної частки недобудов\nвід кількості незавершених об’єктів на вулиці","Кількість недобудов на вулиці","Середня кількість недобудов на вулиці","StreetRating")
BuildPlotOfPredictions(DataFrameForPrediction,x_train,x_test,y_train,y_test,[1,2,3],"Залежність процентної частки недобудовn\nвід кількості незавершених об’єктів за рік","Кількість недобудов за рік","Середня кількість недобудов за рік","YearRating")
BuildPlotOfPredictions(DataFrameForPrediction,x_train,x_test,y_train,y_test,[1,2,3],"Залежність процентної частки недобудов\nвід рейтингу матеріалів","Рейтинг матеріалів","Середній рейтинг матеріалів","MaterialRating")
BuildPlotOfPredictions(DataFrameForPrediction,x_train,x_test,y_train,y_test,[1,2,3],"Залежність процентної частки недобудов\nвід кількості поверхів","Кількість поверхів","Середня кількість поверхів","CountOfStoreys")
BuildPlotOfPredictions(DataFrameForPrediction,x_train,x_test,y_train,y_test,[1,2,3],"Залежність процентної частки недобудов\nвід висоти стелі","Висота стелі","Середня висота стелі","CeilingHeight")
StreetsDict={}
YearsDict={}
MaterialsDict={}
NumbersOfStoreysDict={}
HeightsOfCeilingsDict={}
StatesDict={}
for i in range(0,len(DataForLearning)):
	if(DataForLearning[i][10]==0):
		AddToDictionary(StreetsDict,DataForLearning[i][0])
		AddToDictionary(YearsDict,DataForLearning[i][3])
		for j in DataForLearning[i][5]:
			AddToDictionary(MaterialsDict,j)
		AddToDictionary(NumbersOfStoreysDict,DataForLearning[i][7])
		AddToDictionary(HeightsOfCeilingsDict,DataForLearning[i][8])
	AddToDictionary(StatesDict,DataForLearning[i][9])
for i in range(0,len(DataForPrediction)):
	AddToDictionary(StatesDict,DataForPrediction[i][9])
streets=LoadFromDictionaryToArray(StreetsDict)
years=LoadFromDictionaryToArray(YearsDict)
materials=LoadFromDictionaryToArray(MaterialsDict)
NumbersOfStoreys=LoadFromDictionaryToArray(NumbersOfStoreysDict)
HeightsOfCeilings=LoadFromDictionaryToArray(HeightsOfCeilingsDict)
states=LoadFromDictionaryToArray(StatesDict)
LogisticRegression = LogisticRegression(solver='lbfgs',random_state=0)
LogisticRegression.fit(x_train, y_train)
LogisticRegressionPredictions = LogisticRegression.predict(DataFrameForPrediction)
RandomForest = RandomForestClassifier()
RandomForest.fit(x_train,y_train)
RandomForestPredictions = RandomForest.predict(DataFrameForPrediction)
SupportVectorMachine = svm.SVC()
SupportVectorMachine.fit(x_train, y_train)
SupportVectorMachinePredictions = SupportVectorMachine.predict(DataFrameForPrediction)
LGStatesDict={}
RFStatesDict={}
SVMStatesDict={}
FileOfPredictions = open("predictions.csv", "w",encoding='utf-8-sig')
FileOfPredictions.write("Вулиця;Кількість недобудов на вулиці;№ буд.;Рік;Кількість недобудов за рік;Матеріали;Рейтинг матеріалів;Кількість поверхів;Висота стелі;Стан;Логістична регресія;Випадковий ліс;Метод опорних векторів\n")
for i in range(0,len(DataForPrediction)):
	FileLine=""	
	for j in range(0,len(DataForPrediction[i])):		
		FileLine=FileLine+str(DataForPrediction[i][j])+";"
	if(LogisticRegressionPredictions[i]==1):
		AddToDictionary(LGStatesDict,"Успіх")
		FileLine=FileLine[:len(FileLine)-2]+"Успіх;"		
	else:
		AddToDictionary(LGStatesDict,"Недобудова")
		FileLine=FileLine[:len(FileLine)-2]+"Недобудова;"
	if(RandomForestPredictions[i]==1):
		AddToDictionary(RFStatesDict,"Успіх")
		FileLine=FileLine+"Успіх;"
	else:
		AddToDictionary(RFStatesDict,"Недобудова")
		FileLine=FileLine+"Недобудова;"
	if(SupportVectorMachinePredictions[i]==1):
		AddToDictionary(SVMStatesDict,"Успіх")
		FileLine=FileLine+"Успіх\n"
	else:
		AddToDictionary(SVMStatesDict,"Недобудова")
		FileLine=FileLine+"Недобудова\n"
	FileOfPredictions.write(FileLine)
FileOfPredictions.close()
LGStates=LoadFromDictionaryToArray(LGStatesDict)
RFStates=LoadFromDictionaryToArray(RFStatesDict)
SVMStates=LoadFromDictionaryToArray(SVMStatesDict)
DrawHorizontalPlot(streets,"Статистика недобудов за вулицями","Statistic streets")
DrawHorizontalPlot(years,"Статистика недобудов за роками","Statistic years")
DrawHorizontalPlot(materials,"Статистика недобудов за використаними матеріалами","Statistic materials")
DrawHorizontalPlot(NumbersOfStoreys,"Статистика недобудов за кількістю поверхів","Statistic NumbersOfStoreys")
DrawHorizontalPlot(HeightsOfCeilings,"Статистика недобудов за висотою стелі","Statistic HeightsOfCeilings")
DrawHorizontalPlot(states,"Статистика недобудов за станом","Statistic states")
DrawPieChart(states,"Співвідношення зданих в експлутацію будівель та недобудов","Statistic states")
DrawPieChart(LGStates,"Спрогнозоване співвідношення зданих в експлутацію будівель та недобудов\n(логістична регресія)","Statistic logisticRegression")
DrawPieChart(RFStates,"Спрогнозоване співвідношення зданих в експлутацію будівель та недобудов\n(випадковий ліс)","Statistic RandomForest")
DrawPieChart(SVMStates,"Спрогнозоване співвідношення зданих в експлутацію будівель та недобудов\n(метод опорних векторів)","Statistic SupportVectorMachine")
print("The file predictions.csv was created")
print("Logistic regression accuracy: "+str(LogisticRegression.score(x_test,y_test)))
print("Random forest accuracy: "+str(RandomForest.score(x_test,y_test)))
print("Support vector machine accuracy: "+str(SupportVectorMachine.score(x_test,y_test)))