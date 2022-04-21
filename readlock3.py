import serial
import time
from intelhex import IntelHex
from config import *

# Path to hex file
f = code_dumpFile
print(f)

# Serial port name
p = serialPort
print(p)

with serial.Serial(p, 9600) as ser:
    time.sleep(2)
    print(ser.readline().decode('utf-8'))
    ser.write(b'\x60') # Enable programming
    print(ser.readline().decode('utf-8'))
    print('Reading lock bits')
    ser.write(b'\x67')
    fuses=ser.readline().decode('utf-8')
    fuses=int(fuses, 0)
    print(fuses)
    if not fuses & 1:
        print("LB1 lock enabled: MOVC instructions executed from external program memory are disabled from fetching code bytes from internal memory. EA is sampled and latched on reset and further programming of the Flash memory (parallel or serial mode) is disabled.")
    else:
        print("LB1 lock disabled.")
    if not fuses & 2:
        print("Same as Mode LB1, but parallel or serial verify are also disabled.")
    else:
        print("LB2 lock disabled.")
    if not fuses & 4:
        print("Same as LB2, but external execution is also disabled.")
    else:
        print("LB3 lock disabled.")
    ser.write(b'\x40') # End programming
    print(ser.readline().decode('utf-8'))
    print('Done.')
