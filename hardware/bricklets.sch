EESchema Schematic File Version 2
LIBS:tinkerforge
LIBS:power
LIBS:device
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
LIBS:servo-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
Title ""
Date "9 jun 2013"
Rev "1.0"
Comp "Tinkerforge GmbH"
Comment1 "Licensed under CERN OHL v.1.1"
Comment2 "Copyright (©) 2013, B.Nordmeyer <bastian@tinkerforge.com>"
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 3150 2750
Wire Wire Line
	3150 2850 3150 2750
Wire Wire Line
	3350 2850 3350 2750
Wire Wire Line
	7800 4300 7550 4300
Wire Wire Line
	7550 4300 7550 4400
Wire Wire Line
	7800 4200 7800 4100
Wire Wire Line
	7650 2350 7650 2650
Wire Wire Line
	7650 2650 7800 2650
Wire Wire Line
	7550 4750 7550 4700
Wire Wire Line
	7550 4700 7800 4700
Connection ~ 5000 3600
Wire Wire Line
	5000 2750 5000 4500
Connection ~ 4900 3700
Wire Wire Line
	4900 4600 4900 2850
Wire Wire Line
	6550 3350 7800 3350
Wire Wire Line
	6550 3150 7800 3150
Wire Wire Line
	7800 5100 6550 5100
Wire Wire Line
	7800 4900 6550 4900
Connection ~ 3350 3700
Wire Wire Line
	3350 3250 3350 3700
Connection ~ 3200 2750
Wire Wire Line
	3200 2650 3200 2750
Wire Wire Line
	5000 3600 2450 3600
Wire Wire Line
	4900 4600 7800 4600
Wire Wire Line
	4900 2850 7800 2850
Wire Wire Line
	8250 5300 8250 5250
Wire Wire Line
	8250 3550 8250 3500
Wire Wire Line
	5000 2750 7800 2750
Wire Wire Line
	5000 4500 7800 4500
Wire Wire Line
	4900 3700 2450 3700
Wire Wire Line
	3350 2750 3050 2750
Wire Wire Line
	3050 3250 3050 3600
Connection ~ 3050 3600
Wire Wire Line
	7800 4800 6550 4800
Wire Wire Line
	7800 5000 6550 5000
Wire Wire Line
	6550 3050 7800 3050
Wire Wire Line
	6550 3250 7800 3250
Wire Wire Line
	7800 2950 7350 2950
Wire Wire Line
	7350 2950 7350 2650
Wire Wire Line
	7800 2450 7800 2350
Wire Wire Line
	7800 4400 7650 4400
Wire Wire Line
	7650 4400 7650 4100
Wire Wire Line
	7550 2650 7550 2550
Wire Wire Line
	7550 2550 7800 2550
Wire Wire Line
	3050 2750 3050 2850
Wire Wire Line
	3250 2850 3250 2750
Connection ~ 3250 2750
NoConn ~ 3150 3250
NoConn ~ 3250 3250
$Comp
L R_PACK4 RP2
U 1 1 4D9DC1B4
P 3000 3050
F 0 "RP2" H 3000 3500 40  0000 C CNN
F 1 "1k" H 3000 3000 40  0000 C CNN
F 2 "4X0603" H 3000 3050 60  0001 C CNN
F 3 "" H 3000 3050 60  0001 C CNN
	1    3000 3050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR042
U 1 1 4D0FDD4E
P 7550 4750
F 0 "#PWR042" H 7550 4750 30  0001 C CNN
F 1 "GND" H 7550 4680 30  0001 C CNN
F 2 "" H 7550 4750 60  0001 C CNN
F 3 "" H 7550 4750 60  0001 C CNN
	1    7550 4750
	1    0    0    -1  
$EndComp
$Comp
L 3V3 #PWR043
U 1 1 4D0FDD41
P 7350 2650
F 0 "#PWR043" H 7350 2750 40  0001 C CNN
F 1 "3V3" H 7350 2775 40  0000 C CNN
F 2 "" H 7350 2650 60  0001 C CNN
F 3 "" H 7350 2650 60  0001 C CNN
	1    7350 2650
	1    0    0    -1  
$EndComp
$Comp
L 3V3 #PWR044
U 1 1 4CAC8AB4
P 3200 2650
F 0 "#PWR044" H 3200 2750 40  0001 C CNN
F 1 "3V3" H 3200 2775 40  0000 C CNN
F 2 "" H 3200 2650 60  0001 C CNN
F 3 "" H 3200 2650 60  0001 C CNN
	1    3200 2650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR045
U 1 1 4CAC88B4
P 7800 2350
F 0 "#PWR045" H 7800 2440 20  0001 C CNN
F 1 "+5V" H 7800 2440 30  0000 C CNN
F 2 "" H 7800 2350 60  0001 C CNN
F 3 "" H 7800 2350 60  0001 C CNN
	1    7800 2350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR046
U 1 1 4CAC88AE
P 7800 4100
F 0 "#PWR046" H 7800 4190 20  0001 C CNN
F 1 "+5V" H 7800 4190 30  0000 C CNN
F 2 "" H 7800 4100 60  0001 C CNN
F 3 "" H 7800 4100 60  0001 C CNN
	1    7800 4100
	1    0    0    -1  
$EndComp
$Comp
L 3V3 #PWR047
U 1 1 4CAC87D9
P 7650 4100
F 0 "#PWR047" H 7650 4200 40  0001 C CNN
F 1 "3V3" H 7650 4225 40  0000 C CNN
F 2 "" H 7650 4100 60  0001 C CNN
F 3 "" H 7650 4100 60  0001 C CNN
	1    7650 4100
	1    0    0    -1  
$EndComp
$Comp
L 3V3 #PWR048
U 1 1 4CAC87D4
P 7650 2350
F 0 "#PWR048" H 7650 2450 40  0001 C CNN
F 1 "3V3" H 7650 2475 40  0000 C CNN
F 2 "" H 7650 2350 60  0001 C CNN
F 3 "" H 7650 2350 60  0001 C CNN
	1    7650 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR049
U 1 1 4CAC87AD
P 7550 2650
F 0 "#PWR049" H 7550 2650 30  0001 C CNN
F 1 "GND" H 7550 2580 30  0001 C CNN
F 2 "" H 7550 2650 60  0001 C CNN
F 3 "" H 7550 2650 60  0001 C CNN
	1    7550 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR050
U 1 1 4CAC87A9
P 7550 4400
F 0 "#PWR050" H 7550 4400 30  0001 C CNN
F 1 "GND" H 7550 4330 30  0001 C CNN
F 2 "" H 7550 4400 60  0001 C CNN
F 3 "" H 7550 4400 60  0001 C CNN
	1    7550 4400
	1    0    0    -1  
$EndComp
Text GLabel 6550 4900 0    60   Input ~ 0
BRICKLET-IO1_1
Text GLabel 6550 3150 0    60   Input ~ 0
BRICKLET-IO0_1/DA0
Text GLabel 6550 3350 0    60   Input ~ 0
BRICKLET-IO0_3
Text GLabel 6550 5100 0    60   Input ~ 0
BRICKLET-IO1_3
Text GLabel 6550 5000 0    60   Input ~ 0
BRICKLET-IO1_2/PWM1
Text GLabel 6550 3250 0    60   Input ~ 0
BRICKLET-IO0_2/PWM0
Text GLabel 6550 4800 0    60   Input ~ 0
BRICKLET-IO1_0/AD1
Text GLabel 6550 3050 0    60   Input ~ 0
BRICKLET-IO0_0/AD0
Text GLabel 2450 3600 0    60   Input ~ 0
BRICKLET-I2C-SCL
Text GLabel 2450 3700 0    60   Input ~ 0
BRICKLET-I2C-SDA
$Comp
L GND #PWR051
U 1 1 4CAC33F4
P 8250 5300
F 0 "#PWR051" H 8250 5300 30  0001 C CNN
F 1 "GND" H 8250 5230 30  0001 C CNN
F 2 "" H 8250 5300 60  0001 C CNN
F 3 "" H 8250 5300 60  0001 C CNN
	1    8250 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR052
U 1 1 4CAC33ED
P 8250 3550
F 0 "#PWR052" H 8250 3550 30  0001 C CNN
F 1 "GND" H 8250 3480 30  0001 C CNN
F 2 "" H 8250 3550 60  0001 C CNN
F 3 "" H 8250 3550 60  0001 C CNN
	1    8250 3550
	1    0    0    -1  
$EndComp
$Comp
L CON-SENSOR P2
U 1 1 4CAC3392
P 8250 4650
F 0 "P2" H 8000 5200 60  0000 C CNN
F 1 "CON-SENSOR" V 8450 4650 60  0000 C CNN
F 2 "CON-SENSOR" H 8250 4650 60  0001 C CNN
F 3 "" H 8250 4650 60  0001 C CNN
	1    8250 4650
	1    0    0    -1  
$EndComp
$Comp
L CON-SENSOR P1
U 1 1 4CAC338E
P 8250 2900
F 0 "P1" H 8000 3450 60  0000 C CNN
F 1 "CON-SENSOR" V 8450 2900 60  0000 C CNN
F 2 "CON-SENSOR" H 8250 2900 60  0001 C CNN
F 3 "" H 8250 2900 60  0001 C CNN
	1    8250 2900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
