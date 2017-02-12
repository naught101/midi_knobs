/*
   simple MIDI knob controller.
   
   based on http://www.arduino.cc/en/Tutorial/MidiDevice
*/

#include "MIDIUSB.h"

const int pot1pin = 0;  //A0 input

// TODO: array of pots
uint8_t potValue1;
uint8_t pot1CC = 0x0A;
uint8_t previousValue1 = 0x00;

void setup() {
}

void loop() {
  readPots();
  sendMIDI();
  MidiUSB.flush();
}

void readPots() {
  int val = analogRead(pot1pin);
  potValue1 = (uint8_t) (map(val, 0, 1023, 0, 127));
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void sendMIDI()
{
  if (previousValue1 != potValue1)
  {
    previousValue1 = potValue1;
    controlChange(0, pot1CC, potValue1);
  }
}

