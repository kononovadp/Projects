"""Розробити програмний скрипт мовою Python що забезпечує аналіз властивостей і характеристик вихідних даних відповідно до етапів:
1. Модель генерації випадкової величини за рівномірним нормальним законом розподілу;
2. Модель зміни (ідеальний тренд) досліджуваного процесу за кубічним, лінійним законом;
3. Адитивна модель статистичної вибірки відповідно до синтезованих в п.1,2 моделей випадкової (стохастична) і невипадкової складових. Параметри закону розподілу та закону зміни досліджуваного процесу обрати самостійно.
4. Визначення статистичних (числових) характеристик сформованих в п.1,3 вибірок (дисперсія, середньоквадратичне відхилення, математичне очікування, гістограма закону розподілу).
5. Визначення статистичних характеристик реальних даних, заданих файлом Oschadbank (USD).xls за умов табл. 1 додатку 1.
6. Провести аналіз отриманих результатів та верифікацію розробленого скрипта."""
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
import pandas as pd
import warnings
warnings.filterwarnings('ignore')
n_samples = 1000
time_points = np.linspace(0, 10, n_samples)
# Параметри для генерації випадкових величин
random_params = {
	'mean': 0, # математичне очікування
	'std_dev': 2.5} # стандартне відхилення
# Параметри для трендових моделей
linear_params = {
	'a': 1.5, # коефіцієнт нахилу
	'b': 5.0} # зсув
cubic_params = {
	'a': 0.02, # коефіцієнт при x³
	'b': -0.1, # коефіцієнт при x²
	'c': 0.8, # коефіцієнт при x
	'd': 3.0} # константа
print("1. МОДЕЛЬ ГЕНЕРАЦІЇ ВИПАДКОВОЇ ВЕЛИЧИНИ ЗА РІВНОМІРНИМ НОРМАЛЬНИМ ЗАКОНОМ РОЗПОДІЛУ")
print("Параметри нормального розподілу:")
print("  - Математичне очікування: ", random_params['mean'])
print("  - Стандартне відхилення: ", random_params['std_dev'])
random_sample = np.random.normal(
	loc=random_params['mean'],
	scale=random_params['std_dev'],
	size=n_samples)
print("-" * 90)
print("2.1 МОДЕЛЬ ЗМІНИ (ІДЕАЛЬНИЙ ТРЕНД) ДОСЛІДЖУВАНОГО ПРОЦЕСУ ЗА ЛІНІЙНИМ ЗАКОНОМ")
print("    y = ",linear_params['a'],"x + ",linear_params['b'],sep='')
linear_trend = (linear_params['a'] * time_points + 
	linear_params['b'])
print("2.2 МОДЕЛЬ ЗМІНИ (ІДЕАЛЬНИЙ ТРЕНД) ДОСЛІДЖУВАНОГО ПРОЦЕСУ ЗА КУБІЧНИМ ЗАКОНОМ")
print("    y = ",cubic_params['a'],"x³ + ",cubic_params['b'],"x² + ",cubic_params['c'],"x + ",cubic_params['d'],sep='')
cubic_trend = (cubic_params['a'] * time_points**3 + 
	cubic_params['b'] * time_points**2 + 
	cubic_params['c'] * time_points + 
	cubic_params['d'])
print("-" * 90)
print("3. АДИТИВНІ МОДЕЛІ:")
print("  - Лінійна адитивна: лінійний тренд + випадкова складова")
print("  - Кубічна адитивна: кубічний тренд + випадкова складова")
linear_additive = linear_trend + random_sample
cubic_additive = cubic_trend + random_sample
print("-" * 90)
plt.rcParams['font.family'] = 'DejaVu Sans'
plt.rcParams['axes.unicode_minus'] = False
def output_statistics(data, name):
	# дисперсія, середньоквадратичне відхилення, математичне очікування, гістограма закону розподілу
	stats_dict = {
		'variance': np.var(data, ddof=1),
		'std_dev': np.std(data, ddof=1),
		'mean': np.mean(data)}
	plt.figure(figsize=(10, 6))
	plt.title('Гістограма закону розподілу\n'+name)
	plt.xlabel('Значення')
	plt.ylabel('Щільність')
	plt.hist(data, bins=30, density=True, alpha=0.7, color='skyblue', edgecolor='black')
	plt.grid(True)
	plt.tight_layout()
	plt.savefig(name + ".jpg", dpi=200)
	plt.close()	
	print("NAME:", name)
	print("  Дисперсія: ",f"{stats_dict['variance']:.4f}")
	print("  Середньоквадратичне відхилення: ",f"{stats_dict['std_dev']:.4f}")
	print("  Математичне очікування: ",f"{stats_dict['mean']:.4f}")	
	if len(data) <= 5000:
		shapiro_stat, shapiro_p = stats.shapiro(data)
		print("  Тест Шапіро-Вілка: ", 'нормальний розподіл' if shapiro_p > 0.05 else 'не нормальний розподіл')
	jb_stat, jb_p = stats.jarque_bera(data)
	print("  Тест Жака-Бера:", 'нормальний розподіл' if jb_p > 0.05 else 'не нормальний розподіл')
	return stats_dict
print("4. Статистичні (числові) характеристики вибірок, сформованих в п.1-3")
output_statistics(random_sample, "Випадкова величина (нормальний розподіл)")
output_statistics(linear_additive, "Лінійна адитивна модель")
output_statistics(cubic_additive, "Кубічна адитивна модель")
print("-" * 90)
print("4. Статистичні характеристики реальних даних, заданих файлом Oschadbank (USD).xls")
bank_data = pd.read_excel("Oschadbank (USD).xls")
output_statistics(bank_data["Купівля"], "Купівля")
output_statistics(bank_data["Продаж"], "Продаж")
output_statistics(bank_data["КурсНбу"], "Курс НБУ")