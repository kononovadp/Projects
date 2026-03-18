from pyspark.sql import SparkSession
from pyspark.sql.types import StructType, StructField, IntegerType, StringType

# Створення схеми
schema_airport = StructType([
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

schema_routes = StructType([
    StructField("airline", StringType(), True),
    StructField("airline_id", IntegerType(), True),
    StructField("srcairport", IntegerType(), True),
    StructField("srcairport_id", IntegerType(), True),
    StructField("dstairport", IntegerType(), True),
    StructField("dstairport_id", IntegerType(), True),
    StructField("code_share", StringType(), True),
    StructField("stops", StringType(), True),
    StructField("equipement", StringType(), True),
])

schema_airlines = StructType([
    StructField("id", IntegerType(), True),
    StructField("name", StringType(), True),
    StructField("alias", StringType(), True),
    StructField("iata", StringType(), True),
    StructField("icao", StringType(), True),
    StructField("callsign", StringType(), True),
    StructField("country", StringType(), True),
    StructField("active", StringType(), True)
])

%pip install graphframes
from graphframes import GraphFrame

# Завантаження даних в DataFrame
airports_df = spark.read.csv("dbfs:/FileStore/tables/airports_extended-3.dat", header=True, schema=schema_airport)
routes_df = spark.read.csv("dbfs:/FileStore/tables/routes-3.dat",  header=True, schema=schema_routes)
airlines_df =  spark.read.csv("dbfs:/FileStore/tables/airlines-3.dat",  header=True, schema=schema_airlines)

airports_df.printSchema()

airports_df.show(5)
routes_df.show(15)
airlines_df.show(5)

from pyspark.sql import functions as F

# підрахунок рейсів по аеропортах відправлення (alias)
source_airports = airlines_df.groupBy("alias").agg(F.count("*").alias("num_flights"))

# підрахунок рейсів по аеропортах призначення (icao)
destination_airports = airlines_df.groupBy("icao").agg(F.count("*").alias("num_flights"))

# об'єднуємо обидва DataFrame для підрахунку загальної кількості рейсів по кожному аеропорту
airport_flights = source_airports.union(destination_airports).groupBy("alias").agg(F.sum("num_flights").alias("total_flights"))

airport_flights = airport_flights.withColumnRenamed("alias", "Аеропорт")

max_airport = airport_flights.orderBy(F.desc("total_flights")).first()
min_airport = airport_flights.orderBy(F.asc("total_flights")).first()

print(f"Airport with max flights: {max_airport}")
print(f"Airport with min flights: {min_airport}")