/*
  Usb Parallel Marker Versie
  Copyright Leiden University SOLO - Evert 2018~2023

  HW1 - There are 3 version for HW1, Initial version without leds, test version with high leds, and version with leds
  HW2 - Version with leds, there are 2 versions, test version with high leds, and version with smd flat leds
  HW3 - Added LedCC wire to make it possible to enable/disable all the leds

  20180110  1.0 Initial release
  20220214  1.1 Added command mode to make it possible for reading serial number, from this version also SOLO qr sticker needs to be applied
  20220518  1.2 Added hardware version to VERSION for upcoming futures
  20220531  1.3 Added L and O to enable and disable all the leds
  20220620  1.4 MyInfo String was not a valid Json String, moved HW version to eeprom.
  20220711  1.5 To Make the UsbParmarker compatibel with the BrainBox Trigger box for Tobii Pro Lab, added 9600 baud for data mode
  20221123  1.6 Added F command to test leds and attached hardware
  20230309  1.7 Added TXLED0 empty check (JdH)

*/

/* IMPORTANT NOTE
  TXLED must be disabled to prevent Interference with PORTD, done with #UNDEF
*/

#undef TX_RX_LED_INIT  //DDRD |= (1<<5), DDRB |= (1<<0)
//#undef TXLED0    //  PORTD |= (1<<5)
#undef TXLED1    //  PORTD &= ~(1<<5)
#undef RXLED0    //  PORTB |= (1<<0)
#undef RXLED1    //  PORTB &= ~(1<<0)

#define LEDCC  7 //PE6 Led CommonCathode pin
#include <EEPROM.h>

//Globals
const String SwVer = "SW1.7";
const String Version;
const String Serialno;
const String HwVer;

void setup() {
 //writeStringToEEPROM(10, "S01020");    //Use ones to program te serial number in the eeprom of the device
 //writeStringToEEPROM(20, "HW2");    //Use ones to program the hardware version in the eeprom of the device

  DDRD = 0xFF; //PortD all pins output
  PORTD = 0x00;
  //PORTD = 0xFF; //Inverted output
  pinMode(LEDCC, OUTPUT);
  digitalWrite(LEDCC, LOW);
  Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
  Serialno = readStringFromEEPROM(10);
  HwVer = readStringFromEEPROM(20);
  Version = String(HwVer + ":" + SwVer);   // Set HW version always

  // #################################### Keep the code lines below in the same order ################################################
  TXLED0
  // The macro TXLED0 above is intentionally there to make compilation crash if it is defined as "PORTD |= (1<<5)".
  // TXLED0 should be defined empty, or it will cause DATA3 (and LED3 if enabled) to turn on when sending serial data (an answer)
  // like "Pong,UsbParMarker" after receiving the "P" command for example.
  // Using "#undef TXLED0" does not work (any longer) as apparently the TXLED0 macro is preprocessed before this ino file.
  // To prevent this problem (and this error); change "#define TXLED0			PORTD |= (1<<5)" to "#define TXLED0" on line 95 in:
  // C:\Users\<USER>\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\variants\leonardo\pins_arduino.h

} // Compilation error on this line? Read comments above!
// #################################### Keep the code lines above in the same order ################################################


void loop() {
  if (Serial.baud() == 115200 || Serial.baud() == 9600 ) {    //data mode
    if (Serial.available() > 0) {
      PORTD = Serial.read();       //send marker to output port
      //PORTD = 255- Serial.read();       //send marker to output port Inverted Output
    }
  }
  else if (Serial.baud() == 4800) { //command mode

    if (Serial.available() > 0) {
      handlecommands();
    }
  }
}






