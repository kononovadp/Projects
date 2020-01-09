#11. Є матриця чисел типу double. Знайти кількість її рядків 
#та стовпців, всі елементи яких різні.
#from __future__ import print_function
import random
import time
kolonki=200
stroki=200
print('Array with ',stroki, ' lines and ',kolonki, ' columns is processing...')
def arraycreation():
	global a
	#a=[[0,1,2,3, 4,5,6,7, 8,9,10,11]]
	a = [[0] * kolonki * stroki]
	for i in range(kolonki * stroki):
		a[0][i]=random.uniform(0,9)
def arrayshow():
	i=0
	for p in range(stroki):
		for e in range(kolonki):
			print(a[0][i],end='  ')
			i+=1
		print()
def lines():
	n=0
	re=0
	global diflines
	diflines=0
	j=0
	t=0
	k=0
	for s in range(stroki):
		k=t
		for l in range(kolonki):
			j=t
			for i in range(kolonki):
				if a[0][j]==a[0][k]:
					n+=1
				j+=1
			k+=1
			if n==1:
				re+=1
			n=0
		t+=kolonki
		if re==kolonki:
			diflines+=1
		re=0
def columns():
	n=0
	re=0
	global difcolumns
	difcolumns=0
	j=0
	t=0
	k=0
	for s in range(kolonki):
		k=t
		for l in range(stroki):
			j=t
			for i in range(stroki):
				if a[0][j]==a[0][k]:
					n+=1
				j+=kolonki
			k+=kolonki
			if n==1:
				re+=1
			n=0
		t+=1
		if re==stroki:
			difcolumns+=1
		re=0
import threading
tbac=time.time()
arraycreation()
taac=time.time()
act_without_threads=taac-tbac
tbac=time.time()
thread1 = threading.Thread(target=arraycreation, args=())
thread1.start()
thread1.join()
taac=time.time()
act_with_threads=taac-tbac
tbts=time.time()
lines()
columns()
tats=time.time()
tst_without_threads=tats-tbts
tbts=time.time()
thread1 = threading.Thread(target=lines, args=())
thread2 = threading.Thread(target=columns, args=())
thread1.start()
thread2.start()
thread1.join()
thread2.join()
tats=time.time()
tst_with_threads=tats-tbts
from multiprocessing import Process,freeze_support
tbac=time.time()
if __name__ == '__main__':
	freeze_support()
	p = Process(target=arraycreation, args=())
	p.start()
	p.join()
taac=time.time()
act_multiproc=taac-tbac
tbac=time.time()
if __name__ == '__main__':
	freeze_support()
	p1 = Process(target=lines, args=())
	p2 = Process(target=columns, args=())
	p1.start()
	p2.start()
	p1.join()
	p2.join()
taac=time.time()
tst_multiproc=taac-tbac
print('Array creation WITHOUT modul threading: ',act_without_threads,'s')
print('Array creation USING the modul threading: ',act_with_threads,'s')
print('Task solution WITHOUT modul threading: ',tst_without_threads, 's')
print('Task solution USING the modul threading: ',tst_with_threads,'s')
print('Array creation USING the modul multiprocessing: ',act_multiproc,'s')
print('Task solution USING the modul multiprocessing: ',tst_multiproc,'s')
#Проверка правильности подсчета количества строк и столбцов, 
#все элементы которых разные на примере небольшого массива.
kolonki=5
stroki=5
print()
print('Algorithm test (array ',stroki,' / ',kolonki,')')
a = [[0] * kolonki * stroki]
for i in range(kolonki * stroki):
	a[0][i]=random.randint(0,9)
arrayshow()
lines()
columns()
print('lines with different elements: ',diflines)
print('columns with different elements: ',difcolumns)
input('press enter')