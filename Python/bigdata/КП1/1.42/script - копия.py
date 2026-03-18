from pyspark.sql import SparkSession
from pyspark.sql.functions import *
from pyspark.sql.types import *
from graphframes import GraphFrame
from pyspark.sql.functions import radians, cos, sin, asin, sqrt
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

# # Load data
# airports_path = "airports-extended.dat"
# routes_path = "routes.dat"

# # Read data into DataFrames
# airports = spark.read.csv(airports_path, inferSchema=True, header=False)
# routes = spark.read.csv(routes_path, inferSchema=True, header=False)

# Створення схеми
schema = StructType([
    StructField("id", IntegerType(), True),
    StructField("name", StringType(), True),
    StructField("city", StringType(), True),
    StructField("country", StringType(), True),
    StructField("iata", StringType(), True),
    StructField("icao", StringType(), True),
    StructField("latitude", StringType(), True),
    StructField("longitude", StringType(), True),
    StructField("altitude", StringType(), True),
    StructField("timezone", StringType(), True),
    StructField("dst", StringType(), True),
    StructField("tzdb", StringType(), True),
    StructField("type", StringType(), True),
    StructField("source", StringType(), True)
])
schema1 = StructType([
    StructField("id", StringType(), True),
    StructField("airline", StringType(), True),
    StructField("airline_id", StringType(), True),
    StructField("srcairport", StringType(), True),
    StructField("srcairport_id", StringType(), True),
    StructField("dstairport", StringType(), True),
    StructField("dstairport_id", StringType(), True),
    StructField("code_share", StringType(), True),
    StructField("stops", StringType(), True),
    StructField("equipement", StringType(), True)
])
schema2 = StructType([
    StructField("id", StringType(), True),
    StructField("name", StringType(), True),
    StructField("alias", StringType(), True),
    StructField("iata", StringType(), True),
    StructField("icao", StringType(), True),
    StructField("callsign", StringType(), True),
    StructField("country", StringType(), True),
    StructField("active", StringType(), True)
])
# Завантаження даних в DataFrame
airports_df = spark.read.option("delimiter", ",").csv("airports-extended.dat", header=False, schema=schema)
airlines_df = spark.read.option("delimiter", ",").csv("airlines.dat", header=False, schema=schema1)
routes_df = spark.read.option("delimiter", ",").csv("routes.dat", header=False, schema=schema2)


# перевірка
# poland_airports.show(5)
# belgium_airports.show(5)

#  додаємо унікальний ідентифікатор для вершин
airports = airports_df.select("iata", "name", "country").withColumnRenamed("iata", "id")  # Додаємо стовпець id
routes = routes_df.select("alias", "icao").withColumnRenamed("alias", "source_airport").withColumnRenamed("icao", "destination_airport")

edges = routes.withColumnRenamed("source_airport", "src").withColumnRenamed("destination_airport", "dst")
g = GraphFrame(airports, edges)

# Specify variable vertices for BFS
start_vertex = edges.collect()[502]["src"]  # Example: ID of one airport
end_vertex = edges.collect()[3127]["dst"]   # Example: ID of another airport

print("\n\n-------------start---------------------\n\n")

g.find("(a)-[e]->(b)").filter("a.id = '507'").show()
print("\n\n----------------g.find end---------\n\n")


# Check connectivity of start_vertex
print(f"Neighbors of {start_vertex}:")
g.find("(a)-[e]->(b)").filter(f"a.id = '{start_vertex}'").show()

# Check connectivity of end_vertex
print(f"Neighbors of {end_vertex}:")
g.find("(a)-[e]->(b)").filter(f"b.id = '{end_vertex}'").show()

# Dynamically test connected vertices
connected_pair = edges.select("src", "dst").collect()
if connected_pair:
    start_vertex = airports.collect()[502]["id"]#connected_pair[507]["src"]
    end_vertex = airports.collect()[3127]["id"]#connected_pair[3127]["dst"]
    print(f"TESTING WITH CONNECTED VERTICES: {airports.collect()[502]['name']} -> {end_vertex}")

    bfs_result = g.bfs(
        fromExpr=f"id = '{start_vertex}'",
        toExpr=f"id = '{end_vertex}'"
    )

    if bfs_result.count() > 0:
        print("----------ROUTE FOUND:")
        bfs_result.show()
    else:
        print("----------NO ROUTE FOUND FOR CONNECTED VERTICES.")
else:
    print("----------NO CONNECTED VERTICES FOUND.")






print("\n\n-------------end---------------------\n\n")