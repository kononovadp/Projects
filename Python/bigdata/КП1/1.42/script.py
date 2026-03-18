from pyspark.sql import SparkSession
from pyspark.sql.functions import *
from pyspark.sql.types import *
from graphframes import GraphFrame
from pyspark.sql.functions import radians, cos, sin, asin, sqrt, sum, col
from pyspark.sql.functions import expr, col, sum as _sum, desc
from pyspark.sql import functions as F
from pyspark.sql.window import Window
from random import randrange
from tabulate import tabulate
import geopy.distance
import os
import sys
import math
os.environ['PYSPARK_PYTHON'] = sys.executable
os.environ['PYSPARK_DRIVER_PYTHON'] = sys.executable
spark = SparkSession.builder \
    .master("local[*]") \
    .config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
    .config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
    .appName("GraphFramesExample") \
    .getOrCreate()
# Завантаження даних з файлів
airports_path = "airports-extended.dat"
airlines_path = "airlines.dat"
routes_path = "routes.dat"
# Схеми даних
airports_schema = "id INT, name STRING, city STRING, country STRING, iata STRING, icao STRING, latitude DOUBLE, longitude DOUBLE, altitude INT, timezone DOUBLE, dst STRING, tz STRING, type STRING, source STRING"
airlines_schema = "id INT, name STRING, alias STRING, iata STRING, icao STRING, callsign STRING, country STRING, active STRING"
routes_schema = "airline STRING, airline_id INT, source_airport STRING, source_airport_id INT, destination_airport STRING, destination_airport_id INT, codeshare STRING, stops INT, equipment STRING"
# Читання даних
airports_df = spark.read.csv(airports_path, schema=airports_schema, header=False)
airlines_df = spark.read.csv(airlines_path, schema=airlines_schema, header=False)
routes_df = spark.read.csv(routes_path, schema=routes_schema, header=False)
# Обчислення відстані між двома точками за координатами (Haversine formula)
def haversine(lat1, lon1, lat2, lon2):
    R = 6371  # Радіус Землі в кілометрах
    dlat = math.radians(lat2 - lat1)
    dlon = math.radians(lon2 - lon1)
    a = math.sin(dlat / 2) ** 2 + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(dlon / 2) ** 2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    return R * c
haversine_udf = udf(lambda lat1, lon1, lat2, lon2: haversine(lat1, lon1, lat2, lon2) if lat1 and lon1 and lat2 and lon2 else None, DoubleType())
# Додавання відстані до маршрутів
routes_with_distance_df = routes_df \
    .join(airports_df.select(col("iata").alias("source_iata"), col("latitude").alias("source_lat"), col("longitude").alias("source_lon")), routes_df.source_airport == col("source_iata")) \
    .join(airports_df.select(col("iata").alias("dest_iata"), col("latitude").alias("dest_lat"), col("longitude").alias("dest_lon")), routes_df.destination_airport == col("dest_iata")) \
    .withColumn("distance", haversine_udf(col("source_lat"), col("source_lon"), col("dest_lat"), col("dest_lon")))
# Побудова графу
vertices = airports_df.select(col("iata").alias("id"), "name", "city", "country")
edges = routes_with_distance_df.select(col("source_airport").alias("src"), col("destination_airport").alias("dst"), "distance")
graph = GraphFrame(vertices, edges)
source_airport = 507#3797#507
destination_airport = 2939#146#8600#randrange(0,10667) #2939

source_airport_name = airports_df.select("name").filter(f"id = '{source_airport}'").collect()[0][0]
destination_airport_name = airports_df.select("name").filter(f"id = '{destination_airport}'").collect()[0][0]

source_airport_id = airports_df.select("iata").filter(f"id = '{source_airport}'").collect()[0][0]
destination_airport_id = airports_df.select("iata").filter(f"id = '{destination_airport}'").collect()[0][0]


def printAllPathsUtil(u, d, visited, path):
	# source_airport_id = int(airports_df.select("id").filter(f"id = '{u}'").collect()[0][0])
	# destination_airport_id = int(airports_df.select("id").filter(f"id = '{d}'").collect()[0][0])
	visited[u]= True	
	path.append(u)
	if u == d:
		print (path)
	else:
		j=0
		for i in vertices.collect():
			vid=int(airports_df.select("id").collect()[0][0])
			if visited[vid]== False:
				# src=int(airports_df.select("id").filter(f"id = '{vid}'").collect()[0][0])
				printAllPathsUtil(vid, d, visited, path)
			j+=1
	path.pop()
	visited[u]= False

def printAllPaths(s, d):
	visited =[False]*100000
	path = []
	printAllPathsUtil(s, d, visited, path)

printAllPaths(source_airport, destination_airport)