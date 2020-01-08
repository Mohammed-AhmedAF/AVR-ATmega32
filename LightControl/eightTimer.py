from tkinter import *
from tkinter import ttk
from functools import partial
import serial

ser = serial.Serial('/dev/ttyUSB0',9600)

def driveLED(ledNumber):
   ser.write(str.encode(ledNumber))

root = Tk()

#window title
root.title("LED control")

photo = PhotoImage(file="diode.png")
root.iconphoto(False,photo)

root.geometry("560x100")
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

timer = ttk.Combobox(root,values=["1 min", "5 min", "10 min"])


button0.grid(row=0,column=0,sticky=W,padx=2)
button1.grid(row=0,column=1,sticky=W)
button2.grid(row=0,column=2,sticky=W)
button3.grid(row=0,column=3,sticky=W)
button4.grid(row=0,column=4,sticky=W)
button5.grid(row=0,column=5,sticky=W)
button6.grid(row=0,column=6,sticky=W)
button7.grid(row=0,column=7,sticky=W,padx=2)

timer.grid(row=1,column=0,sticky=W)

root.mainloop()
