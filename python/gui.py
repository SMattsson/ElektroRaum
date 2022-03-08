import tkinter as tk
import serial
import time

string = "enum class Parameter"
indexCounter = 0
startCount = -2
paramList = {}

with open("src/cfg/inc/soundEngineDefs.h") as file:
    dataFile = file.readlines()
    for line in dataFile:
        line = line.strip()
        line = line.replace(',', '')
        if string in line:
            startCount += 1
        elif startCount == -1:
            startCount += 1
        elif startCount >= 0 and line != "NUMBER_OF_PARAMETERS":
            paramList[line] = startCount
            print(line + " " + str(startCount))
            startCount += 1
        if line == "NUMBER_OF_PARAMETERS":
            break


osc_map = [12.00, 9.00, 10.00, 8.0, 0.0]

window = tk.Tk()
window.title('ElektroRaum')
window.geometry('1920x1080')

elektro_raum = serial.Serial(port='/dev/ttyACM0', baudrate=115200, timeout=.1)

def pad_with_leading_zeros(str):
    number_of_zeroes = 4 - len(str)
    tmp = str
    str = ""
    for x in range(number_of_zeroes):
        str += "0"
    str += tmp
    return str
        
def print_selection(v):
    v = "{:.10f}".format(osc_map[int(v)])
    data = str(v)[0:8]
    param = str(pad_with_leading_zeros(str(paramList["OSCILLATOR_0_WAVEFORM"]))).encode('ascii')
    elektro_raum.write('_'.encode('ascii'))
    elektro_raum.write(param)
    elektro_raum.write(data.encode('ascii'))

osc_slider = tk.Scale(window, label='Osc Waveform', from_=0, to=4, orient=tk.HORIZONTAL, length=200, showvalue=0, tickinterval=1, resolution=1, command=print_selection)
osc_slider.pack()

window.mainloop()