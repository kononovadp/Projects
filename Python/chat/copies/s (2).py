# -*- coding: cp1251 -*-
print 'server'
import socket
working = True
while working:
	sock = socket.socket()
	sock.bind(('', 9090))
	sock.listen(1)
	conn, addr = sock.accept()
	p=socket.gethostbyname(socket.gethostname())
	data = conn.recv(1024)
	addr=addr+data
	print 'connected:', data,p
	conn.close()