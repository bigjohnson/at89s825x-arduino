// AT89S8252 Programmer
// Author: mtirado

// Arduino Pin Connections

// RST:  pin 9
// MOSI: pin 11
// MISO: pin 12
// SCK:  pin 13




#include <SPI.h>

#define RSTPin 9
#define MOSIPin 11
#define MISOPin 12
#define SCKPin 13


unsigned char pgm_instruction = 0;
unsigned int pgm_address = 0;
unsigned char pgm_data = 0;

// Programming Enable Instruction
void progEnable2() {
  pinMode(RSTPin, OUTPUT);
  digitalWrite(RSTPin, HIGH);
  delay(50);
  SPI.transfer(0xac);
  SPI.transfer(0x53);
  SPI.transfer(0x00);
}

void progEnable3() {
  pinMode(RSTPin, OUTPUT);
  digitalWrite(RSTPin, HIGH);
  delay(50);
  SPI.transfer(0xac);
  SPI.transfer(0x53);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
}

// Write to code memory
void writeCode2(unsigned int addr, unsigned char data) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x02);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

void writeCode3(unsigned int addr, unsigned char data) {
  SPI.transfer(0x40);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Read from code memory
unsigned char readCode2(unsigned int addr) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x01);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Read from code memory
unsigned char readCode3(unsigned int addr) {
  SPI.transfer(0x20);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Write to data memory
void writeData2(unsigned int addr, unsigned char data) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x06);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Write to data memory
void writeData3(unsigned int addr, unsigned char data) {
  SPI.transfer(0xc0);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Read from data memory
unsigned char readData2(unsigned int addr) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x05);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Read from data memory
unsigned char readData3(unsigned int addr) {
  SPI.transfer(0xa0);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

void eraseChip2() {
  SPI.transfer(0xac);
  SPI.transfer(0x04);
  SPI.transfer(0x00);
  delay(5);
}

void eraseChip3() {
  SPI.transfer(0xac);
  SPI.transfer(0x80);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  delay(5);
}

void writeLock2(unsigned int lock) {
  SPI.transfer(0xac);
  if ( lock == 1 ) {
    SPI.transfer(103 & 0x00ff);
  } else if ( lock == 2 ) {
    SPI.transfer(27 & 0x00ff);
  } else {
    SPI.transfer(7 & 0x00ff);
  }
  SPI.transfer(0x00);
  delay(5);
}

// Read lock
unsigned char readLock3() {
  SPI.transfer(0x24);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  return SPI.transfer(0x00);
}

unsigned char readFuses3() {
  SPI.transfer(0x21);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  return SPI.transfer(0x00);
}

void setup() {
  Serial.begin(9600);
  SPI.setBitOrder (MSBFIRST);
  // According to the AT89S8252 datasheet, The maximum serial clock (SCK) frequency
  //should be less than 1/40 of the crystal frequency (of the chip to be programmed).
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  //SPI.begin();

  //pinMode(RSTPin, OUTPUT);

  pinMode(MOSIPin, INPUT);
  pinMode(MISOPin, INPUT);
  pinMode(SCKPin, INPUT);
  pinMode(RSTPin, INPUT);

  delay(500);
  Serial.println("Programmer ready.");
}

void loop() {
  if (Serial.available() > 0) {
    pgm_instruction = Serial.read();
    switch (pgm_instruction) {
      case 0x50: // Programming enable
        SPI.setDataMode(SPI_MODE0);
        SPI.begin();
        progEnable2();
        Serial.println("Programming mode enabled 89S8252.");
        break;

      case 0x60: // Programming enable
        SPI.setDataMode(SPI_MODE1);
        SPI.begin();
        progEnable3();
        Serial.println("Programming mode enabled 89S8253.");
        break;

      case 0x51: // Write to code memory
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeCode2(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x61: // Write to code memory
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeCode3(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x52: // Read from code memory
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readCode2(pgm_address), HEX);
        break;

      case 0x62: // Read from code memory
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readCode3(pgm_address), HEX);
        break;

      case 0x53: // Erase chip
        eraseChip2();
        Serial.println("Chip erased 89S8252.");
        break;

      case 0x63: // Erase chip
        eraseChip3();
        Serial.println("Chip erased 89S8253.");
        break;

      case 0x54: // Read from data memory
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readData2(pgm_address), HEX);
        break;

      case 0x64: // Read from data memory
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readData3(pgm_address), HEX);
        break;

      case 0x55: // Write to data memory
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeData2(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x65: // Write to data memory
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeData3(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x56: // Write lock
        pgm_address = Serial.read();
        writeLock2(pgm_address);
        Serial.println("Lock bits programmed 89S8252.");
        break;

      case 0x67: // Read lock
        Serial.print("0x");
        Serial.println(readLock3(), HEX);
        break;

      case 0x68: // Read fuses
        Serial.print("0x");
        Serial.println(readFuses3(), HEX);
        break;

      case 0x40: // End programming
        digitalWrite(RSTPin, LOW);
        Serial.println("Programming mode disabled.");
        // Set outputs to inputs (high impedance mode)
        SPI.end();
        digitalWrite(RSTPin, LOW);
        pinMode(MOSIPin, INPUT);
        pinMode(MISOPin, INPUT);
        pinMode(SCKPin, INPUT);
        pinMode(RSTPin, INPUT);
        break;
    }
  }
}
