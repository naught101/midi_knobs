/*
   simple MIDI knob controller.

   based on http://www.arduino.cc/en/Tutorial/MidiDevice
*/

#include "MIDIUSB.h"

#define N_POTS 5


const uint8_t MIDICC = 0x0B;

const int potPin[] = {0, 1, 2, 3, 4};  // Pot pins
const uint8_t potCN[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E};  // MIDI control values

uint8_t potValues[N_POTS];  // Initial values
uint8_t potValuePrev[] = {0, 0, 0, 0, 0}; // previous values for comparison


void setup() {
}

void loop() {
  readPots();
  sendMIDI();
  MidiUSB.flush();
}

void readPots() {
  for (int i=0; i < N_POTS; i++) {
    int val = analogRead(potPin[i]);
    potValues[i] = (uint8_t) (map(val, 0, 1023, 0, 127));
  }
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
  for (int i=0; i < N_POTS; i++) {
    // Pots seem noisy .. this isn't an optimal solution though...
    if (abs(potValuePrev[i] - potValues[i]) > 1)
    // if (potValuePrev[i] != potValues[i])
    {
      potValuePrev[i] = potValues[i];
      controlChange(0, potCN[i], potValues[i]);
    }
  }
}

