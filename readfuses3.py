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

    print('Reading fuses bits')
    ser.write(b'\x68')
    fuses=ser.readline().decode('utf-8')
    fuses=int(fuses, 0)
    print(fuses)
    if not fuses & 1:
        print("Fuse 1: enabled, serial programming.")
    else:
        print("Not Fuse 1: not enabled, serial programming.")
    if not fuses & 2:
        print("Fuse 2: enabled, doubled serial clock.")
    else:
        print("Not Fuse 2: not enabled, doubled serial clock.")
    if not fuses & 4:
        print("Fuse 3: enabled, user row wrinting enabled.")
    else:
        print("Not Fuse 3: not enabled, user row wrinting not enabled.")
    if not fuses & 8:
        print("Fuse 4: enabled, clock osclillator selected")
    else:
        print("Not Fuse 4: disabled, clock quartz selected" )
    ser.write(b'\x40') # End programming
    print(ser.readline().decode('utf-8'))
    print('Done.')
