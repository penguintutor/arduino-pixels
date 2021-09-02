# arduino-pixels
Wireless control of PixelStrips or NeoPixels using a web graphical interface running on an Arduino.

Designed for the Arduino Nano RP2040 connect.
Needs an Arduino that supports WiFiNINA. 

For more details see <http://www.penguintutor.com/projects/arduino-rp2040-pixelstrip> 

## Colors

The color of the pixels depends upon your actual strip. In the default code then grey is set to a very low value to show a noticeable difference on my pixel strip. This may appear to be near to black on the screen, but shows fairly bright on the strip. The same problem occurs with lighter colors such as light green which may appear almost white on the pixel strip.

## Sequences

The sequences are defined in sequences.h and sequences.ino. You can add your own for any additional sequences you would like.

It's also possible to create other sequences using the built-in sequences with specific color sequences. In particular you can add black for any pixels that you would like tried turned off.

For example try a chaser with:
Black; Black; White; White
Grey; White; White; White; Grey; Black