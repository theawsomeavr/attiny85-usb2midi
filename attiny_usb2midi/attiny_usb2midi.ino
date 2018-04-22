//////////////////////////////////////////////////////////////
// sounder (For ATtiny45/85/44/84)
//////////////////////////////////////////////////////////////
// Features:
// CC:1 = Distotion Mode
// CC:2 = Portamento Time
// CC:3 = Sustain Time
// CC:4 = LFO Time
//////////////////////////////////////////////////////////////
/*
# mi:muz:prot#1
#                        +------+
#           RESET A0 PB5 |1    8| VCC
#                 A3 PB3 |2    7| PB2 A1 INT0    (USB D-)
# (Audio)    OC1B A2 PB4 |3    6| PB1 OC0B/OC1A  (USB D+)
#                    GND |4    5| PB0 OC0A       (LED)
#                        +------+
#
# mi:muz:prot#2
#                     +-------+
#                  VCC|1    14|GND
#                XTAL1|2    13|PA0/D0/A0 (USB D-)
#                XTAL2|3    12|PA1/D1/A1 (USB D+) 
#                RESET|4    11|PA2/D2/A2
#        (LED)  D8/PB2|5    10|PA3/D3/A3
#            A7/D7/PA7|6     9|PA4/D4/A4/SCL/SCK
#   MOSI/SDA/A6/D6/PA6|7     8|PA5/D5/A5/MISO (Audio)
#                     +-------+
#
# mi:muz:prot#3
#                        +------+
#           RESET A0 PB5 |1    8| VCC
# (USB D-)        A3 PB3 |2    7| PB2 A1 INT0    
# (Audio/LED)OC1B A2 PB4 |3    6| PB1 OC0B/OC1A  (USB D+)
#                    GND |4    5| PB0 OC0A
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




