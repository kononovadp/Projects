# -*- coding: cp1251 -*-
from Tkinter import *
def printer(event):
	data=ent.get()
	tex.insert(END,data+'\n\\')
	ent.delete(0,END)
root = Tk()
root.title(u'PythonChat v.1.0')
but = Button(root)
but["text"] = "Отправить сообщение"
but.bind("<Button-1>",printer)
ent = Entry(root,width=100,bd=2) 
tex = Text(root,width=75,font="Verdana 12",wrap=WORD)
tex.pack()
ent.pack(side=LEFT)
but.pack(side=RIGHT)
root.mainloop()