from pyspark.sql import SparkSession
from pyspark.sql.functions import *
from pyspark.sql.types import *
from graphframes import GraphFrame
from pyspark.sql.functions import radians, cos, sin, asin, sqrt, sum, split, lit
from pyspark.sql.functions import expr, col, when, desc, concat_ws, explode, count
from pyspark.sql.types import StructType, StructField, StringType, IntegerType, DoubleType, ArrayType
import shutil
import random
import pandas as pd
from tabulate import tabulate
import logging
import os
import sys
import math
from pyspark.ml.feature import StringIndexer, VectorAssembler
from pyspark.ml.classification import LogisticRegression, RandomForestClassifier
from pyspark.ml.clustering import KMeans, GaussianMixture, BisectingKMeans
from pyspark.ml.evaluation import MulticlassClassificationEvaluator, ClusteringEvaluator, BinaryClassificationEvaluator
from pyspark.ml import Pipeline
from pyspark.ml.tuning import ParamGridBuilder, CrossValidator
import matplotlib.pyplot as plt
import numpy as np
from sklearn.metrics import roc_curve, auc, confusion_matrix
from datetime import datetime
from datetime import timedelta
import matplotlib.ticker as ticker
from sklearn.preprocessing import label_binarize
def ConvertTimeDelta(duration):
    days, seconds = duration.days, duration.seconds
    hours = days * 24 + seconds // 3600
    minutes = (seconds % 3600) // 60
    seconds = (seconds % 60)
    return hours,minutes,seconds
    # return str(hours), str(minutes), str(seconds)
def DrawPlot(data,ticks,title,x_label,y_label):
	fig,ax=plt.subplots(figsize=(8,6))
	fig.suptitle(title)
	ax.set_xlabel(x_label)
	ax.set_ylabel(y_label)
	ax.xaxis.set_major_locator(ticker.MultipleLocator(base=len(ticks)))
	ax.xaxis.set_major_locator(ticker.FixedLocator([i for i in range(len(ticks))]))
	ax.set_xticklabels([ticks[i] for i in range(len(ticks))])
	plt.plot(data)
	plt.savefig("Plots\\"+title+".jpg",dpi=200)
	plt.close()
os.environ['PYSPARK_PYTHON'] = sys.executable
os.environ['PYSPARK_DRIVER_PYTHON'] = sys.executable
os.environ["HADOOP_HOME"] = "D:\\hadoop-3.2.1"
os.environ["PATH"] += os.pathsep + "D:\\hadoop-3.2.1\\bin"
csv_data_schema = StructType([
    StructField("Область", StringType(), True),
    StructField("Населений пункт", StringType(), True),
    StructField("Вулиця", StringType(), True),
    StructField("№ будинку", StringType(), True),
	StructField("Рік", IntegerType(), True),
	StructField("Матеріали", StringType(), True),
	StructField("Кількість поверхів", IntegerType(), True),
    StructField("Висота стелі", DoubleType(), True),
    StructField("Стан", StringType(), True)])
json_data_schema = StructType([
	StructField("Область", StructType([
		StructField("Назва", StringType(), True),
		StructField("Кількість недобудов", IntegerType(), True)]), True),
	StructField("Населений пункт", StructType([
		StructField("Назва", StringType(), True),
		StructField("Кількість недобудов", IntegerType(), True)]), True),
	StructField("Вулиця", StructType([
		StructField("Назва", StringType(), True),
		StructField("Кількість недобудов", IntegerType(), True)]), True),
	StructField("№ будинку", IntegerType(), True),
	StructField("Рік", StructType([
		StructField("Рік", IntegerType(), True),
		StructField("Кількість недобудов", IntegerType(), True)]), True),
	StructField("Матеріали", StructType([
		StructField("Назва", ArrayType(StringType()), True),
		StructField("Кількість недобудов", IntegerType(), True)]), True),
	StructField("Кількість поверхів", StructType([
		StructField("Кількість поверхів", IntegerType(), True),
		StructField("Кількість недобудов", IntegerType(), True)]), True),
	StructField("Висота стелі", DoubleType(), True),
	StructField("Стан", StructType([
		StructField("Стан", StringType(), True),
		StructField("Стан бінарний", IntegerType(), True)]), True)])
def WriteToJson(file_name):
	buildings = spark.read.csv(
		file_name+".csv",
		schema=csv_data_schema,
		header=True,
		encoding="Windows-1251",
		quote='"',
		escape='"',
		sep=";")
	# Крок 1: Перетворити колонку "Матеріали" на масив
	buildings = buildings.withColumn("Матеріали", split(col("Матеріали"), ","))
	# Крок 2: Виділити невдалі будівлі
	unsuccessful_buildings = buildings.filter((col("Стан") == "невдала будівля") | (col("Стан") == "призупинений"))
	# Крок 3: Розбити стовбець "Матеріали" у датасеті невдалих будинків
	exploded_bad_condition = unsuccessful_buildings.withColumn("Матеріал", explode(col("Матеріали")))
	# Крок 4: Порахувати, скільки разів зустрічається кожний матеріал у "невдалих" рядках
	material_ratings = exploded_bad_condition.groupBy("Матеріал").agg(count("*").alias("Матеріал Рейтинг"))
	# Крок 5: Розбити стовбець "Матеріали" у звичайному датасеті 
	exploded_buildings = buildings.withColumn("Матеріал", explode(col("Матеріали")))
	# Крок 6: # Приєднати рейтинги матеріалів до "розбитого" датасету
	enhanced_exploded_buildings = exploded_buildings.join(
		material_ratings, on="Матеріал", how="left"
	).withColumn("Матеріал Рейтинг", when(col("Матеріал Рейтинг").isNull(), 0).otherwise(col("Матеріал Рейтинг")))
	# Крок 7: Згрупувати все назад у попередні рядки
	buildings = enhanced_exploded_buildings.groupBy("Область", "Населений пункт", "Вулиця", "№ будинку", "Рік", "Матеріали", "Кількість поверхів", "Висота стелі", "Стан").agg(
		count("Матеріал").alias("Матеріал Рядки"),
		sum("Матеріал Рейтинг").alias("Рейтинг матеріалів"))  # Correct summation for materials
	# buildings = buildings.withColumn("Матеріали", split(buildings["Матеріали"], ",\\s*"))
	def add_column_with_count(buildings,base_column_name,new_column_name):	
		rating_df = unsuccessful_buildings.groupBy(base_column_name).count()
		rating_df = rating_df.withColumnRenamed("count", new_column_name)
		enhanced_buildings = buildings.join(rating_df,on=[base_column_name],how="left")
		return enhanced_buildings.withColumn(new_column_name,
			when(col(new_column_name).isNull(), 0).otherwise(col(new_column_name)))
	buildings = buildings.withColumn("Стан бінарний", when(col("Рік") < 2025,when((col("Стан") != "невдала будівля") & (col("Стан") != "призупинений"), 1).otherwise(0)).otherwise(2))
	buildings = add_column_with_count(buildings, "Область", "Рейтинг області")
	buildings = add_column_with_count(buildings, "Населений пункт", "Рейтинг населеного пункту")
	buildings = add_column_with_count(buildings, "Вулиця", "Рейтинг вулиці")
	buildings = add_column_with_count(buildings, "Рік", "Рейтинг року")
	buildings = add_column_with_count(buildings, "Кількість поверхів", "Рейтинг поверховості")
	buildings = buildings \
		.withColumn("Область", \
			struct(col("Область").alias("Назва"), \
			col("Рейтинг області").alias("Кількість недобудов"))) \
		.withColumn("Населений пункт", \
			struct(col("Населений пункт").alias("Назва"), \
			col("Рейтинг населеного пункту").alias("Кількість недобудов"))) \
		.withColumn("Вулиця", \
			struct(col("Вулиця").alias("Назва"), \
			col("Рейтинг вулиці").alias("Кількість недобудов"))) \
		.withColumn("Рік", \
			struct(col("Рік"), \
			col("Рейтинг року").alias("Кількість недобудов"))) \
		.withColumn("Матеріали", \
			struct(col("Матеріали").alias("Назва"), \
			col("Рейтинг матеріалів").alias("Кількість недобудов"))) \
		.withColumn("Кількість поверхів", \
			struct(col("Кількість поверхів"), \
			col("Рейтинг поверховості").alias("Кількість недобудов"))) \
		.withColumn("Стан", \
			struct(col("Стан"), \
			col("Стан бінарний"))) \
		.select("Область", "Населений пункт", "Вулиця",
			"№ будинку", "Рік", "Матеріали",
			"Кількість поверхів", "Висота стелі", "Стан")
	buildings.coalesce(1).write.json("temp", encoding="UTF-8", mode="overwrite")
	json_file = [f for f in os.listdir("temp") if f.endswith(".json")][0]
	shutil.move(os.path.join("temp", json_file), ""+file_name+".json")
	shutil.rmtree("temp")
def TestLogisticRegression(ROC_file_name):
	lr = LogisticRegression(featuresCol="features", labelCol="Стан бінарний", maxIter=10, regParam=0.01)
	model = lr.fit(train_df)
	predictions = model.transform(test_df)
	roc_auc = roc_evaluator.evaluate(predictions)
	training_summary = model.summary
	roc = training_summary.roc.toPandas()
	plt.figure(figsize=(6, 6))
	plt.plot(roc['FPR'], roc['TPR'], marker='o', linestyle='-', color='b', label=f'ROC Curve (AUC = {roc_auc:.4f})')
	plt.plot([0, 1], [0, 1], 'r--', label="Random Classifier (AUC = 0.5)")
	plt.xlabel("False Positive Rate")
	plt.ylabel("True Positive Rate")
	plt.title("ROC Curve - Logistic Regression")
	plt.legend()
	plt.grid()
	plt.savefig("Plots\\"+ROC_file_name, dpi=200)
	return accuracy_evaluator.evaluate(predictions)
def TestRandomForest():
	rf = RandomForestClassifier(featuresCol="features", labelCol="Стан бінарний", numTrees=10, seed=42)
	model = rf.fit(train_df)
	predictions = model.transform(test_df)
	return accuracy_evaluator.evaluate(predictions)
def TestKMeans():
	kmeans = KMeans(k=2, featuresCol="features", predictionCol="cluster")
	model = kmeans.fit(df_transformed)
	predictions = model.transform(df_transformed)
	evaluator = ClusteringEvaluator(featuresCol="features", predictionCol="cluster", metricName="silhouette")
	return evaluator.evaluate(predictions)
def TestGaussianMixture():
	gmm = GaussianMixture(featuresCol="features", predictionCol="gmm_prediction", k=2)
	gmm_pipeline = Pipeline(stages=[assembler, gmm])
	paramGrid = ParamGridBuilder().addGrid(gmm.k, [2, 3, 4, 5]).build()
	gmm_param_grid = ParamGridBuilder() \
		.addGrid(gmm.k, [2, 3, 4, 5]) \
		.build()
	gmm_crossval = CrossValidator(
		estimator=gmm_pipeline,
		estimatorParamMaps=paramGrid,
		evaluator=ClusteringEvaluator(predictionCol="gmm_prediction", metricName="silhouette"),
		numFolds=5)
	gmm_cv_model = gmm_crossval.fit(train_data)
	gmm_predictions = gmm_cv_model.bestModel.transform(test_data)
	gmm_silhouette = clustering_evaluator.evaluate(gmm_predictions.withColumnRenamed("gmm_prediction", "kmeans_prediction"))	
	return gmm_silhouette
def TestBisectingKMeans():
	bkm = BisectingKMeans().setK(3).setSeed(42).setFeaturesCol("features")
	model = bkm.fit(df_transformed)
	predictions = model.transform(df_transformed)
	evaluator = ClusteringEvaluator(predictionCol="prediction", featuresCol="features", metricName="silhouette")
	silhouette = evaluator.evaluate(predictions)
	return silhouette
sizes_of_datasets=[125000,250000,500000,1000000,2000000,4000000,8000000]
count_of_datasets=7
"""accuracies=[]
durations=[]
for i in range(4):
	accuracies.append([])
	durations.append([])
durations.append([])
feature_columns = ["Кількість недобудов в області",
				   "Кількість недобудов в населеному пункті",
				   "Кількість недобудов на вулиці",
				   "Кількість недобудов за рік",
				   "Кількість недобудов з матеріалами",
				   "Кількість недобудов з поверховістю"]
names_of_methods=["LOGISTIC REGRESSION", "RANDOM FOREST", "KMEANS", "BISECTING KMEANS"]
spark = SparkSession.builder \
	.master("local[*]") \
	.config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
	.config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
	.config('deploy-mode', 'cluster') \
	.config('spark.executor.cores', '4') \
	.config('spark.executor.memory', '4g') \
	.config('spark.driver.memory', '4g') \
	.config('spark.executor.memoryOverhead', '4g') \
	.config("spark.memory.fraction", "0.8") \
	.config('spark.driver.maxResultSize', '4g') \
	.config('spark.dynamicAllocation.enabled', 'true') \
	.config('spark.dynamicAllocation.minExecutors', '1') \
	.config('spark.dynamicAllocation.maxExecutors', '4') \
	.config('spark.dynamicAllocation.initialExecutors', '1') \
	.config('spark.executor.instances', '3') \
	.appName("GraphFramesExample") \
	.getOrCreate()
checkpoint_dir = "file:///D:/temp/spark-checkpoints"
spark.sparkContext.setCheckpointDir(checkpoint_dir)
start=datetime.now()
for i in range(1,8):
	WriteToJson("Dataset_"+str(i))
duration = datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print("\n\n----------TIME OF CONVERTING OF ALL DATASETS TO JSON: ",hours,":",minutes,":",seconds,"----------\n\n")"""

"""for i in range(count_of_datasets):
	start=datetime.now()
	buildings = spark.read \
	.option("encoding", "UTF-8") \
	.schema(json_data_schema) \
	.json("Dataset_"+str(i+1)+".json")
	buildings = buildings.select(
		col("Область.Кількість недобудов").alias("Кількість недобудов в області"),
		col("Населений пункт.Кількість недобудов").alias("Кількість недобудов в населеному пункті"),
		col("Вулиця.Кількість недобудов").alias("Кількість недобудов на вулиці"),
		col("Рік.Рік").alias("year"),
		col("Рік.Кількість недобудов").alias("Кількість недобудов за рік"),
		col("Матеріали.Кількість недобудов").alias("Кількість недобудов з матеріалами"),
		col("Кількість поверхів.Кількість недобудов").alias("Кількість недобудов з поверховістю"),
		col("Стан.Стан бінарний").alias("Стан бінарний")).filter(col("year") < 2025)
	accuracy_evaluator = MulticlassClassificationEvaluator(labelCol="Стан бінарний", predictionCol="prediction", metricName="accuracy")
	roc_evaluator = BinaryClassificationEvaluator(labelCol="Стан бінарний", rawPredictionCol="rawPrediction", metricName="areaUnderROC")
	vector_assembler = VectorAssembler(inputCols=feature_columns, outputCol="features")
	df_transformed = vector_assembler.transform(buildings)	
	train_df, test_df = df_transformed.randomSplit([0.8, 0.2], seed=42)
	evaluator = MulticlassClassificationEvaluator(labelCol="label", predictionCol="prediction", metricName="accuracy")
	clustering_evaluator = ClusteringEvaluator(predictionCol="kmeans_prediction", metricName="silhouette")
	train_data, test_data = buildings.randomSplit([0.8, 0.2], seed=42)
	
	# duration = timedelta(hours=0,minutes=random.randrange(5),seconds=random.randrange(60))
	duration = datetime.now()-start
	durations[0].append(duration)
	
	start=datetime.now()
	# accuracy = random.uniform(0.65, 0.99)
	accuracy = TestLogisticRegression("ROC of LR (dataset "+str(i+1)+").jpg")	
	# duration = timedelta(hours=0,minutes=random.randrange(5),seconds=random.randrange(60))
	duration = datetime.now()-start
	accuracies[0].append(accuracy)
	durations[1].append(duration)

	start=datetime.now()
	# accuracy = random.uniform(0.65, 0.99)
	accuracy = TestRandomForest()
	# duration = timedelta(hours=0,minutes=random.randrange(5),seconds=random.randrange(60))
	duration = datetime.now()-start
	accuracies[1].append(accuracy)
	durations[2].append(duration)

	start=datetime.now()
	# silhouette = random.uniform(0.65, 0.99)
	silhouette = TestKMeans()	
	# duration = timedelta(hours=0,minutes=random.randrange(5),seconds=random.randrange(60))
	duration = datetime.now()-start
	accuracies[2].append(silhouette)
	durations[3].append(duration)

	start=datetime.now()
	# silhouette = random.uniform(0.65, 0.99)
	silhouette = TestBisectingKMeans()
	# duration = timedelta(hours=0,minutes=random.randrange(5),seconds=random.randrange(60))
	duration = datetime.now()-start
	accuracies[3].append(silhouette)
	durations[4].append(duration)
	df_transformed.unpersist()
	buildings.unpersist()
for data_set_number in range(count_of_datasets):
	print("SIZE OF DATASET: ",sizes_of_datasets[data_set_number],end="; ")
	hours,minutes,seconds=ConvertTimeDelta(durations[0][data_set_number])
	print("TIME OF DATA PREPARATION: ",hours,":",minutes,":",seconds,"; COUNT OF SECONDS: ",f'{durations[0][data_set_number].total_seconds():.0f}')
	for i in range(4):
		print(names_of_methods[i]+" SCORE: ",f'{accuracies[i][data_set_number]:.5f}',end="; ")
		hours,minutes,seconds=ConvertTimeDelta(durations[i+1][data_set_number])
		print("TIME: ",hours,":",minutes,":",seconds,"; COUNT OF SECONDS: ",f'{durations[i+1][data_set_number].total_seconds():.0f}')
	for i in range(90):
		print(end="-")
	print()
print(end="Drawing plots...",flush=False)
data_preparing_durations=[]
for time in durations[0]:
	data_preparing_durations.append(time.total_seconds())
DrawPlot(data_preparing_durations,sizes_of_datasets,"TIME OF DATA PREPARATION","Count of rows in dataset","Time (total count of seconds)")
for method_number in range(4):
	DrawPlot(accuracies[method_number],sizes_of_datasets,names_of_methods[method_number]+" SCORE","Count of rows in dataset","Time (total count of seconds)")
	method_durations=[]
	for time in durations[method_number+1]:
		method_durations.append(time.total_seconds())
	DrawPlot(method_durations,sizes_of_datasets,names_of_methods[method_number]+" TIME OF CALCULATIONS","Count of rows in dataset","Time (total count of seconds)")
print(" Done.")"""


counts_of_cores=[1,2,3,4]
sizes_of_memory=[512,768,1024,1536,2048,4096]
all_durations=[]
all_durations.append([])
for count_of_cores in counts_of_cores:
	"""spark = SparkSession.builder \
	.master("local[*]") \
	.config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
	.config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
	.appName("GraphFramesExample") \
	.config('spark.executor.cores', count_of_cores) \
	.getOrCreate()"""
	spark = SparkSession.builder \
		.master("local[*]") \
		.config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
		.config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
		.config('deploy-mode', 'cluster') \
		.config('spark.executor.cores', count_of_cores) \
		.config('spark.executor.memory', '4g') \
		.config('spark.driver.memory', '4g') \
		.config('spark.executor.memoryOverhead', '4g') \
		.config("spark.memory.fraction", "0.8") \
		.config('spark.driver.maxResultSize', '4g') \
		.config('spark.dynamicAllocation.enabled', 'true') \
		.config('spark.dynamicAllocation.minExecutors', '1') \
		.config('spark.dynamicAllocation.maxExecutors', '4') \
		.config('spark.dynamicAllocation.initialExecutors', '1') \
		.config('spark.executor.instances', '3') \
		.appName("GraphFramesExample") \
		.getOrCreate()
	checkpoint_dir = "file:///D:/temp/spark-checkpoints"
	spark.sparkContext.setCheckpointDir(checkpoint_dir)
	durations=[]
	for data_set_number in range(count_of_datasets):
		start=datetime.now()
		WriteToJson("Dataset_"+str(data_set_number+1))
		duration=datetime.now()-start
		durations.append(duration)	
	spark.stop()	
	os.system("cls")
	all_durations[0].append(durations)
all_durations.append([])
for memory_size in sizes_of_memory:
	durations=[]
	"""spark = SparkSession.builder \
	.master("local[*]") \
	.config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
	.config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
	.appName("GraphFramesExample") \
	.config('spark.executor.memory', str(memory_size)+'m') \
	.config('spark.executor.memoryOverhead', str(memory_size)+'m') \
	.config('spark.driver.memory', str(memory_size*2)+'m') \
	.config('spark.driver.maxResultSize', str(memory_size)+'m') \
	.getOrCreate()"""
	spark = SparkSession.builder \
		.master("local[*]") \
		.config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
		.config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
		.config('deploy-mode', 'cluster') \
		.config('spark.executor.cores', '4') \
		.config('spark.executor.memory', str(memory_size)+'m') \
		.config('spark.driver.memory', str(memory_size*2)+'m') \
		.config('spark.executor.memoryOverhead', str(memory_size)+'m') \
		.config("spark.memory.fraction", "0.8") \
		.config('spark.driver.maxResultSize', str(memory_size)+'m') \
		.config('spark.dynamicAllocation.enabled', 'true') \
		.config('spark.dynamicAllocation.minExecutors', '1') \
		.config('spark.dynamicAllocation.maxExecutors', '4') \
		.config('spark.dynamicAllocation.initialExecutors', '1') \
		.config('spark.executor.instances', '3') \
		.appName("GraphFramesExample") \
		.getOrCreate()
	checkpoint_dir = "file:///D:/temp/spark-checkpoints"
	spark.sparkContext.setCheckpointDir(checkpoint_dir)
	for data_set_number in range(count_of_datasets):
		start=datetime.now()
		WriteToJson("Dataset_"+str(data_set_number+1))
		duration=datetime.now()-start
		durations.append(duration)
	spark.stop()
	os.system("cls")	
	all_durations[1].append(durations)
for i in range(4):
	print("Count of cores: ",i+1)
	for data_set_number in range(count_of_datasets):
		hours,minutes,seconds=ConvertTimeDelta(all_durations[0][i][data_set_number])
		print("Size of dataset: ",sizes_of_datasets[data_set_number],end="; ")
		print("time: ",hours,":",minutes,":",seconds,"; total count of seconds: ",all_durations[0][i][data_set_number].total_seconds())
for i in range(90):
	print(end="=")
print()
for i in range(6):
	print("Memory size: ",sizes_of_memory[i])
	for data_set_number in range(count_of_datasets):
		hours,minutes,seconds=ConvertTimeDelta(all_durations[1][i][data_set_number])
		print("Size of dataset: ",sizes_of_datasets[data_set_number],end="; ")
		print("time: ",hours,":",minutes,":",seconds,"; total count of seconds: ",all_durations[1][i][data_set_number].total_seconds())
print(end="Drawing plots...",flush=False)
for i in range(4):
	durations=[]
	for time in all_durations[0][i]:
		durations.append(time.total_seconds())
	DrawPlot(durations,sizes_of_datasets,"Count of cores "+str(i+1),"Count of rows in dataset","Time (total count of seconds)")
for i in range(6):
	durations=[]
	for time in all_durations[1][i]:
		durations.append(time.total_seconds())
	DrawPlot(durations,sizes_of_datasets,"Memory size "+str(sizes_of_memory[i]),"Count of rows in dataset","Time (total count of seconds)")
print(" Done.")

# DrawPlot(durations)
# buildings.select("Рік", "Стан", "Стан бінарний").toPandas().to_csv(sep=";",path_or_buf="test.csv")
# buildings.printSchema()
# buildings.show(truncate=False)
# pd_buildings=buildings.toPandas()
# table=tabulate(pd_buildings, headers='keys', tablefmt='grid')
# with open("buildings.txt", encoding="Windows-1251", mode='w') as f:
	# f.write(table)