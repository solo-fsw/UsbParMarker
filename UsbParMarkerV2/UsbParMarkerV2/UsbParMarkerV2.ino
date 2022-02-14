/*
  Usb Parallel Marker Versie 1 Build 1 10-1-2018
  Copyright Leiden University - SOLO
*/

/* IMPORTANT NOTE
  TXLED must be disabled to prevent Interference with PORTD, done with #UNDEF
*/

#undef TX_RX_LED_INIT  //DDRD |= (1<<5), DDRB |= (1<<0)
#undef TXLED0    //  PORTD |= (1<<5)
#undef TXLED1    //  PORTD &= ~(1<<5)
#undef RXLED0    //  PORTB |= (1<<0)
#undef RXLED1    //  PORTB &= ~(1<<0)

#include <EEPROM.h>

//Globals
const String Version = "1.0";
const String Serialno;

void setup() {
  DDRD = 0xFF; //PortD all pins output
  PORTD = 0x00;
  Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
 // writeStringToEEPROM(10, "S12345");
  Serialno = readStringFromEEPROM(10);
}

void loop() {
  if (Serial.baud() == 115200) {    //data mode
    if (Serial.available() > 0) {
      PORTD = Serial.read();       //send marker to output port
    }
  }
  else if (Serial.baud() == 4800) { //command mode

    if (Serial.available() > 0) {
      handlecommands();
    }
  }
}






