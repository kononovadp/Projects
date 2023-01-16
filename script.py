import pandas as pd
import numpy as np
from sklearn import preprocessing
import matplotlib.pyplot as plt
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
import seaborn as sns
from sklearn.ensemble import RandomForestClassifier
from sklearn import svm
def GetArrayFromLinesOfCSVFormat(lines):
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
DataForLearning=[]
SourceFile=open("DataForLearning.csv",'r',encoding='UTF8')
SourceFile.readline()
for line in SourceFile:
	DataForLearning.append(line)
SourceFile.close()
DataForPrediction=[]
SourceFile=open("DataForPrediction.csv",'r',encoding='UTF8')
SourceFile.readline()
for line in SourceFile:
	DataForPrediction.append(line)
SourceFile.close()
dfl=GetArrayFromLinesOfCSVFormat(DataForLearning)
dfp=GetArrayFromLinesOfCSVFormat(DataForPrediction)
# for i in range(0,20):
	# print("street: "+dfl[i][0]+"; street frequency: "+dfl[i][1]+" house number: "+dfl[i][2]+" year: "+dfl[i][3]+";\nyear frequency: "+dfl[i][4]+"; materials: ",end="")
	# for j in range(0,len(dfl[i][5])):
		# print(dfl[i][5][j]+",",end="")
	# print("rating of materials: "+dfl[i][6]+"; count of storeys: "+dfl[i][7]+"; height of ceiling: "+dfl[i][8]+"; state: "+dfl[i][9]+"; state (boolean): "+str(dfl[i][10]))
	# print("\n-----------------------------------------------------------------")
StreetsDict={}
YearsDict={}
MaterialsDict={}
NumbersOfStoreysDict={}
HeightsOfCeilingsDict={}
StatesDict={}
for i in range(0,len(dfl)):
	if(dfl[i][10]==0):
		AddToDictionary(StreetsDict,dfl[i][0])
		AddToDictionary(YearsDict,dfl[i][3])
		for j in dfl[i][5]:
			AddToDictionary(MaterialsDict,j)
		AddToDictionary(NumbersOfStoreysDict,dfl[i][7])
		AddToDictionary(HeightsOfCeilingsDict,dfl[i][8])
	AddToDictionary(StatesDict,dfl[i][9])
for i in range(0,len(dfp)):
	AddToDictionary(StatesDict,dfp[i][9])
streets=LoadFromDictionaryToArray(StreetsDict)
years=LoadFromDictionaryToArray(YearsDict)
materials=LoadFromDictionaryToArray(MaterialsDict)
NumbersOfStoreys=LoadFromDictionaryToArray(NumbersOfStoreysDict)
HeightsOfCeilings=LoadFromDictionaryToArray(HeightsOfCeilingsDict)
states=LoadFromDictionaryToArray(StatesDict)
df=pd.DataFrame(dfl,columns=['Вулиця','Кількість недобудов на вулиці','№ буд.','Рік','Кількість недобудов за рік','Матеріали','Рейтинг матеріалів','Кількість поверхів','Висота стелі','Стан','Стан (bool)'])
y =  df.iloc[:,10].values
df.drop(df.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
x = df.iloc[:,0:]
x_train, x_test, y_train, y_test = train_test_split(x,y,random_state=0)
lgc = LogisticRegression(solver='lbfgs',random_state=0)
lgc.fit(x_train, y_train)
dfp=pd.DataFrame(dfp,columns=['Вулиця','Кількість недобудов на вулиці','№ буд.','Рік','Кількість недобудов за рік','Матеріали','Рейтинг матеріалів','Кількість поверхів','Висота стелі','Стан','Стан (bool)'])
dfp.drop(dfp.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
LGPredictions = lgc.predict(dfp)
LGStatesDict={}
RFStatesDict={}
SVMStatesDict={}
rfc = RandomForestClassifier()
rfc.fit(x_train,y_train)
RFPredictions = rfc.predict(dfp)
SVM = svm.SVC()
SVM.fit(x_train, y_train)
SVMPredictions = SVM.predict(dfp)
f = open("predictions.csv", "w")
f.write("Вулиця;Кількість недобудов на вулиці;№ буд.;Рік;Кількість недобудов за рік;Матеріали;Рейтинг матеріалів;Кількість поверхів;Висота стелі;Стан;Логістична регресія;Випадковий ліс;Метод опорних векторів\n")
for i in range(0,len(DataForPrediction)):
	if(LGPredictions[i]==1):
		AddToDictionary(LGStatesDict,"Успіх")
		DataForPrediction[i]=DataForPrediction[i][:len(DataForPrediction[i])-1]+";Успіх"
	else:
		AddToDictionary(LGStatesDict,"Недобудова")
		DataForPrediction[i]=DataForPrediction[i][:len(DataForPrediction[i])-1]+";Недобудова"
	if(RFPredictions[i]==1):
		AddToDictionary(RFStatesDict,"Успіх")
		DataForPrediction[i]=DataForPrediction[i]+";Успіх"
	else:
		AddToDictionary(RFStatesDict,"Недобудова")
		DataForPrediction[i]=DataForPrediction[i]+";Недобудова"
	if(SVMPredictions[i]==1):
		AddToDictionary(SVMStatesDict,"Успіх")
		DataForPrediction[i]=DataForPrediction[i]+";Успіх\n"
	else:
		AddToDictionary(SVMStatesDict,"Недобудова")
		DataForPrediction[i]=DataForPrediction[i]+";Недобудова\n"
	f.write(DataForPrediction[i])
f.close()
LGStates=LoadFromDictionaryToArray(LGStatesDict)
RFStates=LoadFromDictionaryToArray(RFStatesDict)
SVMStates=LoadFromDictionaryToArray(SVMStatesDict)
DrawHorizontalPlot(streets,"Статистика недобудов за вулицями","streets")
DrawHorizontalPlot(years,"Статистика недобудов за роками","years")
DrawHorizontalPlot(materials,"Статистика недобудов за використаними матеріалами","materials")
DrawHorizontalPlot(NumbersOfStoreys,"Статистика недобудов за кількістю поверхів","NumbersOfStoreys")
DrawHorizontalPlot(HeightsOfCeilings,"Статистика недобудов за висотою стелі","HeightsOfCeilings")
DrawHorizontalPlot(states,"Статистика недобудов за станом","states")
DrawPieChart(states,"Співвідношення зданих в експлутацію будівель та недобудов","states")
DrawPieChart(LGStates,"Спрогнозоване співвідношення зданих в експлутацію будівель та недобудов\n(логістична регресія)","logistic regression")
DrawPieChart(RFStates,"Спрогнозоване співвідношення зданих в експлутацію будівель та недобудов\n(випадковий ліс)","random forest")
DrawPieChart(SVMStates,"Спрогнозоване співвідношення зданих в експлутацію будівель та недобудов\n(метод опорних векторів)","support vector machine")
print("The file predictions.csv was created")
print("Logistic regression accuracy: "+str(lgc.score(x_test,y_test)))
print("Random forest accuracy: "+str(rfc.score(x_test,y_test)))
print("Support vector machine accuracy: "+str(SVM.score(x_test,y_test)))