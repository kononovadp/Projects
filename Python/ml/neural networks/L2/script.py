import numpy as np
import matplotlib.pyplot as plt
from tensorflow import keras
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Input
from tensorflow.keras.optimizers import Adam
from sklearn.metrics import mean_squared_error
import tensorflow as tf
from tensorflow.keras.layers import Concatenate, Layer
from tensorflow.keras.models import Model
from datetime import datetime
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def target_function(x, y):
	return x**2 + y**2
def generate_training_data(start=0, end=10, step=0.1):
	x = np.arange(start, end, step)
	y = np.arange(start, end, step)
	X, Y = np.meshgrid(x, y)
	x_flat = X.flatten()
	y_flat = Y.flatten()
	z_flat = target_function(x_flat, y_flat)
	inputs = np.column_stack((x_flat, y_flat))	
	return inputs, z_flat, X, Y
class ElmanLayer(Layer):
	def __init__(self, units, **kwargs):
		super(ElmanLayer, self).__init__(**kwargs)
		self.units = units
		self.state = None		
	def build(self, input_shape):
		self.input_dim = input_shape[-1]
		self.kernel = self.add_weight(
			shape=(self.input_dim + self.units, self.units),
			initializer='uniform',
			name='kernel')
		self.bias = self.add_weight(
			shape=(self.units,),
			initializer='zeros',
			name='bias')
		self.built = True		
	def call(self, inputs, states=None, training=None):
		batch_size = tf.shape(inputs)[0]
		if self.state is None or states is None:
			self.state = tf.zeros((batch_size, self.units))
		else:
			self.state = states
		concat = tf.concat([inputs, self.state], axis=1)
		output = tf.matmul(concat, self.kernel) + self.bias
		output = tf.nn.tanh(output)
		self.state = output		
		return output	
	def get_config(self):
		config = super(ElmanLayer, self).get_config()
		config.update({'units': self.units})
		return config
def create_feedforward_model(hidden_neurons):
	model = Sequential([
		Input(shape=(2,)),
		Dense(hidden_neurons, activation='relu'),
		Dense(1)])
	model.compile(optimizer=Adam(learning_rate=0.001), loss='mse')
	return model
def create_cascade_model(hidden_layers):
	input_layer = Input(shape=(2,))
	x = input_layer
	for units in hidden_layers:
		layer_output = Dense(units, activation='relu')(x)
		if x is not input_layer:
			x = Concatenate()([x, layer_output])
		else:
			x = layer_output
	output = Dense(1)(x)
	model = Model(inputs=input_layer, outputs=output)
	model.compile(optimizer=Adam(learning_rate=0.001), loss='mse')
	return model
def create_elman_model(hidden_layers):
	input_layer = Input(shape=(2,))
	x = input_layer	
	for units in hidden_layers:
		x = ElmanLayer(units)(x)		
	output = Dense(1)(x)
	model = Model(inputs=input_layer, outputs=output)
	model.compile(optimizer=Adam(learning_rate=0.001), loss='mse')
	return model
def train_and_evaluate(model, model_name):
	history = model.fit(
		X_train, y_train,
		epochs=500,
		batch_size=32,
		verbose=0,
		validation_data=(X_test, y_test))
	predictions = model.predict(X_test).flatten()
	mse = mean_squared_error(y_test, predictions)
	relative_error = np.mean(np.abs((y_test - predictions) / (y_test + 1e-10))) * 100	
	print(f"Model: {model_name}")
	print(f"MSE: {mse:.6f}")
	print(f"Relative Error: {relative_error:.2f}%\n")	
	return relative_error, history
start = datetime.now()
np.random.seed(42)
tf.random.set_seed(42)
X_train, y_train, X_grid, Y_grid = generate_training_data(0, 10, 0.2)
X_test, y_test, _, _ = generate_training_data(0.1, 10, 0.2)
results = {}
print("Testing Feed Forward Networks:")
model_ff_10 = create_feedforward_model(10)
rel_error_ff_10, history_ff_10 = train_and_evaluate(model_ff_10, "Feed Forward (10 neurons)")
results["Feed Forward (10 neurons)"] = rel_error_ff_10
model_ff_20 = create_feedforward_model(20)
rel_error_ff_20, history_ff_20 = train_and_evaluate(model_ff_20, "Feed Forward (20 neurons)")
results["Feed Forward (20 neurons)"] = rel_error_ff_20
print("\nTesting Cascade Networks:")
# a) 1 hidden layer with 20 neurons
model_cascade_20 = create_cascade_model([20])
rel_error_cascade_20, history_cascade_20 = train_and_evaluate(model_cascade_20, "Cascade (20 neurons)")
results["Cascade (20 neurons)"] = rel_error_cascade_20
model_cascade_10_10 = create_cascade_model([10, 10])
rel_error_cascade_10_10, history_cascade_10_10 = train_and_evaluate(model_cascade_10_10, "Cascade (10+10 neurons)")
results["Cascade (10+10 neurons)"] = rel_error_cascade_10_10
print("\nTesting Elman Networks:")
model_elman_15 = create_elman_model([15])
rel_error_elman_15, history_elman_15 = train_and_evaluate(model_elman_15, "Elman (15 neurons)")
results["Elman (15 neurons)"] = rel_error_elman_15
model_elman_5_5_5 = create_elman_model([5, 5, 5])
rel_error_elman_5_5_5, history_elman_5_5_5 = train_and_evaluate(model_elman_5_5_5, "Elman (5+5+5 neurons)")
results["Elman (5+5+5 neurons)"] = rel_error_elman_5_5_5
plt.figure(figsize=(10, 6))
plt.bar(results.keys(), results.values(), color='skyblue')
plt.xticks(rotation=45, ha='right')
plt.ylabel('Relative Error (%)')
plt.title('Comparison of Neural Network Architectures')
plt.tight_layout()
plt.savefig("relative errors.jpg", dpi = 200)
Z_grid = target_function(X_grid, Y_grid)
fig = plt.figure(figsize=(12, 5))
# 3D surface plot
ax1 = fig.add_subplot(121, projection='3d')
surf = ax1.plot_surface(X_grid, Y_grid, Z_grid, cmap='viridis', alpha=0.8)
ax1.set_xlabel('X')
ax1.set_ylabel('Y')
ax1.set_zlabel('f(X,Y)')
ax1.set_title('Target Function: f(x,y) = x² + y²')
# Contour plot
ax2 = fig.add_subplot(122)
contour = ax2.contourf(X_grid, Y_grid, Z_grid, cmap='viridis')
plt.colorbar(contour, ax=ax2)
ax2.set_xlabel('X')
ax2.set_ylabel('Y')
ax2.set_title('Contour Plot of Target Function')
plt.tight_layout()
plt.savefig("target function.jpg", dpi = 200)
plt.figure(figsize=(12, 6))
plt.plot(history_ff_10.history['val_loss'], label='Feed Forward (10)')
plt.plot(history_ff_20.history['val_loss'], label='Feed Forward (20)')
plt.plot(history_cascade_20.history['val_loss'], label='Cascade (20)')
plt.plot(history_cascade_10_10.history['val_loss'], label='Cascade (10+10)')
plt.plot(history_elman_15.history['val_loss'], label='Elman (15)')
plt.plot(history_elman_5_5_5.history['val_loss'], label='Elman (5+5+5)')
plt.xlabel('Epochs')
plt.ylabel('Validation Loss (MSE)')
plt.title('Validation Loss Comparison')
plt.legend()
plt.yscale('log')
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig("history of all models.jpg", dpi = 200)
best_model_name = min(results, key=results.get)
print(f"Best model: {best_model_name} with relative error: {results[best_model_name]:.2f}%")
print("\nSummary of Results:")
print("-" * 60)
print(f"{'Model Type':<25} {'Architecture':<20} {'Relative Error (%)':<20}")
print("-" * 60)
for model_name, error in results.items():
	model_type = model_name.split('(')[0].strip()
	architecture = '(' + model_name.split('(')[1]
	print(f"{model_type:<25} {architecture:<20} {error:<20.2f}")
print("-" * 60)
duration=datetime.now()-start
hours,minutes,seconds=ConvertTimeDelta(duration)
print("Time: ",hours,":",minutes,":",seconds)