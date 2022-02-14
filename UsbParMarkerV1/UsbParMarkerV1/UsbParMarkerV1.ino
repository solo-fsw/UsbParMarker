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



byte incomingByte = 0;   // for incoming serial data

void setup() {
        DDRD = 0xFF; //PortD all pins output
        PORTD =0x00;
        Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
}

void loop() {
       
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                PORTD = incomingByte;
         }
}

