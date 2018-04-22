// attiny85 should be running at 16mhz
/*
# mi:muz:prot#1
#                        +------+
#           RESET A0 PB5 |1    8| VCC
#                 A3 PB3 |2    7| PB2 A1 INT0    (USB D-)
#            OC1B A2 PB4 |3    6| PB1 OC0B/OC1A  (USB D+)
#                    GND |4    5| PB0 OC0A       (tx)
#                        +------+
*/
//////////////////////////////////////////////////////////////

#include "VUSBMidiATtiny.h"
#include <SendOnlySoftwareSerial.h>

SendOnlySoftwareSerial mySerial (0); 

void onNoteOn(byte ch, byte note, byte vel){
  digitalWrite(4,1);
  mySerial.write (0x90 | ch); 
  mySerial.write (note); 
   mySerial.write (vel);
}

void onNoteOff(byte ch, byte note, byte vel){
    digitalWrite(4,0);
  mySerial.write (0x80 | ch); 
  mySerial.write (note); 
   mySerial.write (vel);
}

void onCtlChange(byte ch, byte num, byte value){
    mySerial.write (0xB0 | ch); 
  mySerial.write (num); 
   mySerial.write (value);
}

void setup() {
  pinMode(3,INPUT_PULLUP);
  pinMode(4,1);
  wdt_enable(WDTO_2S);
    mySerial.begin(31250);
  if(digitalRead(3)==0){
      mySerial.begin(57600);
  }

  UsbMidi.init();
  UsbMidi.setHdlNoteOff(onNoteOff);
  UsbMidi.setHdlNoteOn(onNoteOn);
  UsbMidi.setHdlCtlChange(onCtlChange);

}

void loop() {
 
  wdt_reset();
  UsbMidi.update();
}




