import numpy as np
import matplotlib.pyplot as plt
from skimage.io import imread
from skimage.transform import resize
from sklearn.metrics import silhouette_score
from math import dist
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
import warnings
warnings.filterwarnings("ignore")
import random
import numpy as np
from datetime import datetime
from datetime import timedelta
class OurKMeans:
	def __init__(self, n_clusters):
		self.n_clusters = n_clusters		
	@staticmethod
	def distance(p1, p2):
		# D=np.zeros((len(p1),len(p2)))
		# for i in range(len(p1)):			
			# for j in range(len(p2)):
				# D[i,j]=sum((y-x)**2 for x, y in zip(p1[i], p2[j])) ** 0.5
		D = np.linalg.norm(p1[:, np.newaxis] - p2, axis=2)
		return D
	def fit(self, x):
		count_of_samples = len(x)
		count_of_features = len(x[0])
		self.cluster_centers_ = np.empty((self.n_clusters, count_of_features))
		self.cluster_centers_[0] = x[np.random.choice(count_of_samples)]
		for i in range(1, self.n_clusters):
			distances = np.min(self.distance(x, self.cluster_centers_[:i]), axis=1)
			next_centroid = np.argmax(distances)
			self.cluster_centers_[i] = x[next_centroid]
		while True:
			D = np.argmin(self.distance(x, self.cluster_centers_),axis=1)
			new_cluster_centers = []
			for i in range(self.n_clusters):
				new_cluster_center = x[D == i]
				if(len(new_cluster_center) > 0):
					new_cluster_centers.append(new_cluster_center.mean(axis=0))
				else:
					new_cluster_centers.append(x[np.random.choice(x.shape[0])])
			if np.allclose(new_cluster_centers, self.cluster_centers_):
				break
			self.cluster_centers_ = new_cluster_centers		
		return self	
	def predict(self, x):
		D = self.distance(x, self.cluster_centers_)
		return D.argmin(axis=1)
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
start = datetime.now()
x = np.concatenate([np.random.normal(size=(100, 2)), np.random.normal(size=(100, 2)) + 5])
clust = OurKMeans(2).fit(x).predict(x)
plt.figure(figsize=(6, 6))
plt.scatter(*x.T, c=clust)
plt.savefig("Plots\\KMeans random numbers.jpg", dpi = 200)
plt.close()
image = imread('image.bmp')
image = resize(image, (64, 64), preserve_range=True)
pixels = image.reshape(-1, 3)
ks = list(range(2, 17))
KMeansScores = []
SklearnKMeansScores = []
print()
for k in ks:
	kmeans = OurKMeans(n_clusters=k)
	kmeans.fit(pixels)
	predictions=kmeans.predict(pixels)
	kmeans_silhouette_score = silhouette_score(pixels, predictions, metric='euclidean')	
	KMeansScores.append(kmeans_silhouette_score)	
	clusterer = KMeans(n_clusters=k, random_state=10)  
	predictions=clusterer.fit_predict(pixels)	
	sklearn_kmeans_silhouette_score=silhouette_score(pixels, predictions)  
	SklearnKMeansScores.append(sklearn_kmeans_silhouette_score)	
	print(" K: ",k,"; KMeans silhouette score: ",f'{kmeans_silhouette_score:.5f}',end="; ")
	print("Sklearn KMeans silhouette score: ",f'{sklearn_kmeans_silhouette_score:.5f}')
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print(" Time: ",hours,":",minutes,":",seconds,"\n")
plt.plot(ks, KMeansScores)
plt.savefig("Plots\\KMeans.jpg", dpi = 200)
plt.close()
plt.plot(ks, SklearnKMeansScores)
plt.savefig("Plots\\Sklearn KMeans.jpg", dpi = 200)
plt.close()
plt.plot(ks, KMeansScores, label = "KMeans")
plt.plot(ks, SklearnKMeansScores, label = "Sklearn KMeans")
plt.legend(bbox_to_anchor = (0.35,1),loc = 'upper right')
plt.savefig("Plots\\KMeans and Sklearn KMeans.jpg", dpi = 200)
plt.close()
#################### TASK 2 ####################
class OurPCA:	
	def __init__(self, n_components):
		self.n_components = n_components		
	def fit(self, X):
		self.mean_ = X.mean(axis=0)
		X_centered = X - self.mean_
		covariance_matrix = np.cov(X_centered.T)
		eigenvalue, eigenvectors = np.linalg.eigh(covariance_matrix)
		sorted_indices = np.argsort(eigenvalue)[::-1]
		self.components_ = eigenvectors[:, sorted_indices[:self.n_components]]
		return self		
	def transform(self, X):
		X_centered = X - self.mean_
		X_proj = X_centered.dot(self.components_)
		return X_proj
with np.load('mnist.npz') as npz:
	x, y = [npz[k] for k in ['x_train', 'y_train']]
x = x.reshape(-1, 784).astype(np.float32)
pca = OurPCA(n_components=2).fit(x)
x_proj = pca.transform(x)
plt.figure(figsize=(10, 8))
plt.scatter(*x_proj.T, c=y, s=2)
plt.colorbar()
plt.savefig("Plots\\PCA.jpg", dpi = 200)
plt.close()
pca = PCA(n_components=2, svd_solver='full')
x_proj = pca.fit_transform(x)
plt.figure(figsize=(10, 8))
plt.scatter(*x_proj.T, c=y, s=2)
plt.colorbar()
plt.savefig("Plots\\Sklearn PCA.jpg", dpi = 200)