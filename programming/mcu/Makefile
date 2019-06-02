all :
	avr-gcc -Wall -g -Os -mmcu=atmega328p -o build/tester_avr.bin src/tester_avr.c
	avr-objcopy -j .text -j .data -O ihex build/tester_avr.bin build/tester_avr.hex
	#avr-objdump -d -s -m avr5 build/tester_avr.bin

test :
	gcc src/tester.c -o build/tester.exe
	chmod +x build/tester.exe
	./tester.exe

debug:
	gcc -g src/tester.c -o build/debug.exe
	gdb build/debug.exe

leaks:
	gcc src/tester.c -o build/tester.exe
	chmod +x build/tester.exe
	valgrind --leak-check=full -v build/tester.exe

clean:
	trash "build/*"



