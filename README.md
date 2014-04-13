Arduino I2C Demo
================

Simple demonstration of I2C communication in Arduino.
Hook up two arduinos, one as master, one as slave, using I2C. Master will send three requests to slave to compute x+5 and slave returns the computed answer. Master verifies these answers are correct and outputs status to serial.

An arduino is designated as master by pulling pin 7 high, and slave by pulling pin 7 low.

### How to Build

I'm using [ino](http://inotool.org) to build the arduino code.

To use ino, navigate to the arduino directory and run `ino build` then `ino upload`.
