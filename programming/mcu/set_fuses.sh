#!/bin/bash
echo "uncomment this file to use it. Currently disabled to save you from yourself."

# The curret standard, turns on the external clock 
#avrdude -c 2232HIO -p m328p -U lfuse:w:0xde:m -U hfuse:w:0xd9:m -U efuse:w:0xf7:m -F
