from pyspark.sql import SparkSession
from pyspark.sql.functions import *
from pyspark.sql.types import *
from graphframes import GraphFrame
from pyspark.sql.functions import radians, cos, sin, asin, sqrt, sum, col
from pyspark.sql.functions import expr, col, sum as _sum, desc, concat_ws
import random
from tabulate import tabulate
import logging
import os
import sys
import math
os.environ['PYSPARK_PYTHON'] = sys.executable
os.environ['PYSPARK_DRIVER_PYTHON'] = sys.executable
os.environ["HADOOP_HOME"] = "D:\\hadoop-3.2.1"
os.environ["PATH"] += os.pathsep + "D:\\hadoop-3.2.1\\bin"
spark = SparkSession.builder \
    .master("local[*]") \
    .config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
    .config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
    .appName("GraphFramesExample") \
    .getOrCreate()
checkpoint_dir = "file:///D:/temp/spark-checkpoints"
spark.sparkContext.setCheckpointDir(checkpoint_dir)
airports_path = "airports-extended.dat"
airlines_path = "airlines.dat"
routes_path = "routes.dat"
airports_schema = "id INT, name STRING, city STRING, country STRING, iata STRING, icao STRING, latitude DOUBLE, longitude DOUBLE, altitude INT, timezone DOUBLE, dst STRING, tz STRING, type STRING, source STRING"
airlines_schema = "id INT, name STRING, alias STRING, iata STRING, icao STRING, callsign STRING, country STRING, active STRING"
routes_schema = "airline STRING, airline_id INT, source_airport STRING, source_airport_id INT, destination_airport STRING, destination_airport_id INT, codeshare STRING, stops INT, equipment STRING"
airports_df = spark.read.csv(airports_path, schema=airports_schema, header=False)
airlines_df = spark.read.csv(airlines_path, schema=airlines_schema, header=False)
routes_df = spark.read.csv(routes_path, schema=routes_schema, header=False)
def haversine(lat1, lon1, lat2, lon2):
    R = 6371  # Радіус Землі в кілометрах
    dlat = math.radians(lat2 - lat1)
    dlon = math.radians(lon2 - lon1)
    a = math.sin(dlat / 2) ** 2 + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(dlon / 2) ** 2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    return R * c
haversine_udf = udf(lambda lat1, lon1, lat2, lon2: haversine(lat1, lon1, lat2, lon2) if lat1 and lon1 and lat2 and lon2 else None, DoubleType())
routes_with_distance_df = routes_df \
    .join(airports_df.select(col("iata").alias("source_iata"), col("latitude").alias("source_lat"), col("longitude").alias("source_lon")), routes_df.source_airport == col("source_iata")) \
    .join(airports_df.select(col("iata").alias("dest_iata"), col("latitude").alias("dest_lat"), col("longitude").alias("dest_lon")), routes_df.destination_airport == col("dest_iata")) \
    .withColumn("distance", haversine_udf(col("source_lat"), col("source_lon"), col("dest_lat"), col("dest_lon")))
vertices = airports_df.select(col("iata").alias("id"), "name", "city", "country")
edges = routes_with_distance_df.select(col("source_airport").alias("src"), col("destination_airport").alias("dst"), "distance")
graph = GraphFrame(vertices, edges)
#############################################################################################
result = graph.labelPropagation(maxIter=5)
# Об'єднуємо label до вершин з правильним визначенням колонок
vertices_with_labels = graph.vertices.join(result, graph.vertices.id == result.id).select(graph.vertices.id, graph.vertices.name, result.label)
# Знаходимо кількость аеропортів у кожному кластері
label_counts = vertices_with_labels.groupBy("label").count()
# Сортуємо та отримуємо тільки 5 найбільших
large_clusters = label_counts.filter(col("count") >= 5).orderBy("count", ascending=False).limit(5)
large_cluster_labels = [row["label"] for row in large_clusters.collect()]
large_cluster_airports = vertices_with_labels.filter(col("label").isin(large_cluster_labels))
os.system("cls")
for label in large_cluster_labels:	
	airports_in_cluster = large_cluster_airports.filter(col("label") == label)
	count_of_airports_in_clusters=airports_in_cluster.count()
	print("COUNT OF AIRPORTS IN CLUSTER ",label,": ",count_of_airports_in_clusters)
	if(count_of_airports_in_clusters<1000):
		pd_airports_in_cluster=airports_in_cluster.toPandas()
		table=tabulate(pd_airports_in_cluster, headers='keys', tablefmt='grid')
		with open("airport_tables.txt", encoding="utf-8", mode='a') as f:
			f.write(table)
	# airports_in_cluster.select("id", "name").show(5)