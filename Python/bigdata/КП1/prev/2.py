from pyspark.sql import SparkSession
from pyspark.sql.types import StructType, StructField, IntegerType, StringType

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

%pip install graphframes
from graphframes import GraphFrame


# завантажуємо файли
airports_df = spark.read.option("delimiter", ",").csv("dbfs:/FileStore/tables/airports_extended-3.dat", header=True, schema=schema)
airlines_df = spark.read.option("delimiter", ",").csv("dbfs:/FileStore/tables/airlines-3.dat", header=True, schema=schema1)
routes_df = spark.read.option("delimiter", ",").csv("dbfs:/FileStore/tables/routes-3.dat", header=True, schema=schema2)

from pyspark.sql import functions as F


#  перевірка структури даних
routes_df.printSchema()

routes_df.show(5)

# підрахунок рейсів по аеропортах відправлення (alias)
source_airports = routes_df.groupBy("alias").agg(F.count("*").alias("num_flights"))

# підрахунок рейсів по аеропортах призначення (icao)
destination_airports = routes_df.groupBy("icao").agg(F.count("*").alias("num_flights"))

# об'єднуємо ці два DataFrame для підрахунку загальної кількості рейсів для кожного аеропорту
airport_flights = source_airports.union(destination_airports).groupBy("alias").agg(F.sum("num_flights").alias("total_flights"))

airport_flights = airport_flights.withColumnRenamed("alias", "Аеропорт")

max_airport = airport_flights.orderBy(F.desc("total_flights")).first()
min_airport = airport_flights.orderBy(F.asc("total_flights")).first()

print(f"Airport with max flights: {max_airport}")
print(f"Airport with min flights: {min_airport}")