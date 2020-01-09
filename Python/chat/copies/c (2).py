# -*- coding: cp1251 -*-
print 'client'
import socket
from Tkinter import *

working = True
while working:
	def printer(event):
		sock = socket.socket()
		data=ent.get()
		sock.connect(('localhost', 9090))
		sock.send(data)
#		sock.close()	
#		tex.insert(END,data+'\n\\')
#		ent.delete(0,END)
	root = Tk()
	root.title(u'Client')
	ent = Entry(root,width=150,bd=2)
	
	tex = Text(root,width=100,font="Verdana 12",wrap=WORD)
	but = Button(root)
	but["text"] = "Отправить сообщение"
	but.bind("<Button-1>",printer)
	tex.pack()
	ent.pack(side=LEFT)
	but.pack(side=RIGHT)
	root.mainloop()