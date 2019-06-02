EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:custom_objects_radio_v1
LIBS:radio_v1-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328PB-AU U6
U 1 1 5C51C14D
P 4250 4000
F 0 "U6" H 3850 5475 50  0000 R BNN
F 1 "ATMEGA328PB-AU" H 3850 5400 50  0000 R BNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 4200 2600 50  0001 L CIN
F 3 "" H 3950 4050 50  0001 C CNN
	1    4250 4000
	1    0    0    -1  
$EndComp
Text GLabel 5550 3200 2    60   Input ~ 0
MCU_MISO
Text GLabel 5550 3100 2    60   Input ~ 0
MCU_MOSI
$Comp
L R R15
U 1 1 5C51C156
P 7200 4050
F 0 "R15" V 7280 4050 50  0000 C CNN
F 1 "10K" V 7200 4050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7130 4050 50  0001 C CNN
F 3 "" H 7200 4050 50  0001 C CNN
	1    7200 4050
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR054
U 1 1 5C51C15D
P 4100 5500
F 0 "#PWR054" H 4100 5250 50  0001 C CNN
F 1 "GNDD" H 4100 5375 50  0000 C CNN
F 2 "" H 4100 5500 50  0001 C CNN
F 3 "" H 4100 5500 50  0001 C CNN
	1    4100 5500
	1    0    0    -1  
$EndComp
Text GLabel 5550 3300 2    60   Input ~ 0
MCU_CLK
Text GLabel 5550 4600 2    60   Input ~ 0
UART_TX
Text GLabel 5550 4500 2    60   Input ~ 0
UART_RX
Text GLabel 7300 2900 2    60   Input ~ 0
SPI_select_transceiver
$Comp
L Crystal Y2
U 1 1 5C51C167
P 6400 3450
F 0 "Y2" H 6400 3600 50  0000 C CNN
F 1 "12MHz" H 6400 3300 50  0000 C CNN
F 2 "radio_v1:ECS-120-20-46X" H 6400 3450 50  0001 C CNN
F 3 "" H 6400 3450 50  0001 C CNN
	1    6400 3450
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR055
U 1 1 5C51C16E
P 4050 2500
F 0 "#PWR055" H 4050 2350 50  0001 C CNN
F 1 "+3.3V" H 4050 2640 50  0000 C CNN
F 2 "" H 4050 2500 50  0001 C CNN
F 3 "" H 4050 2500 50  0001 C CNN
	1    4050 2500
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR056
U 1 1 5C51C174
P 2850 3000
F 0 "#PWR056" H 2850 2850 50  0001 C CNN
F 1 "+3.3V" H 2850 3140 50  0000 C CNN
F 2 "" H 2850 3000 50  0001 C CNN
F 3 "" H 2850 3000 50  0001 C CNN
	1    2850 3000
	1    0    0    -1  
$EndComp
$Comp
L C C39
U 1 1 5C51C17A
P 6550 3800
F 0 "C39" H 6575 3900 50  0000 L CNN
F 1 "35pF" H 6575 3700 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6588 3650 50  0001 C CNN
F 3 "" H 6550 3800 50  0001 C CNN
	1    6550 3800
	0    1    1    0   
$EndComp
$Comp
L C C38
U 1 1 5C51C181
P 6550 3100
F 0 "C38" H 6575 3200 50  0000 L CNN
F 1 "35pF" H 6575 3000 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6588 2950 50  0001 C CNN
F 3 "" H 6550 3100 50  0001 C CNN
	1    6550 3100
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR057
U 1 1 5C51C18E
P 7200 3900
F 0 "#PWR057" H 7200 3750 50  0001 C CNN
F 1 "+3.3V" H 7200 4040 50  0000 C CNN
F 2 "" H 7200 3900 50  0001 C CNN
F 3 "" H 7200 3900 50  0001 C CNN
	1    7200 3900
	1    0    0    -1  
$EndComp
Text GLabel 5550 2800 2    60   Input ~ 0
PB0_breakout
Text GLabel 5550 3000 2    60   Input ~ 0
PB2_breakout
Text GLabel 5550 3700 2    60   Input ~ 0
PC0_breakout
Text GLabel 5550 3800 2    60   Input ~ 0
PC1_breakout
Text GLabel 5550 3900 2    60   Input ~ 0
PC2_breakout
Text GLabel 5550 4000 2    60   Input ~ 0
PC3_breakout
Text GLabel 5550 4100 2    60   Input ~ 0
PC4_breakout
Text GLabel 5550 4200 2    60   Input ~ 0
PC5_breakout
Text GLabel 5550 4700 2    60   Input ~ 0
PD2_breakout
Text GLabel 5550 4800 2    60   Input ~ 0
PD3_breakout
Text GLabel 5550 4900 2    60   Input ~ 0
PD4_breakout
Text GLabel 5550 5000 2    60   Input ~ 0
PD5_breakout
Text GLabel 5550 5100 2    60   Input ~ 0
PD6_breakout
Text GLabel 5550 5200 2    60   Input ~ 0
PD7_breakout
Text GLabel 2950 4900 0    60   Input ~ 0
PE3_breakout
Text GLabel 2950 4800 0    60   Input ~ 0
PE2_breakout
Text GLabel 2950 4700 0    60   Input ~ 0
PE1_breakout
Text GLabel 2950 4600 0    60   Input ~ 0
PE0_breakout
$Comp
L GNDD #PWR058
U 1 1 5C5807F9
P 6850 3600
F 0 "#PWR058" H 6850 3350 50  0001 C CNN
F 1 "GNDD" H 6850 3475 50  0000 C CNN
F 2 "" H 6850 3600 50  0001 C CNN
F 3 "" H 6850 3600 50  0001 C CNN
	1    6850 3600
	1    0    0    -1  
$EndComp
$Comp
L R R18
U 1 1 5C67420B
P 9200 4650
F 0 "R18" V 9280 4650 50  0000 C CNN
F 1 "330" V 9200 4650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9130 4650 50  0001 C CNN
F 3 "" H 9200 4650 50  0001 C CNN
	1    9200 4650
	0    -1   -1   0   
$EndComp
$Comp
L C C44
U 1 1 5C674258
P 9450 4900
F 0 "C44" H 9475 5000 50  0000 L CNN
F 1 "47pF" H 9475 4800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9488 4750 50  0001 C CNN
F 3 "" H 9450 4900 50  0001 C CNN
	1    9450 4900
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR059
U 1 1 5C6742DD
P 9450 5050
F 0 "#PWR059" H 9450 4800 50  0001 C CNN
F 1 "GNDD" H 9450 4925 50  0000 C CNN
F 2 "" H 9450 5050 50  0001 C CNN
F 3 "" H 9450 5050 50  0001 C CNN
	1    9450 5050
	1    0    0    -1  
$EndComp
Text GLabel 9050 4650 0    60   Input ~ 0
MCU_MOSI
Text GLabel 9050 4000 0    60   Input ~ 0
MCU_CLK
$Comp
L R R17
U 1 1 5C6745EB
P 9200 4000
F 0 "R17" V 9280 4000 50  0000 C CNN
F 1 "330" V 9200 4000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9130 4000 50  0001 C CNN
F 3 "" H 9200 4000 50  0001 C CNN
	1    9200 4000
	0    -1   -1   0   
$EndComp
$Comp
L C C43
U 1 1 5C6745F1
P 9450 4250
F 0 "C43" H 9475 4350 50  0000 L CNN
F 1 "47pF" H 9475 4150 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9488 4100 50  0001 C CNN
F 3 "" H 9450 4250 50  0001 C CNN
	1    9450 4250
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR060
U 1 1 5C6745F9
P 9450 4400
F 0 "#PWR060" H 9450 4150 50  0001 C CNN
F 1 "GNDD" H 9450 4275 50  0000 C CNN
F 2 "" H 9450 4400 50  0001 C CNN
F 3 "" H 9450 4400 50  0001 C CNN
	1    9450 4400
	1    0    0    -1  
$EndComp
Text GLabel 9050 3250 0    60   Input ~ 0
MCU_MISO
$Comp
L C C42
U 1 1 5C674859
P 9150 3500
F 0 "C42" H 9175 3600 50  0000 L CNN
F 1 "47pF" H 9175 3400 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 9188 3350 50  0001 C CNN
F 3 "" H 9150 3500 50  0001 C CNN
	1    9150 3500
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR061
U 1 1 5C6748A5
P 9150 3650
F 0 "#PWR061" H 9150 3400 50  0001 C CNN
F 1 "GNDD" H 9150 3525 50  0000 C CNN
F 2 "" H 9150 3650 50  0001 C CNN
F 3 "" H 9150 3650 50  0001 C CNN
	1    9150 3650
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 5C6748E2
P 9400 3250
F 0 "R16" V 9480 3250 50  0000 C CNN
F 1 "330" V 9400 3250 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 9330 3250 50  0001 C CNN
F 3 "" H 9400 3250 50  0001 C CNN
	1    9400 3250
	0    -1   -1   0   
$EndComp
Text GLabel 9550 3250 2    60   Input ~ 0
transceiver_MISO
Text GLabel 9550 4000 2    60   Input ~ 0
transceiver_CLK
Text GLabel 9550 4650 2    60   Input ~ 0
transceiver_MOSI
Text GLabel 7300 4300 2    60   Input ~ 0
MCU_reset
$Comp
L R R20
U 1 1 5C6FB376
P 7200 2650
F 0 "R20" V 7280 2650 50  0000 C CNN
F 1 "10K" V 7200 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 7130 2650 50  0001 C CNN
F 3 "" H 7200 2650 50  0001 C CNN
	1    7200 2650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR062
U 1 1 5C6FB6AF
P 7200 2500
F 0 "#PWR062" H 7200 2350 50  0001 C CNN
F 1 "+3.3V" H 7200 2640 50  0000 C CNN
F 2 "" H 7200 2500 50  0001 C CNN
F 3 "" H 7200 2500 50  0001 C CNN
	1    7200 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2900 7300 2900
Connection ~ 7200 2900
Connection ~ 7200 4300
Wire Wire Line
	7200 4300 7200 4200
Wire Wire Line
	7200 2900 7200 2800
Connection ~ 9450 4650
Connection ~ 9450 4000
Connection ~ 9150 3250
Wire Wire Line
	9050 3250 9250 3250
Wire Wire Line
	9150 3350 9150 3250
Wire Wire Line
	9450 4000 9450 4100
Wire Wire Line
	9350 4000 9550 4000
Wire Wire Line
	9450 4650 9450 4750
Wire Wire Line
	9350 4650 9550 4650
Wire Wire Line
	5550 4300 7300 4300
Wire Wire Line
	6850 3450 6850 3600
Connection ~ 6700 3450
Wire Wire Line
	6700 3450 6850 3450
Wire Wire Line
	6700 3100 6700 3800
Wire Wire Line
	6400 3300 6400 3100
Wire Wire Line
	6400 3600 6400 3800
Wire Wire Line
	6400 3600 6100 3600
Wire Wire Line
	6100 3300 6400 3300
Wire Wire Line
	2850 3100 2950 3100
Wire Wire Line
	2850 3000 2850 3100
Connection ~ 4050 2500
Wire Wire Line
	3950 2500 4150 2500
Wire Wire Line
	6100 3500 5550 3500
Wire Wire Line
	6100 3600 6100 3500
Wire Wire Line
	6100 3400 6100 3300
Wire Wire Line
	5550 3400 6100 3400
Connection ~ 4100 5500
Wire Wire Line
	4050 5500 4150 5500
Text Notes 7350 7500 0    60   ~ 0
RadIO V1
Text Notes 8150 7650 0    60   Italic 0
Febuary 24th 2019
$EndSCHEMATC
