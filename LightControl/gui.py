#!/usr/bin/env python3

from tkinter import *
from functools import partial
import serial


def driveLED(ledNumber):
    try:
        ser.write(str.encode(ledNumber))
    except:
        labelStatus['text'] = "Error sending"

def driveLEDAgain():
    try:
        ser.write(str.encode(clicked.get()))
    except:
        print("Error in sending byte")

root = Tk()

buttonsFrame = Frame(root)

#window title
root.title("LED control")

photo = PhotoImage(file="diode.png")
root.iconphoto(False,photo)

root.geometry("580x100")
#Fixed window size
root.resizable(width=False,height=False)

button0 = Button(buttonsFrame,text="LED 1",command=partial(driveLED,'a'))
button1 = Button(buttonsFrame,text="LED 2",command=partial(driveLED,'b'))
button2 = Button(buttonsFrame,text="LED 3",command=partial(driveLED,'c'))
button3 = Button(buttonsFrame,text="LED 4",command=partial(driveLED,'d'))
button4 = Button(buttonsFrame,text="LED 5",command=partial(driveLED,'e'))
button5 = Button(buttonsFrame,text="LED 6",command=partial(driveLED,'f'))
button6 = Button(buttonsFrame,text="LED 7",command=partial(driveLED,'g'))
button7 = Button(buttonsFrame,text="LED 8",command=partial(driveLED,'h'))
buttonSend = Button(buttonsFrame,text="Send!",command=driveLEDAgain)
labelOfTimer = Label(buttonsFrame,text="Timer: ",border=12)
labelStatus = Label(buttonsFrame,text="Hello",bd=1,anchor=W,relief=SUNKEN)
clicked = StringVar()


option = OptionMenu(buttonsFrame,clicked,"a","b","c","d","e","f","g","h")
clicked.set("a")

#Establishing serial connection
try:
    ser = serial.Serial('/dev/ttyUSB0',9600)
except:
    labelStatus['text'] = "Error establishing connection"

#Placing widgets
buttonsFrame.grid(row=0,column=0,sticky=N)
button0.grid(row=0,column=0,sticky=W,padx=2)
button1.grid(row=0,column=1,sticky=W)
button2.grid(row=0,column=2,sticky=W)
button3.grid(row=0,column=3,sticky=W)
button4.grid(row=0,column=4,sticky=W)
button5.grid(row=0,column=5,sticky=W)
button6.grid(row=0,column=6,sticky=W)
button7.grid(row=0,column=7,sticky=W,padx=2)
buttonSend.grid(row=1,column=2,sticky=W,columnspan=3)

labelOfTimer.grid(row=1,column=0,columnspan=1,sticky=W)
option.grid(row=1,column=1,sticky=W,padx=2)
labelStatus.grid(row=2,column=0,columnspan=8,sticky=W+E,padx=3)

root.mainloop()
