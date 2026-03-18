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
spark = SparkSession.builder \
    .master("local[*]") \
    .config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
    .config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
    .appName("GraphFramesExample") \
    .getOrCreate()
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
count_of_transfers=5#random.randrange(4,10)
random_motif=""   #"(a)-[e1]->(b); (b)-[e2]->(c); (c)-[e3]->(d); (d)-[e4]->(e)"
for i in range(count_of_transfers):
	random_motif=random_motif+"("+chr(ord("a")+i)+")-[e"+chr(ord("1")+i)+"]->("+chr(ord("a")+i+1)+"); "
random_motif=random_motif[:len(random_motif)-2]+""
attribute_numbers=[i for i in range(count_of_transfers)]
for i in range(count_of_transfers):
	t=attribute_numbers[i]
	j=random.randrange(0,count_of_transfers)
	attribute_numbers[i]=attribute_numbers[j]
	attribute_numbers[j]=t
source_index=chr(ord('a')+attribute_numbers[0])
destination_index=chr(ord('a')+attribute_numbers[1])
paths = graph.find(random_motif)
filtered_paths = paths.filter(col("a.country") == "Brazil")
path = filtered_paths.sample(withReplacement=False, fraction=0.000001).limit(1).collect()[0]
source=graph.vertices.filter(col("name") == path[source_index].name).collect()[0]
destination=graph.vertices.filter(col("name") == path[destination_index].name).collect()[0]

# source_id="CGR"#"LGW"
# destination_id="MAO"#"UIO"
# source=graph.vertices.filter(col("id") == source_id).collect()[0]
# destination=graph.vertices.filter(col("id") == destination_id).collect()[0]
all_paths = graph.bfs(
    fromExpr=f"id = '{source['id']}'",
    toExpr=f"id = '{destination['id']}'",
    maxPathLength=5
)
os.system("cls")
#############################################################################################
for i in range(38):
	print(end='#')
print(end="START OF INPUT")
for i in range(38):
	print(end='#')
# print("\nRANDOM MOTIF: ",random_motif)
# print("\nCOUNT OF FILTERED PATHS:",paths.count())
print("\nSOURCE AIRPORT: ",source["name"],";\nID: ",source["id"],"; COUNTRY: ",source["country"])
for i in range(90):
	print(end='-')
print("\nDESTINATION AIRPORT: ",destination["name"],";\nID: ",destination["id"],"; COUNTRY: ",destination["country"])
for i in range(90):
	print(end='-')
print()
if all_paths.count()>0:
	paths = all_paths.collect()
	shortest_distance = 100000	
	shortest_path = []
	shortest_distances = []
	longest_distance = 0
	longest_path = []
	longest_distances = []
	for p in paths:
		distance=0
		path=[]
		distances=[]
		for row in p:			
			for column, value in row.asDict().items():
				if column=='src' or column=='dst':
					path.append(value)
				else:
					if column=='distance':
						distance+=value
						distances.append(value)
		print("COMMON DISTANCE: ",f'{distance:.3f} KM; PATH:')
		j=0
		for i in range(0,len(path),2):
			print(path[i]," - ",path[i+1],": ",f'{distances[j]:.3f} KM')
			j+=1
		for i in range(90):
			print(end='-')
		print()
		if distance<shortest_distance:
			shortest_distance=distance
			shortest_path=path
			shortest_distances=distances
		if distance>longest_distance:
			longest_distance=distance
			longest_path=path
			longest_distances=distances
	print("\nTHE SHORTEST DISTANCE: ",f'{shortest_distance:.3f} KM; PATH:')
	j=0
	for i in range(0,len(shortest_path),2):
		print(shortest_path[i]," - ",shortest_path[i+1],": ",f'{shortest_distances[j]:.3f} KM')
		j+=1
	print("THE LONGEST DISTANCE: ",f'{longest_distance:.3f} KM; PATH:')
	j=0
	for i in range(0,len(longest_path),2):
		print(longest_path[i]," - ",longest_path[i+1],": ",f'{longest_distances[j]:.3f} KM')
		j+=1
else:
	print("THERE IS NO PATH")
for i in range(39):
	print(end='#')
print(end="END OF INPUT")
for i in range(39):
	print(end='#')
print()