from pyspark.sql import SparkSession
from pyspark.sql.types import StructType, StructField, IntegerType, StringType
from pyspark.sql.functions import col, expr
from graphframes import GraphFrame
from pyspark.sql import functions as F
# from io import StringIO
from tabulate import tabulate
import os
import sys
os.environ['PYSPARK_PYTHON'] = sys.executable
os.environ['PYSPARK_DRIVER_PYTHON'] = sys.executable
spark = SparkSession.builder \
    .master("local[*]") \
    .config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
    .config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
    .appName("GraphFramesExample") \
    .getOrCreate()
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

poland_airports = airports_df.filter(airports_df.country == "Poland")
belgium_airports = airports_df.filter(airports_df.country == "Belgium")

# перевірка
# poland_airports.show(5)
# belgium_airports.show(5)

#  додаємо унікальний ідентифікатор для вершин
airports = airports_df.select("iata", "name", "country").withColumnRenamed("iata", "id")  # Додаємо стовпець id
routes = routes_df.select("alias", "icao").withColumnRenamed("alias", "source_airport").withColumnRenamed("icao", "destination_airport")

edges = routes.withColumnRenamed("source_airport", "src").withColumnRenamed("destination_airport", "dst")
graph = GraphFrame(airports, edges)

# print(f"NUMBER OF VERTICES: {graph.vertices.count()}")
# print(f"NUMBER OF EDGES: {graph.edges.count()}")

# вибірка аеропортів Польщі та Бельгії
poland_airports = airports.filter(col("country") == "Poland").select("id")
belgium_airports = airports.filter(col("country") == "Belgium").select("id")


# # ВИКОРИСТАННЯ MOTIF 
# створення motif для пошуку рейсів
motif = graph.find("(a)-[e]->(b); (b)-[f]->(c)")

# фільтрація рейсів від Польщі до Бельгії з не більше ніж 2 стиковками
result_1 = motif.filter(
    (col("a.country") == "Poland") & (col("c.country") == "Belgium")
)

# від  Бельгії до  Польщі з не більше ніж 2 стиковками
result_2 = motif.filter(
    (col("a.country") == "Belgium") & (col("c.country") == "Poland")
)
os.system("cls")
print("------------------------------------RESULTS OUTPUT------------------------------------")

result = result_1.union(result_2)
# result.show(truncate=False)
# ВИКОРИСТАННЯ BFS
flights_poland_to_belgium = graph.bfs(
    fromExpr="country == 'Poland'",  
    toExpr="country == 'Belgium'",  
    maxPathLength=3  
    # максимальна кількість стиковок 2, тобто шлях - 3 аеропорти
)
flights_belgium_to_poland = graph.bfs(
    fromExpr="country == 'Belgium'", 
    toExpr="country == 'Poland'",  
    maxPathLength=3  
)
result = flights_poland_to_belgium #.union(flights_belgium_to_poland)

# table_in_file = result.select("from","to")
table_in_file = result.select(col("`from`.name"), col("`from`.country"), col("`to`.name"), col("`to`.country")).toPandas()
table=tabulate(table_in_file, headers='keys', tablefmt='grid')
table_in_file.to_csv("airports.csv", index=False, encoding='utf-8')
with open("airports_table.txt", "w", encoding="utf-8") as f:
    f.write(table)
print("\n----------FROM:----------")
print(tabulate(result.select(col("`from`.name"), col("`from`.country")).toPandas(), headers='keys', tablefmt='grid'))
print("----------TO:----------")
print(tabulate(result.select(col("`to`.name"), col("`to`.country")).toPandas(), headers='keys', tablefmt='grid'))
# # Підрахунок кількості рейсів для кожного аеропорту
airport_flight_counts = edges.groupBy("src").count().withColumnRenamed("count", "flight_count")



max_flight_airport = airport_flight_counts.orderBy(F.desc("flight_count"))
print("MAX COUNT OF FLIGHTS: ",max_flight_airport.first()['flight_count'],"; AIRPORTS WITH MAX COUNT OF FLIGHTS: ")
max_flight_airport.show()
min_flight_airport = airport_flight_counts.orderBy(F.asc("flight_count"))
print("MIN COUNT OF FLIGHTS: ",min_flight_airport.first()['flight_count'],"; AIRPORTS WITH MIN COUNT OF FLIGHTS: ")
min_flight_airport.show()
print("------------------------------------RESULTS OUTPUT END------------------------------------")
