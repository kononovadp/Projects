# Subgraphs Visualizationimport plotly.express as pximport pandas as pdclusters_geodata = detailed_isolated_subgraphs.join(airportsData, detailed_isolated_subgraphs["id"] ==airportsData["airport_id"]) \.select("component", "latitude", "longitude") \.toPandas()clusters_geodata['latitude'] = pd.to_numeric(clusters_geodata['latitude'],errors='coerce')clusters_geodata['longitude'] = pd.to_numeric(clusters_geodata['longitude'],errors='coerce')clusters_geodata.dropna(subset=['latitude', 'longitude'], inplace=True)fig = px.scatter_mapbox(clusters_geodata,lat="latitude",lon="longitude",color="component",zoom=3,mapbox_style="open-street-map")# Subgraphs Visualizationimport plotly.express as pximport pandas as pdclusters_geodata = detailed_isolated_subgraphs.join(airportsData, detailed_isolated_subgraphs["id"] ==airportsData["airport_id"]) \
.select("component", "latitude", "longitude") \.toPandas()clusters_geodata['latitude'] = pd.to_numeric(clusters_geodata['latitude'],errors='coerce')clusters_geodata['longitude'] = pd.to_numeric(clusters_geodata['longitude'],errors='coerce')clusters_geodata.dropna(subset=['latitude', 'longitude'], inplace=True)fig = px.scatter_mapbox(clusters_geodata,lat="latitude",lon="longitude",color="component",zoom=3,mapbox_style="open-street-map")fig.show().select("component", "latitude", "longitude") \.toPandas()clusters_geodata['latitude'] = pd.to_numeric(clusters_geodata['latitude'],errors='coerce')clusters_geodata['longitude'] = pd.to_numeric(clusters_geodata['longitude'],errors='coerce')clusters_geodata.dropna(subset=['latitude', 'longitude'], inplace=True)fig = px.scatter_mapbox(clusters_geodata,lat="latitude",lon="longitude",color="component",zoom=3,mapbox_style="open-street-map")fig.show()

from pyspark.sql import SparkSession
from pyspark.ml.feature import RegexTokenizer, CountVectorizer, IDF
from pyspark.sql.functions import split, col
from pyspark.sql.types import StringType, ArrayType
from pyspark.sql.functions import udf
from pyspark.ml.linalg import SparseVector
from collections import defaultdict

# Ініціалізація Spark сесії
spark = SparkSession.builder.appName("TextProcessing").getOrCreate()

# 1. Завантаження лематизованих даних
df = spark.read.csv("lemmatize_text.csv", header=True, inferSchema=True)

# 2. Розбивка тексту на токени
df_split_tokens = df.withColumn("tokens", split(col("lemmas"), " "))

# 3. Ініціалізація CountVectorizer
vectorizer = CountVectorizer(inputCol="tokens", outputCol="rawFeatures")
model = vectorizer.fit(df_split_tokens)

# 4. Трансформація даних для створення Bag of Words
df_bag = model.transform(df_split_tokens)

# 5. Ініціалізація IDF
idf = IDF(inputCol="rawFeatures", outputCol="features")
idfModel = idf.fit(df_bag)
df_tfidf = idfModel.transform(df_bag)


# 6. Функція для конвертації SparseVector у текстовий формат (для TF-IDF)
def vector_to_string(vector):
    return " ".join([f"{i}:{v:.4f}" for i, v in zip(vector.indices, vector.values)])

vector_to_string_udf = udf(vector_to_string, StringType())

# 7. Додавання стовпця з текстовим представленням TF-IDF
df_tfidf_string = df_tfidf.withColumn("tfidf_str", vector_to_string_udf(col("features")))

# 8. Збереження TF-IDF у файл
df_tfidf_string.select("title", "tfidf_str").write.csv("tfidf_text.csv", header=True, mode="overwrite")

# 9. Отримання 10 найчастіших слів та їх TF-IDF
vocabulary = model.vocabulary
term_frequencies = df_bag.select("rawFeatures").rdd.flatMap(lambda x: x).collect()

term_counts = defaultdict(int)

for vector in term_frequencies:
    for i, v in zip(vector.indices, vector.values):
        term_counts[vocabulary[i]] += int(v)

sorted_terms = sorted(term_counts.items(), key=lambda item: item[1], reverse=True)
top_10_terms = sorted_terms[:10]

# Виводимо TF-IDF для топ-10 слів
print("TF-IDF для 10 найчастіших слів:")
for term, count in top_10_terms:
    term_index = vocabulary.index(term)
    idf_value = idfModel.idf.toArray()[term_index]
    print(f"{term}: TF={count}, IDF={idf_value:.4f}")

# 10. Збереження словника
with open("vocabulary.txt", "w", encoding="utf-8") as f:
    for word in vocabulary:
        f.write(word + "\n")

# Зупинка Spark сесії
spark.stop()