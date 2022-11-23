// AT89S8252/3 Programmer
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
#define SCKPin 13 // If you can, remove the pin 13 connected led or led resistor,
                  // if you will connect a led on port 1.7 and don't remove the Arduinos's led,
                  // the AT89S805x connected led will be alwais on if the programmer is connected...

unsigned char pgm_instruction = 0;
unsigned int pgm_address = 0;
unsigned char pgm_data = 0;
unsigned char bytes[64];

// Programming Enable Instruction AT89S8252
void progEnable2() {
  pinMode(RSTPin, OUTPUT);
  digitalWrite(RSTPin, HIGH);
  delay(50);
  SPI.transfer(0xac);
  SPI.transfer(0x53);
  SPI.transfer(0x00);
}

// Programming Enable Instruction AT89S8253
void progEnable3() {
  pinMode(RSTPin, OUTPUT);
  digitalWrite(RSTPin, HIGH);
  delay(50);
  SPI.transfer(0xac);
  SPI.transfer(0x53);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
}

// Write to code memory byte AT89S8252
void writeCode2(unsigned int addr, unsigned char data) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x02);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Write to code memory byte AT89S8253
void writeCode3(unsigned int addr, unsigned char data) {
  SPI.transfer(0x40);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Read from code memory byte AT89S8252
unsigned char readCode2(unsigned int addr) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x01);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Read from code memory byte AT89S8253
unsigned char readCode3(unsigned int addr) {
  SPI.transfer(0x20);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Write to data memory byte AT89S8252
void writeData2(unsigned int addr, unsigned char data) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x06);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Write to data memory byte AT89S8253
void writeData3(unsigned int addr, unsigned char data) {
  SPI.transfer(0xc0);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Read from data memory byte AT89S8252
unsigned char readData2(unsigned int addr) {
  SPI.transfer(((addr & 0xff00) >> 5) + 0x05);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Read from data memory byte AT89S8253
unsigned char readData3(unsigned int addr) {
  SPI.transfer(0xa0);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Erase chip AT89S8252
void eraseChip2() {
  SPI.transfer(0xac);
  SPI.transfer(0x04);
  SPI.transfer(0x00);
  //delay(5);
}

// Erase chip AT89S8253
void eraseChip3() {
  SPI.transfer(0xac);
  SPI.transfer(0x80);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  //delay(5);
}

// Write lock AT89S8252
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

// Read lock AT89S8253
unsigned char readLock3() {
  SPI.transfer(0x24);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  return SPI.transfer(0x00);
}

// Read fuses AT89S8253
unsigned char readFuses3() {
  SPI.transfer(0x21);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  return SPI.transfer(0x00);
}

// Read from Atmel Sgn byte AT89S8253
unsigned char readAtmelSgn3(unsigned int addr) {
  SPI.transfer(0x28);
  SPI.transfer(0x00);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Read from user Sgn byte AT89S8253
unsigned char readUserSgn3(unsigned int addr) {
  SPI.transfer(0x22);
  SPI.transfer(0x00);
  SPI.transfer(addr & 0x00ff);
  return SPI.transfer(0x00);
}

// Write to user Sign byte AT89S8253
void writeUserSgn3(unsigned int addr, unsigned char data) {
  SPI.transfer(0x42);
  SPI.transfer(0x00);
  SPI.transfer(addr & 0x00ff);
  SPI.transfer(data);
  //delay(5);
}

// Read page from code memory byte AT89S8253
void readPageCode3(unsigned int addr) {
  SPI.transfer(0x30);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00C0);
  for (unsigned char i = 0; i <= 63; i++ ) {
    bytes[i] = SPI.transfer(0x00);
  }
  return;
}

// Read page from data memory byte AT89S8253
void readPageData3(unsigned int addr) {
  SPI.transfer(0xB0);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00E0);
  for (unsigned char i = 0; i <= 31; i++ ) {
    bytes[i] = SPI.transfer(0x00);
  }
  return;
}

void writePageCode3(unsigned int addr) {
  SPI.transfer(0x50);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00C0);
  for (unsigned char i = 0; i <= 63; i++ ) {
    SPI.transfer(bytes[i]);
  }
}

void writePageData3(unsigned int addr) {
  SPI.transfer(0xD0);
  SPI.transfer((addr & 0xff00) >> 8);
  SPI.transfer(addr & 0x00E0);
  for (unsigned char i = 0; i <= 31; i++ ) {
    SPI.transfer(bytes[i]);
  }
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
        Serial.println("Programming mode enabled AT89S8252.");
        break;

      case 0x60: // Programming enable
        SPI.setDataMode(SPI_MODE1);
        SPI.begin();
        progEnable3();
        Serial.println("Programming mode enabled AT89S8253.");
        break;

      case 0x51: // Write to code memory AT89S8252
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeCode2(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x61: // Write to code memory AT89S8253
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeCode3(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x52: // Read from code memory AT89S8252
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readCode2(pgm_address), HEX);
        break;

      case 0x62: // Read from code memory AT89S8253
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readCode3(pgm_address), HEX);
        break;

      case 0x53: // Erase chip AT89S8252
        eraseChip2();
        Serial.println("Chip erased AT89S8252.");
        break;

      case 0x63: // Erase chip AT89S8253
        eraseChip3();
        Serial.println("Chip erased AT89S8253.");
        break;

      case 0x54: // Read from data memory AT89S8252
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readData2(pgm_address), HEX);
        break;

      case 0x64: // Read from data memory AT89S8253
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        Serial.println(readData3(pgm_address), HEX);
        break;

      case 0x55: // Write to data memory AT89S8252
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeData2(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x65: // Write to data memory AT89S8253
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        pgm_data = Serial.read();
        writeData3(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x56: // Write lock AT89S8252
        pgm_address = Serial.read();
        writeLock2(pgm_address);
        Serial.println("Lock bits programmed AT89S8252.");
        break;

      case 0x67: // Read lock AT89S8253
        Serial.print("0x");
        Serial.println(readLock3(), HEX);
        break;

      case 0x68: // Read fuses AT89S8253
        Serial.print("0x");
        Serial.println(readFuses3(), HEX);
        break;

      case 0x69: // Read from ATMEL Sgn. Page AT89S8253
        while (Serial.available() < 1);
        //pgm_address = Serial.read() << 8;
        pgm_address = Serial.read();
        Serial.println(readAtmelSgn3(pgm_address), HEX);
        break;

      case 0x70: // Read from user Sgn. Page AT89S8253
        while (Serial.available() < 1);
        //pgm_address = Serial.read() << 8;
        pgm_address = Serial.read();
        Serial.println(readUserSgn3(pgm_address), HEX);
        break;

      case 0x71: // Write to user Sgn. Page AT89S8253
        while (Serial.available() < 2);
        pgm_address = Serial.read();
        pgm_data = Serial.read();
        writeUserSgn3(pgm_address, pgm_data);
        Serial.println('0');
        break;

      case 0x72: // Read page from code memory AT89S8253
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        readPageCode3(pgm_address);
        for (unsigned char i = 0; i <= 63; i++) {
          Serial.println(bytes[i], HEX);
        }
        break;

      case 0x73: // Read page from data memory AT89S8253
        while (Serial.available() < 2);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();
        readPageData3(pgm_address);
        for (unsigned char i = 0; i <= 31; i++) {
          Serial.println(bytes[i], HEX);
        }
        break;

      case 0x74: // Write page to code memory AT89S8253
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();

        for (unsigned char i = 0; i <= 63; i++) {
          while (Serial.available() == 0);
          bytes[i] = Serial.read();
        }
        writePageCode3(pgm_address);
        Serial.println('0');
        break;

      case 0x75: // Write page to data memory AT89S8253
        while (Serial.available() < 3);
        pgm_address = Serial.read() << 8;
        pgm_address |= Serial.read();

        for (unsigned char i = 0; i <= 31; i++) {
          while (Serial.available() == 0);
          bytes[i] = Serial.read();
        }
        writePageData3(pgm_address);
        Serial.println('0');
        break;

      case 0x40: // End programming
        digitalWrite(RSTPin, LOW);
        Serial.println("Programming mode disabled.");
        // Set outputs to inputs (high impedance mode)
        SPI.end();
        pinMode(MOSIPin, INPUT);
        pinMode(MISOPin, INPUT);
        pinMode(SCKPin, INPUT);
        pinMode(RSTPin, INPUT);
        break;
    }
  }
}
