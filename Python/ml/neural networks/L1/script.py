import numpy as np
import random
import numpy as np
from sklearn.neural_network import MLPClassifier
class MultiLayerPerceptron:
	def __init__(self, input_size, hidden_size, output_size, learning_rate=0.1):
		self.weights_input_hidden = np.random.uniform(-0.5, 0.5, (input_size, hidden_size))
		self.bias_hidden = np.random.uniform(-0.5, 0.5, (1, hidden_size))
		self.weights_hidden_output = np.random.uniform(-0.5, 0.5, (hidden_size, output_size))
		self.bias_output = np.random.uniform(-0.5, 0.5, (1, output_size))
		self.learning_rate = learning_rate		
	def sigmoid(self, x):
		return 1 / (1 + np.exp(-x))	
	def sigmoid_derivative(self, x):
		return x * (1 - x)
	def forward(self, x):
		self.hidden_input = np.dot(x, self.weights_input_hidden) + self.bias_hidden
		self.hidden_output = self.sigmoid(self.hidden_input)
		self.output_input = np.dot(self.hidden_output, self.weights_hidden_output) + self.bias_output
		self.output = self.sigmoid(self.output_input)
		return self.output	
	def predict(self, x):
		output = self.forward(x)
		return (output > 0.5).astype(int)	
	def backward(self, x, y, output):
		error = y - output
		delta_output = error * self.sigmoid_derivative(output)
		error_hidden = delta_output.dot(self.weights_hidden_output.T)
		delta_hidden = error_hidden * self.sigmoid_derivative(self.hidden_output)
		self.weights_hidden_output += self.hidden_output.T.dot(delta_output) * self.learning_rate
		self.bias_output += np.sum(delta_output, axis=0, keepdims=True) * self.learning_rate
		self.weights_input_hidden += x.T.dot(delta_hidden) * self.learning_rate
		self.bias_hidden += np.sum(delta_hidden, axis=0, keepdims=True) * self.learning_rate
		return np.mean(np.abs(error))	
	def train(self, x, y, epochs):
		errors = []
		for epoch in range(epochs):
			output = self.forward(x)
			error = self.backward(x, y, output)
			errors.append(error)
			if epoch % 2000 == 0:
				print("epoch ",epoch,"; error: ",f'{error:.5f}')
		return errors
def int_to_binary(n, bits=8):
	binary=[]
	while n>0:
		a=int(float(n%2))
		binary.insert(0,a)
		n=(n-a)/2
	return binary
def binary_to_int(binary_array):
    result = 0
    for bit in binary_array:
        result = (result << 1) | int(bit)
    return result
x = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([[0],[1],[1],[0]])
mlp = MultiLayerPerceptron(input_size=2, hidden_size=4, output_size=1, learning_rate=0.1)
sklearn_mlp = MLPClassifier(activation='logistic', max_iter=100, hidden_layer_sizes=(3,), alpha=0.001, solver='lbfgs')
sklearn_mlp.fit(x, np.array([0, 1, 1, 0]))
errors = mlp.train(x, y, epochs=20000)
print("| A | B |A XOR B|PROBABILITY|A XOR B (sklearn MLPClassifier)|")
print("|---|---|-------|-----------|-------------------------------|")
for i in range(len(x)):
	a, b = x[i]
	prediction = mlp.predict(x[i:i+1])[0][0]
	probability = mlp.forward(x[i:i+1])[0][0]
	sklearn_mlp_pred=sklearn_mlp.predict([x[i]])[0]
	print("| ",int(a)," | ",int(b)," |   ",prediction,"   |",f"{probability:.9f}|               ",sklearn_mlp_pred,"               |",sep='')
for i in range(90):
	print(end='-')
print()
sklearn_mlp.predict(np.array([0,1]).reshape(1,-1))
for i in range(10):
	n1=random.randint(0,1000)
	n2=random.randint(0,1000)
	n1_binary=int_to_binary(n1)
	n2_binary=int_to_binary(n2)
	n1_binary_length=len(n1_binary)
	n2_binary_length=len(n2_binary)
	if(n1_binary_length>n2_binary_length):
		difference=n1_binary_length-n2_binary_length
		xor_binary_pred=[mlp.predict([n1_binary[k],0])[0][0]for k in range(difference)]
		xor_binary_pred_sklearn=[sklearn_mlp.predict(np.array([n1_binary[k],0]).reshape(1,-1))[0]for k in range(difference)]
		j=0
		for k in range(difference,n1_binary_length):
			xor_binary_pred.append(mlp.predict([n1_binary[k],n2_binary[j]])[0][0])
			xor_binary_pred_sklearn.append(sklearn_mlp.predict(np.array([n1_binary[k],n2_binary[j]]).reshape(1,-1))[0])
			j+=1
	else:
		difference=n2_binary_length-n1_binary_length
		xor_binary_pred=[mlp.predict([n2_binary[k],0])[0][0]for k in range(difference)]
		xor_binary_pred_sklearn=[sklearn_mlp.predict(np.array([n2_binary[k],0]).reshape(1,-1))[0]for k in range(difference)]
		j=0
		for k in range(difference,n2_binary_length):
			xor_binary_pred.append(mlp.predict([n1_binary[j],n2_binary[k]])[0][0])
			xor_binary_pred_sklearn.append(sklearn_mlp.predict(np.array([n1_binary[j],n2_binary[k]]).reshape(1,-1))[0])
			j+=1
	xor_decimal_pred=binary_to_int(xor_binary_pred)
	xor_decimal_pred_sklearn=binary_to_int(xor_binary_pred_sklearn)
	xor_decimal_result=n1^n2
	print("number 1 decimal   : ",n1)
	print("number 2 decimal   : ",n2)
	print("decimal prediction : ",xor_decimal_pred)
	print("decimal sklearn MLP: ",xor_decimal_pred_sklearn)	
	print("xor decimal result : ",xor_decimal_result)
	print("number 1 binary    : ",n1_binary)
	print("number 2 binary    : ",n2_binary)
	print("binary prediction  : ",xor_binary_pred)
	print("binary sklearn MLP : ",xor_binary_pred_sklearn)
	if(xor_decimal_pred!=xor_decimal_result or xor_decimal_pred_sklearn!=xor_decimal_result):
		print("The result is INCORRECT. The program was terminated.")
		exit()
	else:
		print("The result is correct")		
	for i in range(90):
		print(end='-')
	print()