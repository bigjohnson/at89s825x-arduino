# at89s825x-arduino

This is a programmer for the Atmel AT89S8252 and AT89S8253 microcontroller through Arduino's SPI port from an intel hex file.

# Installation

## Hardware

Upload `progammer.ino` to your Arduino board.

Connect the target microcontroller to VCC and GND, and add a crystal between XTAL1 and XTAL2. Make the following connections between the Arduino and the AT89S8252/AT89S8253.


| AT89S8252     | Arduino |
|---------------|---------|
| RESET (Pin 9) | Pin 9   |
| MOSI  (Pin 6) | Pin 11  |
| MISO  (Pin 7) | Pin 12  |
| SCK (Pin 8)   | Pin 13  |
| GND (Pin 20)  | Pin GND |

## Software

Install PySerial and IntelHex modules for Python.

```
python3 -m pip install pyserial intelhex
```

# Usage

Edit `config.py` to change the serial port and target/dump hex files.

In the blink directory there is `blinky.hex` that can be used as a sample program.

The program and data file names are in config.py

### AT89S8252

Program the microcontroller by running the script `writeprogram.py`, before programming you need erase the micro with `eraser.py`.

* If you want erase the chip run `eraser.py` it erase both program and data space.
* If you want dump the program from chip to file run `readprogram.py`
* If you want check the chip program from a file run `verifyprogram.py`
* If you want check if the chip program is empty run `verifyemptyprogram.py`
* If you want write data to chip run `writedata.py`.
* If you want dump the data from chip to file run `readdata.py`
* If you want check the chip data from a file run `verifydata.py`
* If you want check if the chip data is empty run `verifyemptydata.py`
* If you want program lock bits on chip `writelock.py`

### AT89S8253

Program the microcontroller by running the script `writeprogram3.py`, before programming you need erase the micro with `eraser3.py`.

* If you want program the microcontroller fast use `writeprogramfast3.py`
* If you want erase the chip run `eraser3.py` it erase both program and data space.
* If you want dump the program from chip to file run `readprogram3.py`
* If you want dump the program fast from chip to file run `readprogramfast3.py`
* If you want check the chip program from a file run `verifyprogram3.py`
* If you want check the chip program fast from a file run `verifyprogramfast3.py`
* If you want check if the chip program is empty run `verifyemptyprogram3.py`
* If you want check fast if the chip program is empty run `verifyemptyprogramfast3.py`
* If you want write data to chip run `writedata3.py`.
* If you want write data fast to chip run `writedatafast3.py`.
* If you want dump the data from chip to file run `readdata3.py`
* If you want dump the data fast from chip to file run `readdatafast3.py`
* If you want check the chip data from a file run `verifydata3.py`
* If you want check the chip data fast from a file run `verifydatafast3.py`
* If you want check if the chip data is empty run `verifyemptydata3.py`
* If you want check fast if the chip data is empty run `verifyemptydata3.py`
* If you want program lock bits on chip `writelock3.py` (actually unimplemented)
* If you want program fuses bits on chip `writefuses3.py` (actually unimplemented)
* If you want read lock bits on chip `readlock3.py`
* If you want read fuses bits on chip `readfuses3.py`
* If you want read Atmel signature from chip `readatmelsgn3.py`
* If you want write user signature from chip `writeusersgn3.py`
* If you want read user signature from chip `readusersgn3.py`

![8052Explorer](https://raw.githubusercontent.com/bigjohnson/bigjohnson.github.io/master/8052Explorer/8052Explorer.jpg)

the fast version of the programs use the new page mode of the AT89S8253


