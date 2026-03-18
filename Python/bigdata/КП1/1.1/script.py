from pyspark.sql import SparkSession
from pyspark.sql.functions import col, sum, round, udf, monotonically_increasing_id, expr
from pyspark.sql.types import DoubleType
from math import radians, sin, cos, asin, sqrt
from pyspark.sql.types import StructType, StructField, IntegerType, StringType
from graphframes import GraphFrame
import os
import sys
os.environ['PYSPARK_PYTHON'] = sys.executable
os.environ['PYSPARK_DRIVER_PYTHON'] = sys.executable
# Створюємо SparkSession
# spark = SparkSession.builder \
    # .appName("Airline Route Analysis") \
    # .getOrCreate()
spark = SparkSession.builder \
    .master("local[*]") \
    .config("spark.driver.extraJavaOptions", "-Djava.security.manager=allow") \
    .config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12") \
    .appName("GraphFramesExample") \
    .getOrCreate()
# -------------------------------------------------------------------------------------------
# Знайти авіакомпанію з найбільшою сумою відстаней всіх рейсів. Теж саме з найменшою сумою.
# -------------------------------------------------------------------------------------------
# Функція для обчислення відстані між двома точками на сфері (формула гаверсинусів)
def haversine_distance(lat1, lon1, lat2, lon2):
    R = 6371  # радіус Землі в кілометрах    
    # Конвертуємо градуси в радіани
    lat1, lon1, lat2, lon2 = map(float, [lat1, lon1, lat2, lon2])
    lat1, lon1, lat2, lon2 = map(radians, [lat1, lon1, lat2, lon2])    
    # Різниця координат
    dlat = lat2 - lat1
    dlon = lon2 - lon1    
    # Формула гаверсинусів
    a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
    c = 2 * asin(sqrt(a))    
    return float(R * c)
# Реєструємо UDF для використання в Spark
calculate_distance = udf(haversine_distance, DoubleType())
# Завантажуємо дані
airports_df = spark.read.csv("airports-extended.dat", header=False) \
    .select(
        col("_c0").alias("airport_id"),
        col("_c6").cast("double").alias("latitude"),
        col("_c7").cast("double").alias("longitude")
    )
airlines_df = spark.read.csv("airlines.dat", header=False) \
    .select(
        col("_c0").alias("airline_id"),
        col("_c1").alias("airline_name")
    )
routes_df = spark.read.csv("routes.dat", header=False) \
    .select(
        col("_c1").alias("airline_id"),
        col("_c3").alias("source_airport_id"),
        col("_c5").alias("destination_airport_id")
    )
# З'єднуємо таблиці для отримання координат аеропортів
routes_with_coords = routes_df \
    .join(airports_df.alias("src"), 
          col("source_airport_id") == col("src.airport_id")) \
    .join(airports_df.alias("dst"), 
          col("destination_airport_id") == col("dst.airport_id")) \
    .join(airlines_df, "airline_id") \
    .select(
        "airline_id",
        "airline_name",
        col("src.latitude").alias("src_lat"),
        col("src.longitude").alias("src_lon"),
        col("dst.latitude").alias("dst_lat"),
        col("dst.longitude").alias("dst_lon")
    )
# Обчислюємо відстань для кожного маршруту та сумуємо по авіакомпаніях
airlines_distances = routes_with_coords \
    .withColumn(
        "distance",
        calculate_distance(
            col("src_lat"), 
            col("src_lon"), 
            col("dst_lat"), 
            col("dst_lon")
        )
    ) \
    .groupBy("airline_id", "airline_name") \
    .agg(
        round(sum("distance"), 2).alias("total_distance_km"),
        round(sum("distance") / 1000, 2).alias("total_distance_thousand_km")
    )
# Знаходимо авіакомпанії з максимальною та мінімальною сумою відстаней
max_airline = airlines_distances.orderBy(col("total_distance_km").desc()).first()
min_airline = airlines_distances.orderBy(col("total_distance_km").asc()).first()
os.system("cls")
print("-----------------------------------RESULTS-----------------------------------\n")
print("The airline with the HIGHEST sum of distances: ",max_airline['airline_name'])
print("Total distance: ",max_airline['total_distance_km'])
print("Total distance: ",max_airline['total_distance_km'])
print("Total distance (thousand km): ",max_airline['total_distance_thousand_km'])

print("The airline with the LOWEST sum of distances: ",min_airline['airline_name'])
print("Total distance: ",min_airline['total_distance_km'])
print("Total distance: ",min_airline['total_distance_km'])
print("Total distance (thousand km): ",min_airline['total_distance_thousand_km'])
print("Top 10 airlines with the HIGHEST sum of distances: ")
airlines_distances.orderBy(col("total_distance_km").desc()).show(10, truncate=False)
print("Top 10 airlines with the LOWEST sum of distances: ")
airlines_distances.orderBy(col("total_distance_km").asc()).show(10, truncate=False)
spark.stop()
# -------------------------------------------------------------------------------------------
# Знайти всі можливі рейси між Польщею та Бельгією (при не більше ніж 2-х стиковках). 
# Використайте motif та інші варіанти рішень, порівняйте їх результати по швидкодії та 
# складності реалізації.  
# -------------------------------------------------------------------------------------------
"""schema = StructType([
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
    StructField("equipement", StringType(), True),
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


# spark = SparkSession.builder.appName("GraphFramesExample").getOrCreate()
# spark = SparkSession.builder.master("local[*]").config("spark.jars.packages", "graphframes:graphframes:0.8.2-spark3.2-s_2.12").getOrCreate()
spark = SparkSession.builder \
    .appName("Airline Route Analysis") \
    .getOrCreate()
# завантажуємо файли
airports_df = spark.read.option("delimiter", ",").csv("airports_extended.dat", header=True, schema=schema)
airlines_df = spark.read.option("delimiter", ",").csv("airlines.dat", header=True, schema=schema1)
routes_df = spark.read.option("delimiter", ",").csv("routes.dat", header=True, schema=schema2)

from pyspark.sql import functions as F

poland_airports = airports_df.filter(airports_df.country == "Poland")
belgium_airports = airports_df.filter(airports_df.country == "Belgium")

# перевірка
poland_airports.show(5)
belgium_airports.show(5)


#  додаємо унікальний ідентифікатор для вершин
airports = airports_df.select("iata", "name", "country").withColumnRenamed("iata", "id")  # Додаємо стовпець id
routes = routes_df.select("alias", "icao").withColumnRenamed("alias", "source_airport").withColumnRenamed("icao", "destination_airport")

edges = routes.withColumnRenamed("source_airport", "src").withColumnRenamed("destination_airport", "dst")
graph = GraphFrame(airports, edges)

print(f"Number of vertices: {graph.vertices.count()}")
print(f"Number of edges: {graph.edges.count()}")

from pyspark.sql.functions import col

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

final_result = result_1.union(result_2)
final_result.show(truncate=False)

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

final_result = flights_poland_to_belgium.union(flights_belgium_to_poland)
final_result.show(truncate=False)

# Підрахунок кількості рейсів для кожного аеропорту
airport_flight_counts = edges.groupBy("src").count().withColumnRenamed("count", "flight_count")

# Найбільша кількість рейсів
max_flight_airport = airport_flight_counts.orderBy(F.desc("flight_count")).first()
print(f"Airport with Max Flights: {max_flight_airport}")

# Найменша кількість рейсів
min_flight_airport = airport_flight_counts.orderBy(F.asc("flight_count")).first()
print(f"Airport with Min Flights: {min_flight_airport}")"""