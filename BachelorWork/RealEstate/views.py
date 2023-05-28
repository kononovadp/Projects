from django.shortcuts import render
from django.http import HttpResponse
from django.http import HttpResponseRedirect
from django.http import JsonResponse
from django.core import serializers
import psycopg2
from psycopg2.extensions import ISOLATION_LEVEL_AUTOCOMMIT
import pandas as pd
import numpy as np
from sklearn import preprocessing
import matplotlib.pyplot as plt
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
import seaborn as sns
def GetRequestResult(request):
	connection = psycopg2.connect(user="sqluser",password="5353A201",host="127.0.0.1",port="5432",database="realestate")
	connection.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
	cursor = connection.cursor()
	cursor.execute(request)
	records = cursor.fetchall()
	cursor.close()
	connection.close()
	return records
def PageStarted(request):	
	records=GetRequestResult("SELECT * from \"Області\"")
	AllData=[]
	for record in records:
		AllData.append(record[0])
	return render(request,"index.html",{"districts": AllData})
def GetOneColumn(request):
	records=GetRequestResult(request.POST['request'])
	AllData=[]
	for record in records:
		AllData.append(record[int(request.POST['ColumnNumber'])])
	return JsonResponse({"data": AllData})
def GetSeveralColumns(request):
	data=GetRequestResult(request.POST['request'])
	AllData=[]
	for record in data:		
		row=[]
		for i in range(int(request.POST['FirstColumnIndex']),int(request.POST['CountOfColumns'])):
			row.append(record[i])
		AllData.append(row)
	return JsonResponse({"data": AllData})
def UpdateDatabase(request):
	connection = psycopg2.connect(user="sqluser",password="5353A201",host="127.0.0.1",port="5432",database="realestate")
	connection.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
	cursor = connection.cursor()
	houses = request.POST.getlist('data[]')
	for house in houses:
		i=0
		while(house[i]!=';'):
			i+=1
		street=house[:i]
		i+=1
		PrevI=i	
		while(house[i]!=';'):
			i+=1
		HouseNumber=house[PrevI:i]
		i+=1
		PrevI=i	
		while(house[i]!=';'):
			i+=1
		year=house[PrevI:i]
		if(len(year)==0):
			year="null"
		i+=1
		PrevI=i
		materials=[]
		while(house[i]!=';'):		
			while(house[i]!=',' and house[i]!=';'):
				i+=1
			materials.append(house[PrevI:i])
			if(house[i]==';'):
				break
			i+=1
			PrevI=i
		i+=1
		PrevI=i
		while(house[i]!=';'):
			i+=1
		NumberOfStoreys=house[PrevI:i]
		if(len(NumberOfStoreys)==0):
			NumberOfStoreys="null"
		i+=1
		PrevI=i
		while(house[i]!=';'):
			i+=1
		CeilingHeight=house[PrevI:i]
		if(len(CeilingHeight)==0):
			CeilingHeight="null"
		i+=1
		PrevI=i
		while(house[i]!=';' and i<len(house)):
			i+=1
		state=house[PrevI:i]
		cursor.execute("select from Будинки where \"Область\"='"+request.POST['district']+"' and \"Населений пункт\"='"+request.POST['town']+"' and \"Вулиця\"='"+street+"' and \"№ будинку\"='"+HouseNumber+"';")
		data = cursor.fetchall()
		if len(data)>0:
			query="update Будинки set \"Рік будівництва\"="+year+",\"Матеріали\"='{"
			for j in range(0,len(materials)):
				query=query+"\""+materials[j]+"\",";
			if(len(materials)>0):
				query=query[0:len(query)-1]
			query=query+"}',\"Кількість поверхів\"="+NumberOfStoreys+",\"Висота стелі\"="+CeilingHeight+",\"Стан\"='"+state+"' where \"Область\"='"+request.POST['district']+"' and \"Населений пункт\"='"+request.POST['town']+"' and \"Вулиця\"='"+street+"' and \"№ будинку\"='"+HouseNumber+"';";
			cursor.execute(query)
		else:
			query="INSERT INTO Будинки(\"Область\",\"Населений пункт\",\"Вулиця\",\"№ будинку\",\"Рік будівництва\",\"Матеріали\",\"Кількість поверхів\",\"Висота стелі\",\"Стан\") Values ('"+request.POST['district']+"','"+request.POST['town']+"','"+street+"','"+HouseNumber+"',"+year+",'{"
			for j in range(0,len(materials)):
				query=query+"\""+materials[j]+"\",";
			if(len(materials)>0):
				query=query[0:len(query)-1]
			query=query+"}',"+NumberOfStoreys+","+CeilingHeight+",'"+state+"');";
			cursor.execute(query)
	connection.commit()
	cursor.close()
	connection.close()
	return JsonResponse({"data": "success"})
def DeleteFromDatabase(request):
	connection = psycopg2.connect(user="sqluser",password="5353A201",host="127.0.0.1",port="5432",database="realestate")
	connection.set_isolation_level(ISOLATION_LEVEL_AUTOCOMMIT)
	cursor = connection.cursor()
	houses = request.POST.getlist('data[]')
	for house in houses:
		i=0
		while(house[i]!=';'):
			i+=1
		street=house[:i]
		i+=1
		PrevI=i	
		while(house[i]!=';' and i<len(house)):
			i+=1
		HouseNumber=house[PrevI:i]
		cursor.execute("select from Будинки where \"Область\"='"+request.POST['district']+"' and \"Населений пункт\"='"+request.POST['town']+"' and \"Вулиця\"='"+street+"' and \"№ будинку\"='"+HouseNumber+"';")
		data = cursor.fetchall()
		if len(data)>0:
			cursor.execute("delete from Будинки where \"Область\"='"+request.POST['district']+"' and \"Населений пункт\"='"+request.POST['town']+"' and \"Вулиця\"='"+street+"' and \"№ будинку\"='"+HouseNumber+"';")
	connection.commit()
	cursor.close()
	connection.close()
	return JsonResponse({"data": "success"})
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
def PredictUsingLogisticRegression(request):
	dfl=GetArrayFromLinesOfCSVFormat(request.POST.getlist('DataForLearning[]'))
	dfp=GetArrayFromLinesOfCSVFormat(request.POST.getlist('DataForPrediction[]'))
	# for i in range(0,20):
		# print(request.POST['DataForLearning[]'][i]+"\n=================================================")
		# print("street: "+dfl[i][0]+"; street frequency:|"+dfl[i][1]+"| house number: "+dfl[i][2]+" year: "+dfl[i][3]+";\nyear frequency: "+dfl[i][4]+"; materials: ",end="")
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
	DrawHorizontalPlot(streets,"Статистика недобудов за вулицями","streets")
	DrawHorizontalPlot(years,"Статистика недобудов за роками","years")
	DrawHorizontalPlot(materials,"Статистика недобудов за використаними матеріалами","materials")
	DrawHorizontalPlot(NumbersOfStoreys,"Статистика недобудов за кількістю поверхів","NumbersOfStoreys")
	DrawHorizontalPlot(HeightsOfCeilings,"Статистика недобудов за висотою стелі","HeightsOfCeilings")
	DrawHorizontalPlot(states,"Статистика недобудов за станом","states")
	DrawPieChart(states,"Співвідношення зданих в експлутацію будівель та недобудов","states")
	df=pd.DataFrame(dfl,columns=['Вулиця','Кількість недобудов на вулиці','№ буд.','Рік','Кількість недобудов за рік','Матеріали','Рейтинг матеріалів','Кількість поверхів','Висота стелі','Стан','Стан (bool)'])
	y =  df.iloc[:,10].values
	df.drop(df.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
	x = df.iloc[:,0:]
	X_train, X_test, Y_train, Y_test = train_test_split(x,y,random_state=0)
	classifier = LogisticRegression(solver='lbfgs',random_state=0)
	classifier.fit(X_train, Y_train)
	dataforpred=pd.DataFrame(dfp,columns=['Вулиця','Кількість недобудов на вулиці','№ буд.','Рік','Кількість недобудов за рік','Матеріали','Рейтинг матеріалів','Кількість поверхів','Висота стелі','Стан','Стан (bool)'])
	dataforpred.drop(dataforpred.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
	predicted_y = classifier.predict(dataforpred)
	PredictedStatesDict={}
	results=[]
	for prediction in predicted_y:
		if(prediction==1):
			AddToDictionary(PredictedStatesDict,"Успіх")
			results.append("Успіх")
		else:
			AddToDictionary(PredictedStatesDict,"Недобудова")
			results.append("Недобудова")
	PredictedStates=LoadFromDictionaryToArray(PredictedStatesDict)
	DrawPieChart(PredictedStates,"Спрогнозоване співвідношення зданих в експлутацію будівель та недобудов","PredictedStates")
	return JsonResponse({"data": results})
	#--------------------the solution without in-build functions--------------------
	# predictions=[]
	# error=[]
	# err=0
	# b0 = 0
	# b1 = 0
	# b2 = 0
	# alpha = 0.01
	# e = 2.71828
	# for i in range(0,len(dfl)*4):
		# idx=i%10
		# p=-(b0 + b1 * int(dfl[idx][4])+ b2* float(dfl[idx][5]))
		# pred  = 1/(1+ pow(e,p))
		# err = int(dfl[idx][6])-pred
		# b0 = b0 - alpha * err*pred *(1-pred)* 1.0
		# b1 = b1 + alpha * err * pred*(1-pred) *int(dfl[idx][4])
		# b2 = b2 + alpha * err * pred*(1-pred) *float(dfl[idx][5])
		# error.append(err)
	# TestValue=float("{:.2f}".format(b0+b1*int(dfp[0][4])+b2*float(dfp[0][5])))
	# for i in range(0,len(dfp)):
		# pred=b0+b1*int(dfp[i][4])+b2*float(dfp[i][5])
		# if(pred>=TestValue):
			# predictions.append("Вдала будівля");
		# else:
			# predictions.append("Недобудова");