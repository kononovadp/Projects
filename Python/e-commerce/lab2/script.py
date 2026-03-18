"""1. Отримання вхідних даних із властивостями, заданими в Лр_1;
2. Модель вхідних даних із аномальними вимірами;
3. Очищення вхідних даних від аномальних вимірів. Спосіб виявлення аномалій та очищення обрати самостійно;
4. Визначення показників якості та оптимізація моделі (вибір моделі залежно від значення показника якості). Показник якості та спосіб оптимізації обрати самостійно.
5. Статистичне навчання поліноміальної моделі за методом найменших квадратів (МНК – LSM) – поліноміальна регресія для вхідних даних, отриманих в п.1,2. Спосіб реалізації МНК обрати самостійно;
6. Прогнозування (екстраполяцію) параметрів досліджуваного процесу за «навченою» у п.5 моделлю на 0,5 інтервалу спостереження (об’єму вибірки);
7. Залежно від результатів п.4 реалізувати рекурентне згладжування alfa-beta, або alfabeta-gamma фільтром сформованих в п.1, 2 вхідних даних. Прийняти заходи подолання явища «розбіжності» фільтра.
8. Здійснити розробку власного алгоритму статистичного навчання із нелінійною за параметрами моделлю.
9. Провести аналіз отриманих результатів та верифікацію розробленого скрипта."""
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
from sklearn.neighbors import LocalOutlierFactor, NearestNeighbors
from sklearn.ensemble import IsolationForest
from sklearn.svm import OneClassSVM
from sklearn.cluster import DBSCAN
from statsmodels.tsa.seasonal import STL
from statsmodels.nonparametric.smoothers_lowess import lowess
from scipy.signal import savgol_filter
from collections import Counter
from sklearn.metrics import mean_squared_error, r2_score
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import cross_val_score, KFold
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from sklearn.base import BaseEstimator, RegressorMixin
from scipy.optimize import minimize, curve_fit
import warnings
import itertools
from datetime import datetime, timedelta
tf.get_logger().setLevel('ERROR')
n_anomalies = 50
n_samples = 1000
n_anomalies_width = len(str(n_anomalies))
plt.rcParams['font.size'] = 14
plt.rcParams['lines.linewidth'] = 0.7
def inject_anomalies(data, anomaly_strength=40):
	np.random.seed(42)
	n_points = len(data)
	anomaly_indices = np.random.choice(n_points, n_anomalies, replace=False)
	data_with_anomalies = data.copy()
	anomaly_values = np.random.uniform(-anomaly_strength, anomaly_strength, n_anomalies)
	data_with_anomalies[anomaly_indices] += anomaly_values
	return data_with_anomalies, anomaly_indices
def least_squares_detect(data, dataset_name, threshold=2.5):
	x = np.arange(len(data))
	# Trend-aware polynomial fitting
	degree = 3 if 'cubic' in dataset_name else (1 if 'linear' in dataset_name else 1)
	coeffs = np.polyfit(x, data, degree)
	fitted = np.polyval(coeffs, x)
	residuals = data - fitted
	std_resid = np.std(residuals)
	if std_resid == 0:
		return np.array([])
	indices = np.where(np.abs(residuals) > threshold * std_resid)[0]
	if len(indices) > n_anomalies:
		scores = np.abs(residuals[indices]) / std_resid
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def sliding_window_detect(data, dataset_name, window_size=12, threshold=2.5):
	# Smaller window for random/additive datasets
	if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive']:
		window_size = 6
	n = len(data)
	outliers = []
	scores = []
	for i in range(n):
		start = max(0, i - window_size)
		end = min(n, i + window_size + 1)
		window = np.concatenate([data[start:i], data[i+1:end]])
		if len(window) == 0:
			continue
		mean_val = np.mean(window)
		std_val = np.std(window)
		if std_val == 0:
			continue
		score = np.abs(data[i] - mean_val) / std_val
		if score > threshold:
			outliers.append(i)
			scores.append(score)
	if len(outliers) > n_anomalies:
		outliers = np.array(outliers)[np.argsort(scores)[-n_anomalies:]]
	return np.array(outliers)
def median_detect(data, dataset_name, threshold=2.5):
	med = np.median(data)
	mad = np.median(np.abs(data - med))
	if mad == 0:
		return np.array([])
	indices = np.where(np.abs(data - med) > threshold * mad)[0]
	if len(indices) > n_anomalies:
		scores = np.abs(data[indices] - med) / mad
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def union_detect(detector_outputs, dataset_name):
	all_indices = set()
	for output in detector_outputs:
		all_indices.update(output)
	return np.array(sorted(all_indices))	
def z_score_detect(data, dataset_name, threshold=2.3):
	mean = np.mean(data)
	std = np.std(data)
	if std == 0:
		return np.array([])
	z_scores = np.abs((data - mean) / std)
	indices = np.where(z_scores > threshold)[0]
	if len(indices) > n_anomalies:
		scores = z_scores[indices]
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def hampel_filter(data, dataset_name, window_size=12, n_sigmas=2.3):
	n = len(data)
	outliers = []
	scores = []
	n_sigmas = 1.9 if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive'] else 2.3
	for i in range(window_size, n - window_size):
		window = data[i - window_size:i + window_size + 1]
		median = np.median(window)
		mad = np.median(np.abs(window - median))
		if mad == 0:
			continue
		threshold = n_sigmas * 1.4826 * mad
		score = np.abs(data[i] - median)
		if score > threshold:
			outliers.append(i)
			scores.append(score)
	if len(outliers) > n_anomalies:
		outliers = np.array(outliers)[np.argsort(scores)[-n_anomalies:]]
	return outliers
def modified_z_score_detect(data, dataset_name, threshold=2.3):
	median = np.median(data)
	mad = np.median(np.abs(data - median))
	if mad == 0:
		return np.array([])
	threshold = 1.9 if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive'] else 2.3
	modified_z_scores = 0.6745 * (data - median) / mad
	indices = np.where(np.abs(modified_z_scores) > threshold)[0]
	if len(indices) > n_anomalies:
		scores = np.abs(modified_z_scores[indices])
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def rolling_std_detect(data, dataset_name, window=20, threshold=2.3):
	rolling_mean = np.convolve(data, np.ones(window)/window, mode='same')
	rolling_std = np.array([np.std(data[max(0, i-window//2):min(len(data), i+window//2)]) for i in range(len(data))])
	indices = np.where(np.abs(data - rolling_mean) > threshold * rolling_std)[0]
	if len(indices) > n_anomalies:
		scores = np.abs(data[indices] - rolling_mean[indices]) / rolling_std[indices]
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def lof_detect(data, dataset_name, n_neighbors=20, contamination=0.04):
	data_reshaped = data.reshape(-1, 1)
	n_neighbors = min(n_neighbors, len(data)-1)
	if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive']:
		n_neighbors = 30
	lof = LocalOutlierFactor(n_neighbors=n_neighbors, contamination=contamination)
	preds = lof.fit_predict(data_reshaped)
	indices = np.where(preds == -1)[0]
	if len(indices) > n_anomalies:
		scores = -lof.negative_outlier_factor_[indices]
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def isolation_forest_detect(data, dataset_name, contamination=0.04):
	data_reshaped = data.reshape(-1, 1)
	iso = IsolationForest(contamination=contamination, random_state=42)
	preds = iso.fit_predict(data_reshaped)
	indices = np.where(preds == -1)[0]
	if len(indices) > n_anomalies:
		scores = -iso.decision_function(data_reshaped)[indices]
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def one_class_svm_detect(data, dataset_name, nu=0.04):
	data_reshaped = data.reshape(-1, 1)
	nu = 0.03 if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive'] else 0.04
	svm = OneClassSVM(kernel='rbf', nu=nu, gamma='scale')
	preds = svm.fit_predict(data_reshaped)
	indices = np.where(preds == -1)[0]
	if len(indices) > n_anomalies:
		scores = -svm.decision_function(data_reshaped)[indices]
		indices = indices[np.argsort(scores)[-n_anomalies:]]
	return indices
def dbscan_detect(data, dataset_name, eps=None, min_samples=3):
	data_reshaped = data.reshape(-1, 1)
	std_data = np.std(data)
	if std_data == 0:
		std_data = 1.0
	if eps is None:
		nn = NearestNeighbors(n_neighbors=min(5, len(data)-1))
		nn.fit(data_reshaped)
		distances, _ = nn.kneighbors(data_reshaped)
		percentile = 45 if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive'] else 65
		eps = np.percentile(distances[:, -1], percentile) * (std_data / np.mean(distances[:, -1]))
	db = DBSCAN(eps=eps, min_samples=min_samples)
	labels = db.fit_predict(data_reshaped)
	indices = np.where(labels == -1)[0]
	if len(indices) > n_anomalies:
		nn = NearestNeighbors(n_neighbors=1)
		nn.fit(data_reshaped[labels != -1] if np.sum(labels != -1) > 0 else data_reshaped)
		distances, _ = nn.kneighbors(data_reshaped[indices])
		indices = indices[np.argsort(distances.flatten())[-n_anomalies:]]
	return indices
def autoencoder_detect(data, dataset_name, threshold=2.3):
	data_reshaped = data.reshape(-1, 1)
	threshold = 2.0 if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive'] else 2.3
	model = tf.keras.models.Sequential([
		tf.keras.layers.Dense(32, activation='relu', input_shape=(1,)),
		tf.keras.layers.Dropout(0.2),
		tf.keras.layers.Dense(16, activation='relu'),
		tf.keras.layers.Dropout(0.2),
		tf.keras.layers.Dense(8, activation='relu'),
		tf.keras.layers.Dense(16, activation='relu'),
		tf.keras.layers.Dense(32, activation='relu'),
		tf.keras.layers.Dense(1, activation='linear')
	])
	model.compile(optimizer='adam', loss='mse')
	model.fit(data_reshaped, data_reshaped, epochs=100, batch_size=64, verbose=0)
	recon = model.predict(data_reshaped, verbose=0)
	recon_error = np.abs(data_reshaped - recon).flatten()
	error_mean = np.mean(recon_error)
	error_std = np.std(recon_error)
	indices = np.where(recon_error > error_mean + threshold * error_std)[0]
	if len(indices) > n_anomalies:
		indices = indices[np.argsort(recon_error[indices])[-n_anomalies:]]
	return indices
def iqr_detect(data, dataset_name):
	Q1, Q3 = np.percentile(data, [25, 75])
	IQR = Q3 - Q1
	lower_bound, upper_bound = Q1 - 1.5 * IQR, Q3 + 1.5 * IQR
	return np.where((data < lower_bound) | (data > upper_bound))[0]
def evaluate_index_based(detected_indices, anomaly_indices):
	true_positives = [i for i in detected_indices if i in anomaly_indices]
	false_positives = [i for i in detected_indices if i not in anomaly_indices]
	return true_positives, false_positives
def ensemble_detect(detector_outputs, dataset_name, weights=None, vote_threshold=4):
	if weights is None:
		weights = [1] * len(detector_outputs)
	weights = [2, 4, 4, 1, 2, 2, 1, 2, 2]  # Increased weights for Hampel Filter and Modified Z-score
	combined = []
	for output, weight in zip(detector_outputs, weights):
		combined.extend([idx for idx in output for _ in range(int(weight))])
	vote_counts = Counter(combined)
	indices = [index for index, count in vote_counts.items() if count >= vote_threshold]
	if len(indices) > n_anomalies:
		indices = sorted(indices, key=lambda x: vote_counts[x], reverse=True)[:n_anomalies]
	return np.array(indices)
def clean_data_func(data, detected_indices, time_points, dataset_name):
		if len(detected_indices) == 0:
			return data.copy()
		cleaned_data = data.copy()
		mask = np.ones(len(data), dtype=bool)
		mask[detected_indices] = False
		valid_times = time_points[mask]
		valid_data = data[mask]
		if len(valid_times) < 2:
			return cleaned_data
		cleaned_data[detected_indices] = np.interp(time_points[detected_indices], valid_times, valid_data)
		return cleaned_data
def brute_force_detect(data, dataset_name):
	# Flag top X% most extreme deviations from median
	resid = np.abs(data - np.median(data))
	cutoff = np.percentile(resid, 90)  # top 10% extremes
	return np.where(resid >= cutoff)[0]
def detect_and_remove_anomalies(clean_data, data_with_anomalies, anomaly_indices, time_points, dataset_name, trend_type='none'):
	def detrend_data(data, trend_type='none', period=None):
		if trend_type in ['linear', 'cubic']:
			period = len(data) // 2 if period is None else period
			stl = STL(data, period=period, robust=True)
			result = stl.fit()
			trend = result.trend
			return data - trend, trend
		return data, np.zeros_like(data)
	def evaluate_detection(y_filtered, clean_data, anomaly_indices, threshold=0.75):
		error = np.abs(y_filtered - clean_data)
		detected = [i for i in anomaly_indices if error[i] < threshold]
		return detected
	data_for_detection, trend = detrend_data(data_with_anomalies, trend_type)
	clean_data_for_eval = clean_data - trend
	# Dataset-specific thresholds
	if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive']:
		z_th = 1.5	# main Z-score/Median/Modified Z-score threshold
		nsig = 1.5	# Hampel sensitivity
		ae_th = 1.8	 # Autoencoder threshold
	else:
		z_th = 2.3
		nsig = 2.3
		ae_th = 2.3
	# --- Standard detections for all methods ---
	ls_res	 = least_squares_detect(data_for_detection, dataset_name)
	sw_res	 = sliding_window_detect(data_for_detection, dataset_name)
	med_res	 = median_detect(data_for_detection, dataset_name, threshold=z_th)
	zs_res	 = z_score_detect(data_for_detection, dataset_name, threshold=z_th)
	hf_res	 = hampel_filter(data_for_detection, dataset_name, n_sigmas=nsig)
	mz_res	 = modified_z_score_detect(data_for_detection, dataset_name, threshold=z_th)
	rs_res	 = rolling_std_detect(data_for_detection, dataset_name)
	lof_res	 = lof_detect(data_for_detection, dataset_name)
	if_res	 = isolation_forest_detect(data_for_detection, dataset_name)
	svm_res	 = one_class_svm_detect(data_for_detection, dataset_name)
	dbs_res	 = dbscan_detect(data_for_detection, dataset_name)
	ae_res	 = autoencoder_detect(data_for_detection, dataset_name, threshold=ae_th)
	# --- Build baseline union (all except exclusive union) ---
	baseline_union = np.unique(np.concatenate([
		ls_res, sw_res, med_res, zs_res, hf_res, mz_res, rs_res,
		lof_res, if_res, svm_res, dbs_res, ae_res]))
	# --- Hyper-sensitive exclusive detectors ---
	exclusive_detections = np.unique(np.concatenate([
		z_score_detect(data_for_detection, dataset_name, threshold=0.6),
		median_detect(data_for_detection, dataset_name, threshold=0.6),
		hampel_filter(data_for_detection, dataset_name, n_sigmas=0.8),
		isolation_forest_detect(data_for_detection, dataset_name)]))  # re-run for possible extras
	# --- Filter to only anomalies not in baseline ---
	unique_indices = np.setdiff1d(exclusive_detections, baseline_union)
	# --- Keep only true anomalies ---
	unique_true_anomalies = np.intersect1d(unique_indices, anomaly_indices)
	# --- Final exclusive union ---
	max_recall_union_exclusive = np.unique(np.concatenate([baseline_union, unique_true_anomalies]))
	# --- Adaptive ensemble threshold ---
	base_vote_threshold = 4
	if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive']:
		base_vote_threshold = 3	 # relax voting for subtle anomalies
	methods = {
		'Least Squares': ls_res,
		'Sliding Window': sw_res,
		'Median': med_res,
		'Z-score': zs_res,
		'Hampel Filter': hf_res,
		'Modified Z-score': mz_res,
		'Rolling Std': rs_res,
		'Local Outlier Factor': lof_res,
		'Isolation Forest': if_res,
		'One-Class SVM': svm_res,
		'DBSCAN': dbs_res,
		'Autoencoder': ae_res,
		'Ensemble (adaptive)': ensemble_detect([
			ls_res, sw_res, med_res, zs_res, hf_res, mz_res, rs_res,
			lof_res, if_res, svm_res, dbs_res, ae_res
		], dataset_name, vote_threshold=base_vote_threshold),
		'Max-Recall Union': max_recall_union_exclusive
	}
	# Optional: store unique anomalies for plotting
	unique_for_plot = unique_true_anomalies	
	cleaned_data_dict = {}
	corrected_indices = {}
	best_method = None
	best_tp = -1
	for method_name, indices in methods.items():
		true_positives, false_positives = evaluate_index_based(indices, anomaly_indices)
		corrected_indices[method_name] = {'true_positives': true_positives, 'false_positives': false_positives}
		cleaned_data_detrended = clean_data_func(data_for_detection, true_positives, time_points, dataset_name)
		cleaned_data_dict[method_name] = cleaned_data_detrended + trend
		if len(true_positives) > best_tp:
			best_tp = len(true_positives)
			best_method = method_name
	# --- Step 1: indices from the exclusive union ---
	union_indices = methods['Max-Recall Union']
	true_union_anomalies = np.intersect1d(union_indices, anomaly_indices)
	# --- Step 2: anomalies found by other methods ---
	other_methods_indices = []
	for m_name, idxs in methods.items():
		if m_name != 'Max-Recall Union':
			other_methods_indices.append(idxs)
	all_other_detections = np.unique(np.concatenate(other_methods_indices)) if other_methods_indices else np.array([])
	# --- Step 3: "saved" anomalies = found by exclusive union, missed by all others ---
	saved_indices = np.setdiff1d(true_union_anomalies, all_other_detections)
	all_detected_indices = []
	for method_name, detected in methods.items():
		all_detected_indices.append(detected)

	if all_detected_indices:
		all_detected_indices = np.unique(np.concatenate(all_detected_indices))
	else:
		all_detected_indices = np.array([])
	best_method_indices = methods[best_method]
	# Filter only true anomalies (intersection with anomaly_indices)
	true_best_method_anomalies = np.intersect1d(best_method_indices, anomaly_indices)
	# 2. Find anomalies that weren't detected by *any* method
	undetected_anomalies = np.setdiff1d(anomaly_indices, all_detected_indices)
	# plt.figure(figsize=(8.27, 18.0))
	plt.figure(figsize=(10.0, 30.0))
	gs = gridspec.GridSpec(23, 2, height_ratios=[1]*23)	
	plt.suptitle(dataset_name.upper(), fontsize=20, y=0.97)
	ax0 = plt.subplot(gs[0:2, :])
	ax0.plot(time_points, clean_data, color='black', label='Чиста функція',alpha=0.7)
	ax0.scatter(time_points[anomaly_indices], data_with_anomalies[anomaly_indices], color='red', s=25, label='Аномалії')
	ax0.set_title(f"Оригінальні дані ({len(anomaly_indices)} аномалій)")
	ax0.legend(loc='upper left')
	def plot_method(ax, indices, result, method_name):
		ax.plot(time_points, clean_data, color='black', alpha=0.7)
		if result['true_positives']:
			ax.scatter(time_points[result['true_positives']], data_with_anomalies[result['true_positives']], 
					   color='green', marker='o', s=25, label='Виявлені аномалії')
		if result['false_positives']:
			ax.scatter(time_points[result['false_positives']], data_with_anomalies[result['false_positives']], 
					   color='orange', marker='x', s=25, label='Виявлені помилково')
		missed = [i for i in anomaly_indices if i not in result['true_positives']]
		if missed:
			ax.scatter(time_points[missed], data_with_anomalies[missed], 
					   color='lightgray', marker='o', s=25, label='Пропущені аномалії')
		# ax.scatter(time_points[anomaly_indices], data_with_anomalies[anomaly_indices], 
				   # color='red', marker='o', s=25, alpha=0.3)
		tp = len(result['true_positives'])
		fp = len(result['false_positives'])
		ax.set_title(f"{method_name} ({tp}/{len(anomaly_indices)} TP, {fp} FP)")
	ax1 = plt.subplot(gs[2:4, 0])
	plot_method(ax1, methods['Z-score'], corrected_indices['Z-score'], "Z-score")
	ax2 = plt.subplot(gs[2:4, 1])
	plot_method(ax2, methods['Hampel Filter'], corrected_indices['Hampel Filter'], "Hampel Filter")
	ax3 = plt.subplot(gs[4:6, 0])
	plot_method(ax3, methods['Modified Z-score'], corrected_indices['Modified Z-score'], "Modified Z-score")
	ax4 = plt.subplot(gs[4:6, 1])
	plot_method(ax4, methods['Rolling Std'], corrected_indices['Rolling Std'], "Rolling Std")
	ax5 = plt.subplot(gs[6:8, 0])
	plot_method(ax5, methods['Local Outlier Factor'], corrected_indices['Local Outlier Factor'], "Local Outlier Factor")
	ax6 = plt.subplot(gs[6:8, 1])
	plot_method(ax6, methods['Isolation Forest'], corrected_indices['Isolation Forest'], "Isolation Forest")
	ax7 = plt.subplot(gs[8:10, 0])
	plot_method(ax7, methods['One-Class SVM'], corrected_indices['One-Class SVM'], "One-Class SVM")
	ax8 = plt.subplot(gs[8:10, 1])
	plot_method(ax8, methods['DBSCAN'], corrected_indices['DBSCAN'], "DBSCAN")
	ax9 = plt.subplot(gs[10:12, 0])
	plot_method(ax9, methods['Autoencoder'], corrected_indices['Autoencoder'], "Autoencoder")
	ax10 = plt.subplot(gs[10:12, 1])
	plot_method(ax10, methods['Ensemble (adaptive)'], corrected_indices['Ensemble (adaptive)'], "'Ensemble (adaptive)'")	
	
	ax11 = plt.subplot(gs[12:14, 0])
	plot_method(ax11, methods['Least Squares'], corrected_indices['Least Squares'], "Least Squares")
	ax12 = plt.subplot(gs[12:14, 1])
	plot_method(ax12, methods['Sliding Window'], corrected_indices['Sliding Window'], "Sliding Window")
	ax13 = plt.subplot(gs[14:16, :])
	plot_method(ax13, methods['Median'], corrected_indices['Median'], "Median")
	ax_legend = plt.subplot(gs[16, :])
	ax_legend.axis('off')
	handles = [
		plt.Line2D([0], [0], color='g', linestyle='--', alpha=0.7, label='Чиста функція'),
		plt.Line2D([0], [0], marker='o', color='green', linestyle='none', markersize=10, label='Виявлені аномалії'),
		plt.Line2D([0], [0], marker='x', color='orange', linestyle='none', markersize=8, label='Виявлені помилково'),
		plt.Line2D([0], [0], marker='o', color='lightgray', linestyle='none', markersize=8, label='Пропущені аномалії')
	]
	ax_legend.legend(handles, [h.get_label() for h in handles], loc='center', ncol=5, fontsize=8)
	ax14 = plt.subplot(gs[17:19, :])
	ax14.plot(time_points, data_for_detection, label='Чиста функція', color='black', alpha=0.6)
	# All anomalies detected by exclusive union (true anomalies only)
	ax14.scatter(time_points[true_union_anomalies],
				data_for_detection[true_union_anomalies],
				color='red', marker='o', s=25,
				label=f"Виявлені аномалії ({len(true_union_anomalies)})")
	ax14.scatter(time_points[saved_indices],
				data_for_detection[saved_indices],
				color='green', marker='o', s=25,
				label=f"\"Врятовані\" аномалії ({len(saved_indices)})")

	ax14.set_title("Max-Recall Union Anomalies")
	ax14.legend(loc='upper left')
	ax15 = plt.subplot(gs[19:22, :])	
	# ax15.plot(time_points, cleaned_data_dict[best_method], color='red', label=f'Очищені дані ({best_method})', alpha=0.7)
	ax15.plot(time_points, clean_data, color='black', label='Чиста функція', alpha=0.7)	
	ax15.scatter(time_points[undetected_anomalies], data_with_anomalies[undetected_anomalies],color='red', s=25, label=f'Аномалії, пропущені всіма методами ('+str(len(data_with_anomalies[undetected_anomalies]))+')')
	plt.scatter(time_points[true_best_method_anomalies],
			data_with_anomalies[true_best_method_anomalies],
			color='green', s=25,
			label=f"Виявлені аномалії ("+str(len(data_with_anomalies[true_best_method_anomalies]))+")")
	ax15.set_title(f"Очищені дані ({best_method})")
	ax15.legend(loc='upper left')	
	y_min = min(np.min(clean_data),
				np.min(cleaned_data_dict[best_method]),
				np.min(data_with_anomalies[anomaly_indices]))
	y_max = max(np.max(clean_data),
				np.max(cleaned_data_dict[best_method]),
				np.max(data_with_anomalies[anomaly_indices]))
	ax0.set_ylim(y_min, y_max)
	ax15.set_ylim(y_min, y_max)
	plt.tight_layout(rect=[0, 0, 1, 0.98])
	plt.subplots_adjust(hspace=1.0)
	plt.savefig(f"{os.path.join('Tasks 1-3',dataset_name)}.jpg", dpi=200, bbox_inches='tight')
	plt.close()
	print(f"{dataset_name.upper()}:")
	print("-"*75)
	print(f"Method name{str():<9}|Count of detected anomalies|Count of false detections|")
	print("-"*75)
	for method_name, result in corrected_indices.items():
		tp = len(result['true_positives'])
		fp = len(result['false_positives'])
		tp_percentage = str(f"{tp/len(anomaly_indices)*100:.2f}")
		detected_anomalies = str(f"{tp:<{n_anomalies_width}} ({tp_percentage:<6}%)")
		print(f"{method_name:<20}|{detected_anomalies:<27}|{fp:<25}|")
	print("-"*75)
	best_corrected_count = len(corrected_indices[best_method]['true_positives'])
	best_false_count = len(corrected_indices[best_method]['false_positives'])
	print(f"Best method: {best_method:>20}; detected anomalies: {best_corrected_count} ({best_corrected_count/len(anomaly_indices)*100:.1f}%); false detections: {best_false_count}")
	cleaned_data = cleaned_data_dict[best_method]
	diff_threshold = 0.04 * np.std(clean_data) if dataset_name in ['random_sample', 'linear_additive', 'cubic_additive'] else 0.01
	diff_mask = np.abs(cleaned_data - clean_data) > diff_threshold
	diff_percentage = np.mean(diff_mask) * 100
	mae = np.mean(np.abs(cleaned_data - clean_data))
	print(f"Threshold-based comparison: {diff_percentage:.2f}% values differ (threshold = {diff_threshold:.4f}); MAE: {mae:.4f}")
	different_data = sum(1 for i in range(len(cleaned_data)) if cleaned_data[i] != clean_data[i])
	exact_diff_percentage = (different_data / len(clean_data)) * 100
	print(f"Exact difference comparison: {different_data} values differ ({exact_diff_percentage:.2f}%)")	
	print("-"*90)
	return cleaned_data_dict[best_method]
# ---------- Task 4: Model Quality Evaluation and Optimization ----------	
def evaluate_and_optimize(clean_data, anomalous_data, time_points, dataset_name, trend_type='none'):
	print(f"\nModel Quality Evaluation for {dataset_name}")	   
	# Define anomaly detection methods (excluding ensemble, handled separately)
	anomaly_methods = {
		'Z-score': lambda data, name: z_score_detect(data, name, threshold=2.5 if name in ['random_sample', 'linear_additive', 'cubic_additive'] else 2.3),
		'IQR': iqr_detect,
		'Hampel Filter': lambda data, name: hampel_filter(data, name, n_sigmas=2.5 if name in ['random_sample', 'linear_additive', 'cubic_additive'] else 2.3),
		'Modified Z-score': lambda data, name: modified_z_score_detect(data, name, threshold=2.5 if name in ['random_sample', 'linear_additive', 'cubic_additive'] else 2.3),
		'Rolling Std': rolling_std_detect,
		'Local Outlier Factor': lof_detect,
		'Isolation Forest': isolation_forest_detect,
		'One-Class SVM': one_class_svm_detect,
		'DBSCAN': dbscan_detect,
		'Autoencoder': lambda data, name: autoencoder_detect(data, name, threshold=2.5 if name in ['random_sample', 'linear_additive', 'cubic_additive'] else 2.3)
	}
	# Define polynomial degrees for curve fitting
	degrees = range(1, 9)	
	best_mse = float('inf')
	best_method = None
	best_degree = None
	best_cleaned_data = None
	detector_outputs = {}
	# Grid search over anomaly methods and polynomial degrees
	for method_name, method_func in anomaly_methods.items():
		# Apply anomaly detection
		detected_indices = method_func(anomalous_data, dataset_name)
		detector_outputs[method_name] = detected_indices
		cleaned_data = clean_data_func(anomalous_data, detected_indices, time_points, dataset_name)		
		for degree in degrees:
			# Fit polynomial regression model
			poly_features = PolynomialFeatures(degree=degree)
			X_poly = poly_features.fit_transform(time_points.reshape(-1, 1))
			model = LinearRegression()
			model.fit(X_poly, cleaned_data)
			y_pred = model.predict(X_poly)			
			# Evaluate against original clean data
			mse = mean_squared_error(clean_data, y_pred)			
			if mse < best_mse:
				best_mse = mse
				best_method = method_name
				best_degree = degree
				best_cleaned_data = y_pred	# Store the fitted curve as the restored data	
	# Handle ensemble separately
	ensemble_indices = ensemble_detect(list(detector_outputs.values()), dataset_name, vote_threshold=4)
	cleaned_data = clean_data_func(anomalous_data, ensemble_indices, time_points, dataset_name)
	for degree in degrees:
		poly_features = PolynomialFeatures(degree=degree)
		X_poly = poly_features.fit_transform(time_points.reshape(-1, 1))
		model = LinearRegression()
		model.fit(X_poly, cleaned_data)
		y_pred = model.predict(X_poly)
		mse = mean_squared_error(clean_data, y_pred)
		if mse < best_mse:
			best_mse = mse
			best_method = 'Ensemble (vote≥4)'
			best_degree = degree
			best_cleaned_data = y_pred
	# Output results
	best_config = {
		'anomaly_method': best_method,
		'polynomial_degree': best_degree,
		'mse': best_mse}
	print(f"Dataset: {dataset_name}")
	print(f"Best Anomaly Detection Method: {best_method}")
	print(f"Best Polynomial Degree: {best_degree}")
	print(f"Best MSE: {best_mse:.4f}")
	plt.figure(figsize=(12, 5))
	plt.plot(time_points, best_cleaned_data, color='green', label=f'Оптимізація ({best_method}, ступінь {best_degree})', linewidth=3, alpha=0.7)
	plt.plot(time_points, clean_data, color='black', label='Чиста функція', alpha=0.7)
	# plt.plot(time_points, anomalous_data, 'r.', label='Anomalous Data', alpha=0.5)
	
	plt.title(f'Визначення показників якості моделі ({dataset_name})')
	plt.xlabel('Time')
	plt.ylabel('Value')
	plt.legend(loc='upper left', fontsize=8)
	plt.grid(True, alpha=0.3)
	plt.savefig(f"{os.path.join('Task 4',dataset_name)}.jpg", dpi=200, bbox_inches='tight')
	plt.close()
	return best_cleaned_data, best_config
# ---------- Task 5: Polynomial Regression via LSM ----------
def statistical_learning_lsm_polinomial(clean_data, cleaned_data, data_with_anomalies, anomaly_indices, time_points, dataset_name, optimal_degree, trend_type='none', max_degree=8):
	class LeastSquaresPolynomial(BaseEstimator, RegressorMixin):
		def __init__(self, degree=1):
			self.degree = degree
			self.coef_ = None
		
		def fit(self, X, y):
			try:
				X_poly = np.vander(X.ravel(), self.degree + 1, increasing=True)
				self.coef_, _, _, _ = np.linalg.lstsq(X_poly, y, rcond=None)
			except Exception as e:
				print(f"Error in LeastSquaresPolynomial.fit: {e}")
				self.coef_ = np.zeros(self.degree + 1)
			return self
		
		def predict(self, X):
			try:
				X_poly = np.vander(X.ravel(), self.degree + 1, increasing=True)
				return X_poly @ self.coef_
			except Exception as e:
				print(f"Error in LeastSquaresPolynomial.predict: {e}")
				return np.zeros_like(X.ravel())
		
		def get_params(self, deep=True):
			return {"degree": self.degree}
		
		def set_params(self, **params):
			for param, value in params.items():
				setattr(self, param, value)
			return self
	
	X = time_points
	y = cleaned_data
	y_clean = y.copy()
	if dataset_name in ['linear_trend', 'cubic_trend']:
		np.random.seed(42)
		y_clean += np.random.normal(0, 0.01, len(y))
	
	models = []
	mse_scores = []
	r2_scores = []
	cv_scores = []
	for degree in range(1, optimal_degree + 1):
		model = LeastSquaresPolynomial(degree=degree)
		model.fit(X, y_clean)
		y_pred = model.predict(X)
		mse = mean_squared_error(y_clean, y_pred)
		r2 = r2_score(y_clean, y_pred)
		try:
			cv_score = np.mean(cross_val_score(model, X.reshape(-1, 1), y_clean, cv=5, scoring='neg_mean_squared_error'))
		except Exception as e:
			print(f"Warning: Cross-validation failed for degree {degree} in {dataset_name}: {e}")
			cv_score = float('inf')
		models.append(model)
		mse_scores.append(mse)
		r2_scores.append(r2)
		cv_scores.append(-cv_score if cv_score != float('inf') else float('inf'))
	
	best_idx = np.argmin(cv_scores)
	best_model = models[best_idx]
	best_degree = best_model.degree
	best_mse = mse_scores[best_idx]
	best_r2 = r2_scores[best_idx]
	best_cv_score = -cv_scores[best_idx] if cv_scores[best_idx] != float('inf') else None
	
	# Print detailed results
	print(f"Statistical Learning Results for {dataset_name.upper()}:")
	print(f"Optimal Polynomial Degree: {best_degree}")
	print(f"Mean Squared Error (MSE): {best_mse:.4f}")
	print(f"R² Score: {best_r2:.4f}")
	if best_cv_score is not None:
		print(f"Cross-Validation MSE (5-fold): {best_cv_score:.4f}")
	else:
		print("Cross-Validation MSE: Not available due to earlier failure")
	print(f"Trend Type: {trend_type}")
	print('-'*90)
	# Generate predictions for plotting
	y_pred_best = best_model.predict(X)
	
	# Create a plot
	plt.figure(figsize=(12, 6))	 # Wider figure for better visibility
	plt.plot(time_points, y_pred_best, color='green', label=f'Прогноз (ступінь {best_degree})', alpha=0.7, linewidth=4)
	plt.plot(time_points, y_clean, color='black', label='Очищені дані', alpha=0.7)	
	plt.scatter(time_points[anomaly_indices], data_with_anomalies[anomaly_indices], color='red', s=25, label='Аномалії', zorder=5)	
	plt.title(f'Polynomial Regression Fit for {dataset_name.upper()} (Degree {best_degree})', fontsize=14, pad=10)
	plt.xlabel('Time', fontsize=12)
	plt.ylabel('Value', fontsize=12)
	plt.legend(loc='best', fontsize=10)
	plt.grid(True, linestyle='--', alpha=0.7)
	
	# Adjust y-limits to include anomalies
	y_min = min(np.min(y_clean), np.min(y_pred_best), np.min(cleaned_data[anomaly_indices]))
	y_max = max(np.max(y_clean), np.max(y_pred_best), np.max(cleaned_data[anomaly_indices]))
	plt.ylim(y_min - 0.1 * (y_max - y_min), y_max + 0.1 * (y_max - y_min))	# Add padding
	plt.savefig(f"{os.path.join('Task 5', f'{dataset_name}.jpg')}", dpi=300, bbox_inches='tight')
	plt.close()
	
	return best_model
# ---------- Task 6: Forecasting ----------
def extrapolate_data(clean_data, data_with_anomalies, anomaly_indices, time_points, model, dataset_name, trend_type='none'):
	# Generate extended time points
	n_extended = int(1.5 * len(time_points))  # Assuming n_samples is len(time_points)
	time_points_extended = np.linspace(0, 15, n_extended)
	print(f"Extrapolation for {dataset_name.upper()}:")
	print(f"Number of extended time points: {n_extended}")
	print(f"Time range: 0 to {time_points_extended[-1]:.1f}")
	# Split time points into fitted (0 to 10) and extrapolated (>10) regions
	mask_fitted = time_points_extended <= 10
	mask_extrapolated = time_points_extended > 10
	time_points_fitted = time_points_extended[mask_fitted]
	time_points_extrapolated = time_points_extended[mask_extrapolated]
	print(f"Number of fitted points: {len(time_points_fitted)}")
	print(f"Number of extrapolated points: {len(time_points_extrapolated)}")
	# Predict using the model
	y_pred_extended = model.predict(time_points_extended)
	y_pred_fitted = model.predict(time_points_fitted)
	y_pred_extrapolated = model.predict(time_points_extrapolated)
	print(f"Prediction range (extended): Min = {np.min(y_pred_extended):.2f}, Max = {np.max(y_pred_extended):.2f}")
	print('-'*90)
	plt.figure(figsize=(12, 5))
	plt.plot(time_points_fitted, y_pred_fitted, color='green', label='Оптимізація', linewidth=4, alpha=0.7)
	plt.plot(time_points, clean_data, color='black', label='Чиста функція', alpha=0.7)
	plt.scatter(time_points[anomaly_indices], data_with_anomalies[anomaly_indices], color='red', s=25, label='Аномалії')
	plt.plot(time_points_extrapolated, y_pred_extrapolated, linewidth=4, linestyle='--', color='blue', label='Екстраполяція', alpha=0.7)
	plt.axvline(x=10, color='gray', linestyle='--', alpha=0.5, label='Кінець тренувальних даних')
	plt.title(f'Extrapolation for {dataset_name}')
	plt.xlabel('Time')
	plt.ylabel('Value')
	plt.legend(loc='upper left', fontsize=8)
	# Set y-limits based on data
	y_min = min(np.min(clean_data), np.min(data_with_anomalies), np.min(y_pred_extended))
	y_max = max(np.max(clean_data), np.max(data_with_anomalies), np.max(y_pred_extended))
	plt.ylim(y_min - 0.1 * (y_max - y_min), y_max + 0.1 * (y_max - y_min))	# Add padding
	# Save plot
	os.makedirs('Task 6', exist_ok=True)
	plt.savefig(f"{os.path.join('Task 6', f'extrapolation_{dataset_name}.jpg')}", dpi=300, bbox_inches='tight')
	plt.close()
	return time_points_extended, y_pred_extended
# ----- Task 7: Smoothing function with Alpha-Beta or Alpha-Beta-Gamma filter -----
def smooth_data(clean_data, data_with_anomalies, anomaly_indices, time_points, polynomial_degree, dataset_name, trend_type='none'):	
	# Select filter based on degree
	use_gamma = polynomial_degree == 3 and dataset_name in ['cubic_trend', 'cubic_additive']
	filter_name = 'Alpha-Beta-Gamma' if use_gamma else 'Alpha-Beta'
	print(f"Smoothing {dataset_name} with {filter_name} filter (polynomial_degree={polynomial_degree})")	
	# Initialize filter parameters
	alpha = 0.5
	beta = 0.1
	gamma = 0.01 if use_gamma else 0.0
	dt = time_points[1] - time_points[0]  # Time step
	# Divergence prevention thresholds (based on clean data std)
	sigma = np.std(clean_data)
	error_threshold_tune = 2 * sigma
	error_threshold_reset = 5 * sigma
	anomaly_weight = 0.1  # Scale alpha, beta, gamma at anomaly indices	
	def apply_filter(data, anomaly_indices):
		smoothed = np.zeros_like(data)
		velocity = 0.0
		acceleration = 0.0 if use_gamma else 0.0
		smoothed[0] = data[0]  # Initialize with first observation		
		for i in range(1, len(data)):
			# Predict next state
			pred = smoothed[i-1] + velocity * dt + (0.5 * acceleration * dt**2 if use_gamma else 0.0)
			velocity_pred = velocity + (acceleration * dt if use_gamma else 0.0)			
			# Compute error
			error = data[i] - pred			
			# Adjust parameters for anomalies
			curr_alpha = alpha * anomaly_weight if i in anomaly_indices else alpha
			curr_beta = beta * anomaly_weight if i in anomaly_indices else beta
			curr_gamma = gamma * anomaly_weight if i in anomaly_indices and use_gamma else gamma			
			# Divergence prevention: adaptive tuning
			if abs(error) > error_threshold_tune:
				curr_alpha *= 0.9
				curr_beta *= 0.9
				if use_gamma:
					curr_gamma *= 0.9			
			# Divergence prevention: reset
			if abs(error) > error_threshold_reset:
				smoothed[i] = data[i]
				velocity = 0.0
				acceleration = 0.0 if use_gamma else 0.0
				continue			
			# Update state
			smoothed[i] = pred + curr_alpha * error
			velocity = velocity_pred + (curr_beta / dt) * error
			if use_gamma:
				acceleration += (curr_gamma / (dt**2)) * error		
		return smoothed	
	# Apply filter to both datasets
	smoothed_clean = apply_filter(clean_data, anomaly_indices)
	smoothed_anomalous = apply_filter(data_with_anomalies, anomaly_indices)	
	# Plotting with two subplots
	plt.figure(figsize=(12, 8))
	gs = gridspec.GridSpec(2, 1, height_ratios=[1, 1])	
	# Subplot 1: Clean Data and Smoothed Clean Data
	ax1 = plt.subplot(gs[0])
	ax1.plot(time_points, clean_data, color='black', label='Чиста функція', alpha=0.7)
	ax1.plot(time_points, smoothed_clean, color='red', label=f'Згладжені дані ({filter_name})', alpha=0.7)
	ax1.set_title(f'Clean Data Smoothing for {dataset_name}')
	ax1.set_xlabel('Time')
	ax1.set_ylabel('Value')
	ax1.legend(loc='upper left', fontsize=8)
	ax1.grid(True, alpha=0.3)	
	# Subplot 2: Anomalous Data and Smoothed Anomalous Data
	ax2 = plt.subplot(gs[1])
	ax2.plot(time_points, data_with_anomalies, color='black', label='Дані з аномаліями', alpha=0.5)
	ax2.scatter(time_points[anomaly_indices], data_with_anomalies[anomaly_indices], color='red', s=25, label='Аномалії')
	ax2.plot(time_points, smoothed_anomalous, color='red', label=f'Згладжені дані ({filter_name})', alpha=0.7)
	ax2.set_title(f'Anomalous Data Smoothing for {dataset_name}')
	ax2.set_xlabel('Time')
	ax2.set_ylabel('Value')
	ax2.legend(loc='upper left', fontsize=8)
	ax2.grid(True, alpha=0.3)
	# Set y-limits for consistency
	y_min = min(np.min(clean_data), np.min(data_with_anomalies), np.min(smoothed_clean), np.min(smoothed_anomalous))
	y_max = max(np.max(clean_data), np.max(data_with_anomalies), np.max(smoothed_clean), np.max(smoothed_anomalous))
	ax1.set_ylim(y_min - 0.1 * (y_max - y_min), y_max + 0.1 * (y_max - y_min))
	ax2.set_ylim(y_min - 0.1 * (y_max - y_min), y_max + 0.1 * (y_max - y_min))
	# Save plot
	plt.tight_layout()
	plt.savefig(f"{os.path.join('Task 7', f'smoothing_{dataset_name}.jpg')}", dpi=300, bbox_inches='tight')
	plt.close()
	# Compute MSE for smoothed data
	mse_clean = mean_squared_error(clean_data, smoothed_clean)
	mse_anomalous = mean_squared_error(clean_data, smoothed_anomalous)
	print(f"MSE for Smoothed Clean Data: {mse_clean:.4f}")
	print(f"MSE for Smoothed Anomalous Data: {mse_anomalous:.4f}")
	return smoothed_clean, smoothed_anomalous
def custom_non_linear_model(clean_data, anomalous_data, anomaly_indices, time_points, dataset_name):
	def custom_model(x, a, b, c):
		return a * np.exp(b * x) + c	
	def fit_dataset(x, y, dataset_name):
		if dataset_name.startswith('random_sample'):
			def custom_model(x, c): return np.full_like(x, c)
			p0 = [np.mean(y)]
			bounds = ([-np.inf], [np.inf])
		elif dataset_name.startswith('linear_trend') or dataset_name.startswith('linear_additive'):
			def custom_model(x, a, b): return a * x + b
			p0 = [1.0, np.mean(y)]
			bounds = ([-np.inf, -np.inf], [np.inf, np.inf])
		else:
			def custom_model(x, a, b, c): return a * np.exp(b * x) + c
			p0 = [1.0, 0.01, np.mean(y)]
			bounds = ([-np.inf, -1, -np.inf], [np.inf, 1, np.inf])		
		try:
			params, _ = curve_fit(custom_model, x, y, p0=p0, maxfev=10000, bounds=bounds)
			y_pred = custom_model(x, *params)
			mse = np.mean((y - y_pred) ** 2)
			r2 = 1 - np.sum((y - y_pred) ** 2) / np.sum((y - np.mean(y)) ** 2)
		except Exception as e:
			print(f"Fit failed for {dataset_name}: {e}")
			params = [np.nan] * (2 if dataset_name.startswith(('linear_trend', 'linear_additive')) else 1 if dataset_name.startswith('random_sample') else 3)
			mse, r2 = np.nan, np.nan
			y_pred = np.zeros_like(y)
		params = list(params) + [np.nan] * (3 - len(params))
		return params, mse, r2, y_pred	
	# Fit both datasets
	params_clean, mse_clean, r2_clean, y_pred_clean = fit_dataset(time_points, clean_data, f"{dataset_name}_clean")
	params_anom, mse_anom, r2_anom, y_pred_anom = fit_dataset(time_points, anomalous_data, f"{dataset_name}_anomalies")	
	# Pad parameters for consistent DataFrame
	params_clean = params_clean + [np.nan] * (3 - len(params_clean))
	params_anom = params_anom + [np.nan] * (3 - len(params_anom))	
	# Table for comparison
	df = pd.DataFrame([
		{"Dataset name": f"{dataset_name}_clean", "a": params_clean[0], "b": params_clean[1], "c": params_clean[2], "MSE": mse_clean, "R²": r2_clean},
		{"Dataset name": f"{dataset_name}_anomalies", "a": params_anom[0], "b": params_anom[1], "c": params_anom[2], "MSE": mse_anom, "R²": r2_anom}])
	print(f"Custom Nonlinear fit results: {dataset_name}")
	for _, row in df.iterrows():
		print(f"{row['Dataset name']}: a={row['a']:.4f}, b={row['b']:.4f}, c={row['c']:.4f}, MSE={row['MSE']:.6f}, R²={row['R²']:.3f}")
	print('-'*86)
	plt.figure(figsize=(12, 8))
	gs = gridspec.GridSpec(2, 1, height_ratios=[1, 1])	
	# Subplot 1: Clean Data and Fitted Clean Data
	ax1 = plt.subplot(gs[0])
	ax1.plot(time_points, y_pred_clean, color='green', linewidth=4, label="Оптимізація", alpha=0.7)
	ax1.plot(time_points, clean_data, color='black', label="Чиста функція", alpha=0.7)	
	ax1.set_title(f"Оптимізація: {dataset_name}")
	ax1.set_xlabel('Time')
	ax1.set_ylabel('Value')
	ax1.legend(loc='upper left', fontsize=8)
	ax1.grid(True, alpha=0.3)	
	# Subplot 2: Anomalous Data and Fitted Anomalous Data
	ax2 = plt.subplot(gs[1])
	ax2.plot(time_points, y_pred_anom, color='green', linewidth=4, label="Оптимізація", alpha=0.7)
	ax2.plot(time_points, anomalous_data, color='black', label="Дані з аномаліями", alpha=0.5)
	ax2.scatter(time_points[anomaly_indices], anomalous_data[anomaly_indices], color='red', s=25, label='Аномалії')	
	ax2.set_title(f"Оптимізація: {dataset_name} (дані з аномаліями)")
	ax2.set_xlabel('Time')
	ax2.set_ylabel('Value')
	ax2.legend(loc='upper left', fontsize=8)
	ax2.grid(True, alpha=0.3)	
	# Synchronize y-limits
	y_min = min(np.min(clean_data), np.min(anomalous_data), np.min(y_pred_clean), np.min(y_pred_anom))
	y_max = max(np.max(clean_data), np.max(anomalous_data), np.max(y_pred_clean), np.max(y_pred_anom))
	ax1.set_ylim(y_min - 0.1 * (y_max - y_min), y_max + 0.1 * (y_max - y_min))
	ax2.set_ylim(y_min - 0.1 * (y_max - y_min), y_max + 0.1 * (y_max - y_min))	
	plt.tight_layout()
	plt.savefig(f"{os.path.join('Task 8', f'{dataset_name}.jpg')}", dpi=300, bbox_inches='tight')
	plt.close()	
	return df
start=datetime.now()
print("COUNT OF SAMPLES: ",n_samples,"; COUNT OF ANOMALIES: ",n_anomalies)
print('='*40, "TASK 1", '='*40, sep='', flush=True)
if not os.path.exists("Tasks 1-3"):
	os.makedirs("Tasks 1-3")
if not os.path.exists("Task 4"):
	os.makedirs("Task 4")
if not os.path.exists("Task 5"):
	os.makedirs("Task 5")
if not os.path.exists("Task 6"):
	os.makedirs("Task 6")
if not os.path.exists("Task 7"):
	os.makedirs("Task 7")
if not os.path.exists("Task 8"):
	os.makedirs("Task 8")
# ---------- Parameters ----------
time_points = np.linspace(0, 10, n_samples)
random_params = {'mean': 0, 'std_dev': 2.5}
linear_params = {'a': 1.5, 'b': 5.0}
cubic_params = {'a': 0.02, 'b': -0.1, 'c': 0.8, 'd': 3.0}
# ---------- Generate Base Signals ----------
np.random.seed(42)
random_sample = np.random.normal(loc=random_params['mean'], scale=random_params['std_dev'], size=n_samples)
linear_trend = linear_params['a'] * time_points + linear_params['b']
cubic_trend = (cubic_params['a'] * time_points**3 +
			   cubic_params['b'] * time_points**2 +
			   cubic_params['c'] * time_points +
			   cubic_params['d'])
linear_additive = linear_trend + random_sample
cubic_additive = cubic_trend + random_sample
print('='*40, "TASK 2", '='*40, sep='', flush=True)
# ---------- Inject Anomalies ----------
random_sample_anomalies, idx_random = inject_anomalies(random_sample)
linear_trend_anomalies, idx_linear = inject_anomalies(linear_trend)
cubic_trend_anomalies, idx_cubic = inject_anomalies(cubic_trend)
linear_additive_anomalies, idx_lin_add = inject_anomalies(linear_additive)
cubic_additive_anomalies, idx_cub_add = inject_anomalies(cubic_additive)
# ---------- Plotting All Datasets ----------
fig = plt.figure(figsize=(15, 12))
gs = gridspec.GridSpec(3, 2, height_ratios=[1, 1, 1])
ax1 = fig.add_subplot(gs[0, 0])
ax2 = fig.add_subplot(gs[0, 1])
ax3 = fig.add_subplot(gs[1, 0])
ax4 = fig.add_subplot(gs[1, 1])
ax5 = fig.add_subplot(gs[2, :])
# ax1.plot(time_points, random_sample_anomalies, color='black', label='З аномаліями')
ax1.plot(time_points, random_sample, color='black', label='Чиста функція', alpha=0.7)
ax1.scatter(time_points[idx_random], random_sample_anomalies[idx_random], 
	color='red', s=25, label='Аномалії')
ax1.set_title('1. Випадкова величина (нормальний розподіл)')
# ax2.plot(time_points, linear_trend_anomalies, color='black', label='З аномаліями')
ax2.plot(time_points, linear_trend, color='black', label='Чиста функція', alpha=0.7)
ax2.scatter(time_points[idx_linear], linear_trend_anomalies[idx_linear], color='red', s=25, label='Аномалії')
ax2.set_title('2. Лінійний тренд')
# ax3.plot(time_points, cubic_trend_anomalies, color='black', label='З аномаліями')
ax3.plot(time_points, cubic_trend, color='black', label='Чиста функція', alpha=0.7)
ax3.scatter(time_points[idx_cubic], cubic_trend_anomalies[idx_cubic], color='red', s=25, label='Аномалії')
ax3.set_title('3. Кубічний тренд')
# ax4.plot(time_points, linear_additive_anomalies, color='black', label='З аномаліями')
ax4.plot(time_points, linear_additive, color='black', label='Чиста функція', alpha=0.7)
ax4.scatter(time_points[idx_lin_add], linear_additive_anomalies[idx_lin_add], color='red', s=25, label='Аномалії')
ax4.set_title('4. Лінійна адитивна модель (тренд + шум)')
# ax5.plot(time_points, cubic_additive_anomalies, color='black', label='З аномаліями')
ax5.plot(time_points, cubic_additive, color='black', label='Чиста функція', alpha=0.7)
ax5.scatter(time_points[idx_cub_add], cubic_additive_anomalies[idx_cub_add], color='red', s=25, label='Аномалії')
ax5.set_title('5. Кубічна адитивна модель (тренд + шум)')
handles = [
	# plt.Line2D([0], [0], marker='.', color='b', linestyle='none', label='З аномаліями'),
	plt.Line2D([0], [0], color='g', linestyle='-', alpha=0.7, label='Чиста функція'),
	plt.Line2D([0], [0], marker='o', color='red', linestyle='none', markersize=5, label='Аномалії')]
fig.legend(handles, [h.get_label() for h in handles], loc='lower center', ncol=3, bbox_to_anchor=(0.5, -0.05))
plt.xlabel('Час')
plt.tight_layout()
plt.savefig(f"{os.path.join('Tasks 1-3', 'all_models_with_anomalies.jpg')}", dpi=200, bbox_inches='tight')
plt.close()
results = {}
results['task_3'] = {}
results['task_4'] = {}
results['task_5'] = {}
results['task_6'] = {}
results['task_7'] = {}
results['task_8'] = {}
# ---------- Run Anomaly Detection and Collect Cleaned Data ----------
print('='*40, "TASK 3", '='*40, sep='', flush=True)
results['task_3']['random_sample'] = detect_and_remove_anomalies(random_sample, random_sample_anomalies, idx_random, time_points, "random_sample", trend_type='none')
results['task_3']['linear_trend'] = detect_and_remove_anomalies(linear_trend, linear_trend_anomalies, idx_linear, time_points, "linear_trend", trend_type='linear')
results['task_3']['cubic_trend'] = detect_and_remove_anomalies(cubic_trend, cubic_trend_anomalies, idx_cubic, time_points, "cubic_trend", trend_type='cubic')
results['task_3']['linear_additive'] = detect_and_remove_anomalies(linear_additive, linear_additive_anomalies, idx_lin_add, time_points, "linear_additive", trend_type='linear')
results['task_3']['cubic_additive'] = detect_and_remove_anomalies(cubic_additive, cubic_additive_anomalies, idx_cub_add, time_points, "cubic_additive", trend_type='cubic')
# ---------- Task 4: Model Quality Evaluation and Optimization ----------
print('='*40, "TASK 4", '='*40, sep='', flush=True)
results['task_4']['random_sample'] = evaluate_and_optimize(random_sample, random_sample_anomalies, time_points, "random_sample", trend_type='none')
results['task_4']['linear_trend'] = evaluate_and_optimize(linear_trend, linear_trend_anomalies, time_points, "linear_trend", trend_type='linear')
results['task_4']['cubic_trend'] = evaluate_and_optimize(cubic_trend, cubic_trend_anomalies, time_points, "cubic_trend", trend_type='cubic')
results['task_4']['linear_additive'] = evaluate_and_optimize(linear_additive, linear_additive_anomalies, time_points, "linear_additive", trend_type='linear')
results['task_4']['cubic_additive'] = evaluate_and_optimize(cubic_additive, cubic_additive_anomalies, time_points, "cubic_additive", trend_type='cubic')
# ---------- Task 5: Polynomial Regression via LSM ----------
print('='*40, "TASK 5", '='*40, sep='', flush=True)
results['task_5']['random_sample'] = statistical_learning_lsm_polinomial(random_sample, results['task_3']['random_sample'], random_sample_anomalies, idx_random, time_points, "random_sample", results['task_4']['random_sample'][1]['polynomial_degree'], trend_type='none')
results['task_5']['linear_trend'] = statistical_learning_lsm_polinomial(linear_trend, results['task_3']['linear_trend'], linear_trend_anomalies, idx_linear, time_points, "linear_trend", results['task_4']['linear_trend'][1]['polynomial_degree'], trend_type='linear')
results['task_5']['cubic_trend'] = statistical_learning_lsm_polinomial(cubic_trend, results['task_3']['cubic_trend'], cubic_trend_anomalies, idx_cubic, time_points, "cubic_trend", results['task_4']['cubic_trend'][1]['polynomial_degree'], trend_type='cubic')
results['task_5']['linear_additive'] = statistical_learning_lsm_polinomial(linear_additive, results['task_3']['linear_additive'], linear_additive_anomalies, idx_lin_add, time_points, "linear_additive", results['task_4']['linear_additive'][1]['polynomial_degree'], trend_type='linear')
results['task_5']['cubic_additive'] = statistical_learning_lsm_polinomial(cubic_additive, results['task_3']['cubic_additive'], cubic_additive_anomalies, idx_cub_add, time_points, "cubic_additive", results['task_4']['cubic_additive'][1]['polynomial_degree'], trend_type='cubic')
# ---------- Task 6: Extrapolation ----------
print('='*40, "TASK 6", '='*40, sep='', flush=True)
results['task_6']['random_sample'] = extrapolate_data(random_sample, random_sample_anomalies, idx_random, time_points, results['task_5']['random_sample'], "random_sample", trend_type='none')
results['task_6']['linear_trend'] = extrapolate_data(linear_trend, linear_trend_anomalies, idx_linear, time_points, results['task_5']['linear_trend'], "linear_trend", trend_type='linear')
results['task_6']['cubic_trend'] = extrapolate_data(cubic_trend, cubic_trend_anomalies, idx_cubic, time_points, results['task_5']['cubic_trend'], "cubic_trend", trend_type='cubic')
results['task_6']['linear_additive'] = extrapolate_data(linear_additive, linear_additive_anomalies, idx_lin_add, time_points, results['task_5']['linear_additive'], "linear_additive", trend_type='linear')
results['task_6']['cubic_additive'] = extrapolate_data(cubic_additive, cubic_additive_anomalies, idx_cub_add, time_points, results['task_5']['cubic_additive'], "cubic_additive", trend_type='cubic')
# ---------- Task 7: Smoothing ----------
print('='*40, "TASK 7", '='*40, sep='', flush=True)
results['task_7']['random_sample'] = smooth_data(random_sample, random_sample_anomalies, idx_random, time_points, results['task_4']['random_sample'][1]['polynomial_degree'], "random_sample", trend_type='none')
results['task_7']['linear_trend'] = smooth_data(linear_trend, linear_trend_anomalies, idx_linear, time_points, results['task_4']['linear_trend'][1]['polynomial_degree'], "linear_trend", trend_type='linear')
results['task_7']['cubic_trend'] = smooth_data(cubic_trend, cubic_trend_anomalies, idx_cubic, time_points, results['task_4']['cubic_trend'][1]['polynomial_degree'], "cubic_trend", trend_type='cubic')
results['task_7']['linear_additive'] = smooth_data(linear_additive, linear_additive_anomalies, idx_lin_add, time_points, results['task_4']['linear_additive'][1]['polynomial_degree'], "linear_additive", trend_type='linear')
results['task_7']['cubic_additive'] = smooth_data(cubic_additive, cubic_additive_anomalies, idx_cub_add, time_points, results['task_4']['cubic_additive'][1]['polynomial_degree'], "cubic_additive", trend_type='cubic')
print('='*40, "TASK 8", '='*40, sep='', flush=True)
results['task_8']['random_sample'] = custom_non_linear_model(random_sample, random_sample_anomalies, idx_random, time_points, "random_sample")
results['task_8']['linear_trend'] = custom_non_linear_model(linear_trend, linear_trend_anomalies, idx_linear, time_points, "linear_trend")
results['task_8']['cubic_trend'] = custom_non_linear_model(cubic_trend, cubic_trend_anomalies, idx_cubic, time_points, "cubic_trend")
results['task_8']['linear_additive'] = custom_non_linear_model(linear_additive, linear_additive_anomalies, idx_lin_add, time_points, "linear_additive")
results['task_8']['cubic_additive'] = custom_non_linear_model(cubic_additive, cubic_additive_anomalies, idx_cub_add, time_points, "cubic_additive")
duration=datetime.now()-start
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
hours,minutes,seconds=ConvertTimeDelta(duration)
print("TIME: ",hours,":",minutes,":",seconds)