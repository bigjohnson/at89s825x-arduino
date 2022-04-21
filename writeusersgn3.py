import serial
import time
from intelhex import IntelHex
from config import *

# Path to hex file
f = user_sgn_File
print(f)

# Serial port name
p = serialPort
print(p)

# Read hex file
ih = IntelHex()

ih.fromfile(f, format='hex')

if ih.addresses()[len(ih.addresses()) - 1]  >= at89s8253_max_user_sgn:
    a = input('The data is too large, max data is ' + str(at89s8253_max_user_sgn) + ' bytes, continue? y/n: ')
    if  a != 'Y' and a != 'y':
        quit()

with serial.Serial(p, 9600) as ser:
    time.sleep(2)
    print(ser.readline().decode('utf-8'))
    ser.write(b'\x60') # Enable programming
    ih.dump()
    print('Programming...')
    print(ser.readline().decode('utf-8'))
    conta = 0
    for i in range(0, len(ih.addresses())):
        addr = ih.addresses()[i]
        if addr < at89s8253_max_user_sgn:
            if conta == 255:
                print(hex(addr))
            if conta == 256:
                conta = 0
            conta += 1
            ser.write(b'\x71')
            #ser.write(bytes([addr//256])) # high address byte
            ser.write(bytes([addr%256]))  # low address byte
            ser.write(bytes([ih[addr]]))  # data byte
            #time.sleep(0.05)
            ser.readline()

    a = input('Programming done. Do you wish to verify? y/n: ')
    conta = 0
    if  a == 'Y' or a == 'y':
        print('Verifying...')
        err = False
        for i in range(0, len(ih.addresses())):
            addr = ih.addresses()[i]
            if addr < at89s8253_max_user_sgn:
                if conta == 255:
                    print(hex(addr))
                if conta == 256:
                    conta = 0
                conta += 1
                ser.write(b'\x70')
                #ser.write(bytes([addr//256])) # high address byte
                ser.write(bytes([addr%256]))  # low address byte
                k = int(ser.readline().decode('utf-8'), 16)
                if k != ih[addr]:
                    print('Error at address' + hex(addr))
                    print('Got %d, was %d' % (k, ih[addr]))
                    err = True

        if not err:
            print('Verification complete.')

    ser.write(b'\x40') # End programming
    print(ser.readline().decode('utf-8'))
    print('Done.')
