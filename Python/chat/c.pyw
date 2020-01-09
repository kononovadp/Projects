# -*- coding: cp1251 -*-
from Tkinter import *
import socket
def printer(event):	
	sock = socket.socket()
	sock.connect(('localhost', 9090))
	data=ent.get()
	sock.send(data)
	ent.delete(0,END)
	rdata = sock.recv(1024)
	tex.insert(END,rdata+'\n\\')
	sock.close()
root = Tk()
root.title(u'PythonChat v.1.0')
ent = Entry(root,width=100,bd=2)
tex = Text(root,width=75,font="Verdana 12",wrap=WORD)
but = Button(root)
but["text"] = "Отправить сообщение"
but.bind("<Button-1>",printer)
tex.pack()
ent.pack(side=LEFT)
but.pack(side=RIGHT)
root.mainloop()