// Set Teensy to USB MIDI mode and include files from:
// https://github.com/2kohm/Teensy-USB-MIDI-CLOCK

#include <MIDI.h>

int relayPin = 0;

void setup() { 
  Serial.begin(31250); 

  pinMode(relayPin, OUTPUT);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);              
 
  pinMode(relayPin, OUTPUT);     
  digitalWrite(relayPin, HIGH); // HIGH == off in my relay setup
}

#define DIVISOR 48

// MIDI clock bytes
#define CLOCK 248
#define START 250
#define CONTINUE 251
#define STOP 252

void loop() {
  usbMIDI.read();
}

void RealTimeSystem(byte realtimebyte) {
  static int i = 0;
  static int count = -1;
  if(realtimebyte == START || realtimebyte == STOP) { 
    i = 0;
    count = -1;
  }
  if(realtimebyte == CLOCK) { 
        i++;
        count--;
        if(count < 0 && ((i % DIVISOR) == 0)) {
          digitalWrite(relayPin, LOW);
          count = DIVISOR;
          i = 0;
        }
        if(count == 0) {
          digitalWrite(relayPin, HIGH);
        }
  }
}

