Arduino MIDI controller
=======================

A basic Arduino-based MIDI controller that uses pots and buttons to send MIDI.
Works with any Atmega32u4-based Arduino (Leonardo, Micro, Pro Micro, Lilypad USB), and uses the USB port connect to the computer, using the [MIDIUSB library](https://www.arduino.cc/en/Reference/MIDIUSB).


## Requirements

- Atmega32u4-based Arduino (Leonardo, Micro, Pro Micro, Lilypad USB)
- Potentiometers (~10k, but anything between 5k and 50k should work)
- Some filter capacitors (~1µf give or take an order of magnitude) if your pots are noisy.
- Buttons (momentary switches)
- A case, if you want
- some way of getting a USB connection from your computer to the Arduino.


## Build

- Hook the pots up (1: ground, 2 (wiper): analogue pin, 3: +5V)
- Add a filter cap from ground to wiper for each potentiometer (pin 1 to 2), if you're getting noise on the pots.
- Adjust the pin values as appropriate in the code and upload the sketch, and you should be good to go.
