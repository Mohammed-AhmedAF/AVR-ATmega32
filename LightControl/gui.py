#!/usr/bin/env python3

from tkinter import *
from functools import partial
import serial

try:
    ser = serial.Serial('/dev/ttyUSB0',9600)
except:
    print("Error in establishing connection")

def driveLED(ledNumber):
    try:
        ser.write(str.encode(ledNumber))
    except:
        print("Error in sending byte")

def driveLEDAgain():
    try:
        ser.write(str.encode(clicked.get()))
    except:
        print("Error in sending byte")

root = Tk()

#window title
root.title("LED control")

photo = PhotoImage(file="diode.png")
root.iconphoto(False,photo)

root.geometry("580x100")
#Fixed window size
root.resizable(width=False,height=False)

button0 = Button(root,text="LED 1",command=partial(driveLED,'a'))
button1 = Button(root,text="LED 2",command=partial(driveLED,'b'))
button2 = Button(root,text="LED 3",command=partial(driveLED,'c'))
button3 = Button(root,text="LED 4",command=partial(driveLED,'d'))
button4 = Button(root,text="LED 5",command=partial(driveLED,'e'))
button5 = Button(root,text="LED 6",command=partial(driveLED,'f'))
button6 = Button(root,text="LED 7",command=partial(driveLED,'g'))
button7 = Button(root,text="LED 8",command=partial(driveLED,'h'))
buttonA = Button(root,text="Send!",command=driveLEDAgain)
labelOfTimer = Label(root,text="Timer: ",border=12)
clicked = StringVar()


option = OptionMenu(root,clicked,"a","b","c","d","e","f","g","h")
clicked.set("a")


#Placing widgets
button0.grid(row=0,column=0,sticky=W,padx=2)
button1.grid(row=0,column=1,sticky=W)
button2.grid(row=0,column=2,sticky=W)
button3.grid(row=0,column=3,sticky=W)
button4.grid(row=0,column=4,sticky=W)
button5.grid(row=0,column=5,sticky=W)
button6.grid(row=0,column=6,sticky=W)
button7.grid(row=0,column=7,sticky=W,padx=2)
buttonA.grid(row=1,column=2,sticky=W)

labelOfTimer.grid(row=1,column=0,sticky=W)
option.grid(row=1,column=1,sticky=W,padx=2)

root.mainloop()
