import pandas as pd
import numpy as np
import random as rnd
import pathlib
from sklearn.linear_model import LogisticRegression
from keras import Model, optimizers, regularizers
from keras.layers import Dense, Input, Dropout, BatchNormalization
from sklearn.metrics import confusion_matrix, precision_recall_curve, roc_curve, auc, log_loss
import matplotlib.pyplot as plt #побудова графіків
# завантаження даних
test_path = 'test.csv'
train_path = 'train.csv'
train_df = pd.read_csv(train_path)
test_df = pd.read_csv(test_path)
combine = [train_df, test_df]
pd.set_option('display.expand_frame_repr', False)
# видалення неважливих стовбців: Ticket та Cabin
train_df = train_df.drop(['Ticket', 'Cabin'], axis=1)
test_df = test_df.drop(['Ticket', 'Cabin'], axis=1)
combine = [train_df, test_df]
# скорочення поля Name (отримання лише заголовків)
for dataset in combine:
    dataset['Title'] = dataset.Name.str.extract('([A-Za-z]+)\.', expand=False)
# заміна заголовків більш загальними іменами
for dataset in combine:
    dataset['Title'] = dataset['Title'].replace(['Capt', 'Col','Major', 'Rev', 'Sir', 'Jonkheer','Ms','Mlle','Mme','Dona','Lady','Miss','Mr','Mrs'], 'Ordinary')
    dataset['Title'] = dataset['Title'].replace(['Don','Countess','Dr'], 'Nobel')
# перетворення назв категорій
train_df = pd.concat([train_df, pd.get_dummies(train_df['Title'], prefix='Title')],axis=1).drop(['Title'],axis=1)
test_df = pd.concat([test_df, pd.get_dummies(test_df['Title'], prefix='Title')],axis=1).drop(['Title'],axis=1)
combine =[train_df, test_df]
# видалення стовбців Name та PassengerId
train_df = train_df.drop(['Name', 'PassengerId'], axis=1)
test_df = test_df.drop(['Name'], axis=1)
combine = [train_df, test_df]
# перетворення назви статі на числове
for dataset in combine:
    dataset['Sex'] = dataset['Sex'].map( {'female': 0, 'male': 1} ).astype(int)
# доповнення стовбця Age
guess_ages = np.zeros((2,3))
for dataset in combine:
    for i in range(0, 2):
        for j in range(0, 3):
            guess_df = dataset[(dataset['Sex'] == i) & (dataset['Pclass'] == j + 1)]['Age'].dropna()
            # age_mean = guess_df.mean()
            # age_std = guess_df.std()
            # age_guess = rnd.uniform(age_mean - age_std, age_mean + age_std)
            age_guess = guess_df.median()
            # перетоврення віку на найближчий .5 вік
            guess_ages[i, j] = int(age_guess / 0.5 + 0.5) * 0.5
    for i in range(0, 2):
        for j in range(0, 3):
            dataset.loc[(dataset.Age.isnull()) & (dataset.Sex == i) & (dataset.Pclass == j + 1), 'Age'] = guess_ages[i, j]
    dataset['Age'] = dataset['Age'].astype(int)
# створення числових шифрів для різних вікових груп
for dataset in combine:
    dataset.loc[ dataset['Age'] <= 16, 'Age'] = 0
    dataset.loc[(dataset['Age'] > 16) & (dataset['Age'] <= 32), 'Age'] = 1
    dataset.loc[(dataset['Age'] > 32) & (dataset['Age'] <= 48), 'Age'] = 2
    dataset.loc[(dataset['Age'] > 48) & (dataset['Age'] <= 64), 'Age'] = 3
    dataset.loc[ dataset['Age'] > 64, 'Age'] =4
# перетворення числових шифрів
train_df = pd.concat([train_df, pd.get_dummies(train_df['Age'], prefix='AgeBand')],axis=1).drop(['Age'],axis=1)
test_df = pd.concat([test_df, pd.get_dummies(test_df['Age'], prefix='AgeBand')],axis=1).drop(['Age'],axis=1)
combine = [train_df, test_df]
# перетоврення Pclass
train_df = pd.concat([train_df, pd.get_dummies(train_df['Pclass'], prefix='Pclass')],axis=1).drop(['Pclass'],axis=1)
test_df = pd.concat([test_df, pd.get_dummies(test_df['Pclass'], prefix='Pclass')],axis=1).drop(['Pclass'],axis=1)
combine =[train_df, test_df]
# злиття стовбців SibSp та Parch в FamilySize
for dataset in combine:
    dataset['FamilySize'] = dataset['SibSp'] + dataset['Parch'] + 1
# створення стобця IsAlone, яке базується на FamilySize
for dataset in combine:
    dataset['IsAlone'] = 0
    dataset.loc[dataset['FamilySize'] == 1, 'IsAlone'] = 1
# збереження лише стовбця IsAlone
train_df = train_df.drop(['Parch', 'SibSp', 'FamilySize'], axis=1)
test_df = test_df.drop(['Parch', 'SibSp', 'FamilySize'], axis=1)
combine = [train_df, test_df]
# доповнення категоріального стовбця Embarked
freq_port = train_df.Embarked.dropna().mode()[0]
for dataset in combine:
    dataset['Embarked'] = dataset['Embarked'].fillna(freq_port)
# перетоврення його на числове значення values
train_df = pd.concat([train_df, pd.get_dummies(train_df['Embarked'], prefix='Embarked')],axis=1).drop(['Embarked'],axis=1)
test_df = pd.concat([test_df, pd.get_dummies(test_df['Embarked'], prefix='Embarked')],axis=1).drop(['Embarked'],axis=1)
combine = [train_df, test_df]
# доповнення стовбця Fare (вартість проїзду)
test_df['Fare'].fillna(test_df['Fare'].dropna().median(), inplace=True)
# створення тарифних зон
train_df['FareBand'] = pd.qcut(train_df['Fare'], 4)
# перетоврення їх на прості значення
for dataset in combine:
    dataset.loc[ dataset['Fare'] <= 7.91, 'Fare'] = 0
    dataset.loc[(dataset['Fare'] > 7.91) & (dataset['Fare'] <= 14.454), 'Fare'] = 1
    dataset.loc[(dataset['Fare'] > 14.454) & (dataset['Fare'] <= 31), 'Fare']   = 2
    dataset.loc[ dataset['Fare'] > 31, 'Fare'] = 3
    dataset['Fare'] = dataset['Fare'].astype(int)
# кодування значень
train_df = pd.concat([train_df, pd.get_dummies(train_df['Fare'], prefix='Fare')],axis=1).drop(['Fare'],axis=1)
test_df = pd.concat([test_df, pd.get_dummies(test_df['Fare'], prefix='Fare')],axis=1).drop(['Fare'],axis=1)
combine =[train_df, test_df]
train_df = train_df.drop(['FareBand'], axis=1)
combine = [train_df, test_df]
#####  моделювання та прогнозування ######
# підготовка даних
X_train = train_df.drop('Survived', axis=1)
Y_train = train_df['Survived']
X_test = test_df.drop('PassengerId', axis=1).copy()
# логістична регресія
logreg = LogisticRegression()
logreg.fit(X_train, Y_train)
Y_pred = logreg.predict(X_test)
acc_log = round(logreg.score(X_train, Y_train)*100, 2)
# багатошаровий персептрон
input = Input(shape=(20,))
x = Dense(256,activation='relu')(input)
x = Dropout(0.8)(x)
x = Dense(256, activation='relu')(x)
x = Dense(128, activation='relu')(x)
x = BatchNormalization()(x)
x = Dense(128, activation='relu')(x)
x = Dense(64, activation='relu')(x)
x = Dense(64, activation='relu')(x)
output = Dense(1, activation='sigmoid')(x)
MLP = Model(input, output)
sgd = optimizers.SGD(lr=0.01, decay=1e-6, momentum=0.6, nesterov=True)
adam = optimizers.Adam(lr=0.01, beta_1=0.9, beta_2=0.999, epsilon=None, decay=0.001, amsgrad=False)
MLP.compile(optimizer=adam, loss='binary_crossentropy', metrics=['binary_accuracy'])
split = int(X_train.shape[0]*0.9)
history = MLP.fit(X_train.values, Y_train.values, batch_size=64, epochs=250,validation_split=0.2, verbose=1)
predictions = MLP.predict(X_test.values,verbose=0)
# виведення підсумків про точність
plt.figure()
plt.plot(history.history['binary_accuracy'])
plt.plot(history.history['val_binary_accuracy'])
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
# прогнозування виживших
submission = pd.DataFrame()
submission['PassengerId'] = test_df['PassengerId'].copy()
submission['Survived'] = (predictions>=0.72).astype(int)
submission.to_csv('predictions.csv', index=False)
print("Done.")