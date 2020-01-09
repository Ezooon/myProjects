from tkinter import *
import getpass
from random import randint


import xmlrpc.client

#Creates server window instance


user = getpass.getuser() + str(randint(0, 200))
def disableEntry(event):
	chatLog.config(state=DISABLED)

def pressAction(event):
	clickAction()

def clickAction():
	message = inputText.get("0.0",END)
	#Write message to chat window
	server.sendMessage(user +": "+ message)

	#Scroll to the bottom of chat windows
	chatLog.yview(END)

	#Erace previous message in Entry Box
	inputText.delete("0.0",END)


	
m = Tk()
m.geometry("500x500")

server = xmlrpc.client.ServerProxy("http://localhost:8000")


inputText= Text(m, bd=0, bg="white",width="29", height="5", font="Arial")
inputText.bind("<Return>", disableEntry)
inputText.bind("<KeyRelease-Return>", pressAction)
inputText.config(highlightbackground='blue')


send = Button(m, text='Send', command='show')
send.config(command=clickAction)
send.place(x=6, y=401, height=90)


#Create a Chat window
chatLog = Text(m, bd=0, bg="white", height="8", width="50", font="Arial",)
chatLog.config(state=DISABLED)
chatLog.place(x=6,y=6, height=386, width=370)

#Bind a scrollbar to the Chat window
scrollbar = Scrollbar(m, command=chatLog.yview, cursor="heart")
chatLog['yscrollcommand'] = scrollbar.set
scrollbar.place(x=376,y=6, height=386)
inputText.place(x=128, y=401, height=90, width=265)



curmessage = server.numOfMessages()
server.sendMessage(user  + " has joined the chat!\n")
def update():	
	global curmessage
	if (server.numOfMessages() == curmessage):
		pass
	else:
		message = server.getMessage(curmessage)
		curmessage = (curmessage + 1) % 10
		chatLog.config(state=NORMAL)
		chatLog.insert(END, message)
		chatLog.yview(END)
		chatLog.config(state=DISABLED)
	m.after(500, update)

m.after(50, update)
m.mainloop()
