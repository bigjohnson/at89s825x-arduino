import serial
import time
from intelhex import IntelHex
from config import *

# Path to hex file
f = data_dumpFile
print('Reading file: ' + f)

# Serial port name
p = serialPort
print(p)

# Read hex file
print('Programmer port = ' + p)

# Read hex file
ih = IntelHex()
#ih.fromfile(f, format='hex')


with serial.Serial(p, 9600) as ser:
    time.sleep(2)
    print(ser.readline().decode('utf-8'))
    ser.write(b'\x60') # Enable programming
    print(ser.readline().decode('utf-8'))
#    ih.dump()
#    print('Programming...')
    # for i in range(0, len(ih.addresses())):
    #     addr = ih.addresses()[i]
    #     ser.write(b'\x51')
    #     ser.write(bytes([addr//256])) # high address byte
    #     ser.write(bytes([addr%256]))  # low address byte
    #     ser.write(bytes([ih[addr]]))  # data byte
    #     time.sleep(0.05)
    # ser.readline()

    #a = input('Programming done. Do you wish to verify? y/n: ')
    #if  a == 'Y' or a == 'y':
    print('Reading...')
    conta = 0
    #err = False
    for i in range(0x0, at89s8253_max_data, 32):
        #addr = ih.addresses()[i]
        #if (conta - 1) == 255:
        #    print(hex(i))            
        #if conta == 256:
        #    conta = 0
        #conta += 64
        print(hex(i) + " ", end = '')
        ser.write(b'\x73')
        ser.write(bytes([i//256])) # high address byte
        ser.write(bytes([i%256]))  # low address byte
        for o in range(0, 32):
            k = int(ser.readline().decode('utf-8'), 16)
            print('.', end = '')
            ih[i+o] = k
        print()
        #print(k);
        #     if k != ih[addr]:
        #         print('Error at address' + hex(addr))
        #         print('Got %d, was %d' % (k, ih[addr]))
        #         err = True
        # if not err:
        #     print('Verification complete.')
        #
    ser.write(b'\x40') # End programming
    print(ser.readline().decode('utf-8'))
    ih.dump()
    ih.write_hex_file(f)
    print('Done.')
