import serial
import time
from intelhex import IntelHex
from config import *

# Path to hex file
f = data_targetFile
print('Reading file: ' + f)

# Serial port name
p = serialPort
print('Programmer port = ' + p)

# Read hex file
ih = IntelHex()

ih.fromfile(f, format='hex')

if ih.addresses()[len(ih.addresses()) - 1]  >= at89s8252_max_data:
    print('The file is too large ' + hex(ih.addresses()[len(ih.addresses()) - 1]) + '!')
    print('Max space is ' + hex(at89s8252_max_data) + ' bytes, extra data will be ignored!')
    a = input( 'Continue? y/n: ')
    if  a != 'Y' and a != 'y':
        quit()

with serial.Serial(p, 9600) as ser:
    time.sleep(2)
    print(ser.readline().decode('utf-8'))
    ser.write(b'\x50') # Enable programming
    ih.dump()

    print(ser.readline().decode('utf-8'))
    conta = 0
    print('Verifying...')
    err = False
    for i in range(0, len(ih.addresses())):
        addr = ih.addresses()[i]
        if addr < at89s8252_max_data:
            if conta == 0:
                print()
                print(hex(i) + ' ', end='')
            if conta == 31:
                conta = -1
            conta += 1
            ser.write(b'\x54')
            ser.write(bytes([addr//256])) # high address byte
            ser.write(bytes([addr%256]))  # low address byte
            k = int(ser.readline().decode('utf-8'), 16)
            if k != ih[addr]:
                #print('Error at address' + hex(addr))
                #print('Got %d, was %d' % (k, ih[addr]))
                err = True
                print('E', end = '')
            else:
                print('.', end = '')
    print()
    if not err:
        print('Data verification complete.')
    else:
        print('Data verification issue.')
    ser.write(b'\x40') # End programming
    print(ser.readline().decode('utf-8'))
    print('Done.')
