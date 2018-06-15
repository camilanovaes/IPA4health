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
LIBS:Baymax-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L LM386 U1
U 1 1 5B23C343
P 7850 1300
F 0 "U1" H 7900 1600 50  0000 L CNN
F 1 "LM386" H 7950 1450 50  0000 L CNN
F 2 "" H 7950 1400 50  0001 C CNN
F 3 "" H 8050 1500 50  0001 C CNN
	1    7850 1300
	1    0    0    1   
$EndComp
$Comp
L R R1
U 1 1 5B23C3EF
P 2100 1700
F 0 "R1" V 2180 1700 50  0000 C CNN
F 1 "4.7K" V 2100 1700 50  0000 C CNN
F 2 "" V 2030 1700 50  0001 C CNN
F 3 "" H 2100 1700 50  0001 C CNN
	1    2100 1700
	-1   0    0    1   
$EndComp
$Comp
L C C3
U 1 1 5B23C470
P 8500 1650
F 0 "C3" H 8525 1750 50  0000 L CNN
F 1 "100nF" H 8525 1550 50  0000 L CNN
F 2 "" H 8538 1500 50  0001 C CNN
F 3 "" H 8500 1650 50  0001 C CNN
	1    8500 1650
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5B23C64E
P 2350 1700
F 0 "R2" V 2430 1700 50  0000 C CNN
F 1 "4.7K" V 2350 1700 50  0000 C CNN
F 2 "" V 2280 1700 50  0001 C CNN
F 3 "" H 2350 1700 50  0001 C CNN
	1    2350 1700
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x04 J1
U 1 1 5B23C6E0
P 1550 1450
F 0 "J1" H 1550 1650 50  0000 C CNN
F 1 "Conn_01x04" V 1700 1400 50  0000 C CNN
F 2 "" H 1550 1450 50  0001 C CNN
F 3 "" H 1550 1450 50  0001 C CNN
	1    1550 1450
	-1   0    0    1   
$EndComp
Text Notes 1350 1100 0    60   ~ 0
MAX30100
$Comp
L Conn_01x04 J2
U 1 1 5B23CABE
P 3050 1350
F 0 "J2" H 3050 1050 50  0000 C CNN
F 1 "Conn_01x04" V 3200 1300 50  0000 C CNN
F 2 "" H 3050 1350 50  0001 C CNN
F 3 "" H 3050 1350 50  0001 C CNN
	1    3050 1350
	1    0    0    -1  
$EndComp
Text Notes 2800 1100 0    60   ~ 0
Arduino UNO
Text Notes 2650 1250 0    60   ~ 0
GND
Text Notes 1800 1250 0    60   ~ 0
GND
Text Notes 2700 1550 0    60   ~ 0
5V
Text Notes 1800 1550 0    60   ~ 0
Vcc
Text Notes 1800 1450 0    60   ~ 0
SCL
Text Notes 2700 1450 0    60   ~ 0
A5
Text Notes 2700 1350 0    60   ~ 0
A4
Text Notes 1800 1350 0    60   ~ 0
SDA
$Comp
L CP1 C2
U 1 1 5B23DDBE
P 8050 2050
F 0 "C2" H 8075 2150 50  0000 L CNN
F 1 "100uF" H 8075 1950 50  0000 L CNN
F 2 "" H 8050 2050 50  0001 C CNN
F 3 "" H 8050 2050 50  0001 C CNN
	1    8050 2050
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 5B23DE24
P 7500 2150
F 0 "C1" H 7525 2250 50  0000 L CNN
F 1 "100uF" H 7250 2050 50  0000 L CNN
F 2 "" H 7500 2150 50  0001 C CNN
F 3 "" H 7500 2150 50  0001 C CNN
	1    7500 2150
	1    0    0    -1  
$EndComp
$Comp
L CP1 C4
U 1 1 5B23DE74
P 8850 1300
F 0 "C4" V 8900 1100 50  0000 L CNN
F 1 "1000uF" V 9000 1200 50  0000 L CNN
F 2 "" H 8850 1300 50  0001 C CNN
F 3 "" H 8850 1300 50  0001 C CNN
	1    8850 1300
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 5B23ED4D
P 6400 1250
F 0 "R3" V 6480 1250 50  0000 C CNN
F 1 "1K" V 6400 1250 50  0000 C CNN
F 2 "" V 6330 1250 50  0001 C CNN
F 3 "" H 6400 1250 50  0001 C CNN
	1    6400 1250
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 5B23F58E
P 6400 1450
F 0 "R4" V 6300 1450 50  0000 C CNN
F 1 "1K" V 6400 1450 50  0000 C CNN
F 2 "" V 6330 1450 50  0001 C CNN
F 3 "" H 6400 1450 50  0001 C CNN
	1    6400 1450
	0    -1   -1   0   
$EndComp
Text Notes 5500 1300 0    60   ~ 0
LEFT_AUDIO
Text Notes 5450 1500 0    60   ~ 0
RIGHT_AUDIO
Text Notes 5000 1100 0    60   ~ 0
P2_Out
$Comp
L Conn_01x03 J3
U 1 1 5B23F6E8
P 5150 1400
F 0 "J3" H 5150 1600 50  0000 C CNN
F 1 "Conn_01x03" V 5300 1400 50  0000 C CNN
F 2 "" H 5150 1400 50  0001 C CNN
F 3 "" H 5150 1400 50  0001 C CNN
	1    5150 1400
	-1   0    0    1   
$EndComp
Wire Wire Line
	1750 1550 1950 1550
Connection ~ 2350 1350
Connection ~ 2100 1450
Wire Wire Line
	2100 1550 2100 1450
Wire Wire Line
	2350 1550 2350 1350
Wire Wire Line
	1750 1250 2850 1250
Wire Wire Line
	1750 1350 2850 1350
Wire Wire Line
	1750 1450 2850 1450
Wire Wire Line
	1950 1550 1950 1900
Wire Wire Line
	1950 1900 2500 1900
Wire Wire Line
	2500 1900 2500 1550
Wire Wire Line
	2500 1550 2850 1550
Wire Wire Line
	2100 1850 2100 1900
Connection ~ 2100 1900
Wire Wire Line
	2350 1850 2350 1900
Connection ~ 2350 1900
Wire Wire Line
	5350 1300 6150 1300
Wire Wire Line
	6150 1300 6150 1250
Wire Wire Line
	6150 1250 6250 1250
Wire Wire Line
	5350 1400 6150 1400
Wire Wire Line
	6150 1400 6150 1450
Wire Wire Line
	6150 1450 6250 1450
$Comp
L Earth #PWR1
U 1 1 5B23F7A8
P 5400 1750
F 0 "#PWR1" H 5400 1500 50  0001 C CNN
F 1 "Earth" H 5400 1600 50  0001 C CNN
F 2 "" H 5400 1750 50  0001 C CNN
F 3 "" H 5400 1750 50  0001 C CNN
	1    5400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 1500 5400 1500
Wire Wire Line
	5400 1500 5400 1750
Text Notes 5450 1700 0    60   ~ 0
GND
Wire Wire Line
	6550 1250 6600 1250
Wire Wire Line
	6600 1250 6600 1450
Wire Wire Line
	6600 1450 6550 1450
Wire Wire Line
	6700 1400 7550 1400
Wire Wire Line
	6700 1400 6700 1350
Wire Wire Line
	6700 1350 6600 1350
Connection ~ 6600 1350
Text Notes 6750 1400 0    60   ~ 0
MONO_AUDIO
$Comp
L Earth #PWR2
U 1 1 5B240F4D
P 7250 950
F 0 "#PWR2" H 7250 700 50  0001 C CNN
F 1 "Earth" H 7250 800 50  0001 C CNN
F 2 "" H 7250 950 50  0001 C CNN
F 3 "" H 7250 950 50  0001 C CNN
	1    7250 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 900  7750 1000
Wire Wire Line
	7550 1200 7450 1200
Wire Wire Line
	7450 1200 7450 900 
Wire Wire Line
	7250 900  7750 900 
Wire Wire Line
	7250 900  7250 950 
Connection ~ 7450 900 
$Comp
L Earth #PWR3
U 1 1 5B2414C5
P 7500 2550
F 0 "#PWR3" H 7500 2300 50  0001 C CNN
F 1 "Earth" H 7500 2400 50  0001 C CNN
F 2 "" H 7500 2550 50  0001 C CNN
F 3 "" H 7500 2550 50  0001 C CNN
	1    7500 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1600 7750 2150
Wire Wire Line
	7500 2000 7500 1900
Wire Wire Line
	7500 1900 7750 1900
Connection ~ 7750 1900
Wire Wire Line
	7500 2300 7500 2550
Wire Wire Line
	7850 1600 7850 1800
Wire Wire Line
	7850 1800 8050 1800
Wire Wire Line
	8050 1800 8050 1900
$Comp
L Earth #PWR5
U 1 1 5B241AE4
P 8050 2550
F 0 "#PWR5" H 8050 2300 50  0001 C CNN
F 1 "Earth" H 8050 2400 50  0001 C CNN
F 2 "" H 8050 2550 50  0001 C CNN
F 3 "" H 8050 2550 50  0001 C CNN
	1    8050 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 2200 8050 2550
$Comp
L Conn_01x02 J4
U 1 1 5B241B74
P 9750 1300
F 0 "J4" H 9750 1400 50  0000 C CNN
F 1 "Conn_01x02" V 9900 1250 50  0000 C CNN
F 2 "" H 9750 1300 50  0001 C CNN
F 3 "" H 9750 1300 50  0001 C CNN
	1    9750 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1300 8700 1300
Wire Wire Line
	9000 1300 9550 1300
Wire Wire Line
	8500 1500 8500 1300
Connection ~ 8500 1300
$Comp
L Earth #PWR6
U 1 1 5B241E7E
P 8500 2050
F 0 "#PWR6" H 8500 1800 50  0001 C CNN
F 1 "Earth" H 8500 1900 50  0001 C CNN
F 2 "" H 8500 2050 50  0001 C CNN
F 3 "" H 8500 2050 50  0001 C CNN
	1    8500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1800 8500 2050
$Comp
L Earth #PWR7
U 1 1 5B241EF1
P 9250 1700
F 0 "#PWR7" H 9250 1450 50  0001 C CNN
F 1 "Earth" H 9250 1550 50  0001 C CNN
F 2 "" H 9250 1700 50  0001 C CNN
F 3 "" H 9250 1700 50  0001 C CNN
	1    9250 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 1400 9250 1400
Wire Wire Line
	9250 1400 9250 1700
Text Notes 9600 1050 0    60   ~ 0
Speaker
Text Notes 9450 1300 0    60   ~ 0
+
Text Notes 9450 1400 0    60   ~ 0
-
$Comp
L +5V #PWR4
U 1 1 5B2420BB
P 7750 2150
F 0 "#PWR4" H 7750 2000 50  0001 C CNN
F 1 "+5V" H 7750 2290 50  0000 C CNN
F 2 "" H 7750 2150 50  0001 C CNN
F 3 "" H 7750 2150 50  0001 C CNN
	1    7750 2150
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x08 J?
U 1 1 5B243D6A
P 1700 3300
F 0 "J?" H 1700 3700 50  0000 C CNN
F 1 "Conn_01x08" H 1700 2800 50  0000 C CNN
F 2 "" H 1700 3300 50  0001 C CNN
F 3 "" H 1700 3300 50  0001 C CNN
	1    1700 3300
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x08 J?
U 1 1 5B243E27
P 3800 3300
F 0 "J?" H 3800 3700 50  0000 C CNN
F 1 "Conn_01x08" H 3800 2800 50  0000 C CNN
F 2 "" H 3800 3300 50  0001 C CNN
F 3 "" H 3800 3300 50  0001 C CNN
	1    3800 3300
	1    0    0    1   
$EndComp
Text Notes 3550 2650 0    60   ~ 0
Arduino UNO
Text Notes 1600 2650 0    60   ~ 0
Display
Wire Wire Line
	1900 2900 3600 2900
Wire Wire Line
	1900 3000 3600 3000
Wire Wire Line
	1900 3100 3600 3100
Wire Wire Line
	1900 3200 3600 3200
Wire Wire Line
	1900 3300 3600 3300
Wire Wire Line
	1900 3400 3600 3400
Wire Wire Line
	1900 3500 3600 3500
Wire Wire Line
	1900 3600 3600 3600
Text Notes 2000 2900 0    60   ~ 0
LED
Text Notes 2000 3000 0    60   ~ 0
SCK
Text Notes 2000 3100 0    60   ~ 0
SDA
Text Notes 2000 3200 0    60   ~ 0
A0
Text Notes 2000 3300 0    60   ~ 0
RESET
Text Notes 2000 3400 0    60   ~ 0
CS
Text Notes 2000 3500 0    60   ~ 0
GND
Text Notes 2000 3600 0    60   ~ 0
Vcc
Text Notes 3350 3000 0    60   ~ 0
13
Text Notes 3350 3100 0    60   ~ 0
11
Text Notes 3400 3200 0    60   ~ 0
9
Text Notes 3400 3300 0    60   ~ 0
8
Text Notes 3350 3400 0    60   ~ 0
10
Text Notes 3300 3500 0    60   ~ 0
GND
Text Notes 3350 2900 0    60   ~ 0
3V3
Text Notes 3350 3600 0    60   ~ 0
5V
$Comp
L Conn_01x07 J?
U 1 1 5B244938
P 8700 3850
F 0 "J?" H 8700 3450 50  0000 C CNN
F 1 "Conn_01x07" H 8700 4300 50  0000 C CNN
F 2 "" H 8700 3850 50  0001 C CNN
F 3 "" H 8700 3850 50  0001 C CNN
	1    8700 3850
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x07 J?
U 1 1 5B2449DF
P 6800 3850
F 0 "J?" H 6800 3450 50  0000 C CNN
F 1 "Conn_01x07" H 6800 4300 50  0000 C CNN
F 2 "" H 6800 3850 50  0001 C CNN
F 3 "" H 6800 3850 50  0001 C CNN
	1    6800 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7000 3550 8500 3550
Wire Wire Line
	8500 3650 7000 3650
Wire Wire Line
	7000 3750 8500 3750
Wire Wire Line
	8500 3850 7000 3850
Wire Wire Line
	7000 3950 8500 3950
Wire Wire Line
	8500 4050 7000 4050
Wire Wire Line
	7000 4150 8500 4150
Text Notes 6700 3300 0    60   ~ 0
RFID
Text Notes 8500 3300 0    60   ~ 0
Raspberry
Text Notes 7100 3550 0    60   ~ 0
SDA
Text Notes 7100 3650 0    60   ~ 0
SCK
Text Notes 7100 3750 0    60   ~ 0
MOSI
Text Notes 7100 3850 0    60   ~ 0
MISO
Text Notes 7100 3950 0    60   ~ 0
GND
Text Notes 7100 4050 0    60   ~ 0
RST
Text Notes 7100 4150 0    60   ~ 0
3V3
Text Notes 8100 3850 0    60   ~ 0
GPIO  9
Text Notes 8300 3950 0    60   ~ 0
GND
Text Notes 8100 4050 0    60   ~ 0
GPIO 25
Text Notes 8300 4150 0    60   ~ 0
3V3
Text Notes 8100 3550 0    60   ~ 0
GPIO  8
Text Notes 8100 3650 0    60   ~ 0
GPIO 11
Text Notes 8100 3750 0    60   ~ 0
GPIO 10
$EndSCHEMATC
