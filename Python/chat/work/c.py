# -*- coding: cp1251 -*-
print 'client'
import socket
working = True
while working:
	sock = socket.socket()
	sock.connect(('localhost', 9090))
	data=raw_input()
	sock.send(data)
	rdata = sock.recv(1024)
	print 'message from server: '+rdata
	sock.close()