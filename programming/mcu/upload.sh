#!/bin/bash

# Port number input, connecting to a FT2232H based generic programmer,
# programming an atmega328p[b] device.
# Need to add in -F as I can't figure out how to get it to do b.
avrdude -c 2232HIO -p m328p -U build/tester_avr.hex -F

