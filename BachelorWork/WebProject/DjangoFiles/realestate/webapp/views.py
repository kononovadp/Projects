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
from sklearn.ensemble import RandomForestClassifier
from sklearn import svm
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
def GetDataFrameFromLinesOfCSVFormat(lines):
	arr=[]
	LineNumber=0
	j=0
	for i in range(1,len(lines)):
		line=lines[i]
	# for line in lines:
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
	return pd.DataFrame(arr,columns=['Вулиця','Кількість недобудов на вулиці','№ буд.','Рік','Кількість недобудов за рік','Матеріали','Рейтинг матеріалів','Кількість поверхів','Висота стелі','Стан','Стан (bool)'])
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
def GetBestPredictions(DataForPrediction,x_train, x_test, y_train, y_test):
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
def predict(request):
	DataForLearning=GetDataFrameFromLinesOfCSVFormat(request.POST.getlist('DataForLearning[]'))
	DataForPrediction=GetDataFrameFromLinesOfCSVFormat(request.POST.getlist('DataForPrediction[]'))
	y = DataForLearning.iloc[:,10].values
	DataForLearning.drop(DataForLearning.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
	x = DataForLearning.iloc[:,0:]
	DataForPrediction.drop(DataForPrediction.columns[[0,2,3,5,9,10]],axis=1,inplace=True)
	x_train, x_test, y_train, y_test = train_test_split(x,y,random_state=0)
	predictions=GetBestPredictions(DataForPrediction,x_train, x_test, y_train, y_test)
	PredictedStatesDict={}
	results=[]
	for i in range(0,len(predictions)):
		if(predictions[i]==1):
			AddToDictionary(PredictedStatesDict,"Успіх")
			results.append("Успіх")
		else:
			AddToDictionary(PredictedStatesDict,"Недобудова")
			results.append("Недобудова")
	PredictedStates=LoadFromDictionaryToArray(PredictedStatesDict)
	return JsonResponse({"data": results})