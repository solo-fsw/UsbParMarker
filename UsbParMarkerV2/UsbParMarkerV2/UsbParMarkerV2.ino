/*
  Usb Parallel Marker Versie 
  Copyright Leiden University SOLO - Evert 2018~2022

HW1 - There are 3 version for HW1, Initial version without leds, test version with high leds, and version with leds 
HW2 - Version with leds, there are 2 versions, test version with high leds, and version with leds 
HW3 - Added LedCC wire to make it possible to switch the leds ON/OFF 

20180110  1.0 Initial release
20220214  1.1 Added command mode to make it possible for reading serial number, from this version also SOLO qr sticker needs to be applied
20220518  1.2 Added hardware version to VERSION for upcoming futures
20220531  1.3 Added L and O to switch On or Off the leds

*/

/* IMPORTANT NOTE
  TXLED must be disabled to prevent Interference with PORTD, done with #UNDEF
*/

#undef TX_RX_LED_INIT  //DDRD |= (1<<5), DDRB |= (1<<0)
#undef TXLED0    //  PORTD |= (1<<5)
#undef TXLED1    //  PORTD &= ~(1<<5)
#undef RXLED0    //  PORTB |= (1<<0)
#undef RXLED1    //  PORTB &= ~(1<<0)

#define LEDCC  7 //PE6 Led CommonCathode pin
#include <EEPROM.h>

//Globals
const String Version = "HW3:SW1.3";
const String Serialno;

void setup() {
  DDRD = 0xFF; //PortD all pins output
  PORTD = 0x00;
  pinMode(LEDCC, OUTPUT);
  digitalWrite(LEDCC, LOW);
  Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
  writeStringToEEPROM(10, "Sxxxxx");    //Use ones to program te serial number in the device
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






