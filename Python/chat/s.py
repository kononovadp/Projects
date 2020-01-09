# -*- coding: cp1251 -*-
print 'server'
import socket
working = True
while working:
	sock = socket.socket()
	sock.bind(('', 9090))
	sock.listen(10)
	conn, addr = sock.accept()
	print 'message from: ', addr
	data = conn.recv(1024)
	conn.send(data)
	print data
	conn.close()