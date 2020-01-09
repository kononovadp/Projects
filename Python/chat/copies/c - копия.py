# -*- coding: cp1251 -*-
print 'client'
import socket
sock = socket.socket()
sock.connect(('localhost', 9090))
data=raw_input()
sock.send(data)
sock.close()
raw_input('')