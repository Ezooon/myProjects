from tkinter import *
from midiutil import MIDIFile
from threading import Thread, Semaphore
from sys import stdout
from random import sample
from time import sleep

master = Tk()
canvas = Canvas(master, width=600, height=300, bg='white')
canvas.pack(padx=20, pady=20)
notes=[]

def get_pixels_of(canvas):
    width = int(canvas["width"])
    height = int(canvas["height"])
    colors = []
    newYmax = 100
    newYmin = 60
    newXmax = 60
    newXmin = 0

    #iterate through all pixels, getting coordinates of black ones only
    for x in range(width):
        column = []
        for y in range(height):
            if (get_pixel_color(canvas, x, y) == "BLACK"):
                newYValue = (((y) * (newYmax-newYmin)) / 300) + newYmin
                newXValue = (((x) * (newXmax-newXmin)) / 600) + newXmin
                notes.append([newXValue,96-(round(newYValue)-76)])
        colors.append(column)
    return colors

def get_pixel_color(canvas, x, y):
    ids = canvas.find_overlapping(x, y, x, y)
    if len(ids) > 0:
        index = ids[-1]
        color = canvas.itemcget(index, "fill")
        color = color.upper()
        if color != '':
            return color.upper()
    return "WHITE"

#function used for drawing when mouse is clicked
def click(click_event):
    global prev
    prev = click_event

#function used for drawing when mouse is clicked and dragged
def move(move_event):
    global prev
    global notes
    canvas.create_line(prev.x, prev.y, move_event.x, move_event.y, width=2)
    prev = move_event 

#function is called when user hits enter
def generateNotes(event=None):
    global notes
    global canvas
    print("CREATING MIDI")
    get_pixels_of(canvas) #get all pixels and stores in notes list
    track    = 0
    channel  = 0
    time     = 0    # In beats
    duration = 1/10    # In beats
    tempo    = 10   # In BPM
    volume   = 100  # 0-127, as per the MIDI stand1
    MyMIDI = MIDIFile(1)  # One track
    MyMIDI.addTempo(track, time, tempo)

    #populate midi
    for note in notes:
        MyMIDI.addNote(track, channel, note[1], note[0], duration, volume)
    with open("generator.mid", "wb") as output_file:
        MyMIDI.writeFile(output_file)
    print("DONE CREATING MIDI")

canvas.bind('<Button-1>', click)
canvas.bind('<B1-Motion>', move)
master.bind('<Return>', generateNotes)

mainloop()
