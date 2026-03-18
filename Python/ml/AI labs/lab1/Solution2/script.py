import numpy as np
import pandas as pd
import warnings
import matplotlib.pyplot as plt
warnings.filterwarnings("ignore")
# нейронна мережа багатошаровий персептрон
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Dropout
from keras.utils import np_utils
from sklearn.preprocessing import LabelEncoder
from sklearn.impute import SimpleImputer 
# завантаження даних
traindata = pd.read_csv('train.csv')
testdata = pd.read_csv('test.csv')
# кодування стовбців даних
le = LabelEncoder()
traindata['Sex'] = le.fit_transform(traindata['Sex'])
testdata['Sex'] = le.fit_transform(testdata['Sex'])
traindata['Embarked'] = le.fit_transform(traindata['Embarked'].astype(str))
testdata['Embarked'] = le.fit_transform(testdata['Embarked'].astype(str))
# відбір властивостей для тренування
X = traindata[['Pclass','Sex','Age','Fare','Parch','SibSp','Embarked']].values
y = traindata.iloc[:,1].values
X_real_test = testdata[['Pclass','Sex','Age','Fare','Parch','SibSp','Embarked']].values
# обробка пустих значень
imputer = SimpleImputer()
X_transformed = imputer.fit_transform(X)
X_real_test = imputer.fit_transform(X_real_test)
# виправлення випадкових джерел для відтворюваності
seed = 7
np.random.seed(seed)
labels = np_utils.to_categorical(y)
def BuildModel():	
	model = Sequential()
	model.add(Dense(7, input_dim=7, activation='relu'))
	model.add(Dense(2, activation='softmax'))
	model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
	return model
model = BuildModel()
# підгонка моделі
history = model.fit(X_transformed, labels, epochs=250, validation_split=0.2, batch_size=6, verbose=1)
# виведення підсумків про точність
plt.figure()
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(['train', 'validation'], loc='upper left')
plt.savefig("accuracy")
# виведення підсумків про функцію втрат
plt.figure()
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('model loss')
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['train', 'validation'], loc='upper left')
plt.savefig("loss")
pred = model.predict(X_real_test)
y_pred_test = pred.argmax(1)
pid = testdata[['PassengerId']].values
res = np.expand_dims(y_pred_test,axis=1)
f = np.hstack((pid,res))
df = pd.DataFrame(f, columns = ['PassengerId', 'Survived']) 
df.to_csv('predictions.csv', index=False)