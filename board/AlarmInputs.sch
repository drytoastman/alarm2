EESchema Schematic File Version 4
EELAYER 30 0
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
L Connector:Screw_Terminal_01x08 J2
U 1 1 60DBBE57
P 2960 2400
F 0 "J2" H 3040 2392 50  0000 L CNN
F 1 "Inputs" H 3040 2301 50  0000 L CNN
F 2 "_project:8pinscrew" H 2960 2400 50  0001 C CNN
F 3 "~" H 2960 2400 50  0001 C CNN
	1    2960 2400
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x08 J3
U 1 1 60DBD909
P 2960 3530
F 0 "J3" H 3040 3522 50  0000 L CNN
F 1 "Inputs" H 3040 3431 50  0000 L CNN
F 2 "_project:8pinscrew" H 2960 3530 50  0001 C CNN
F 3 "~" H 2960 3530 50  0001 C CNN
	1    2960 3530
	-1   0    0    -1  
$EndComp
Text GLabel 3160 2400 2    50   BiDi ~ 0
GND
Text GLabel 3160 2800 2    50   BiDi ~ 0
GND
Text GLabel 3160 3530 2    50   BiDi ~ 0
GND
Text GLabel 3160 3930 2    50   BiDi ~ 0
GND
Text GLabel 6750 3350 2    50   BiDi ~ 0
GND
Text GLabel 6750 2850 2    50   BiDi ~ 0
GND
Text GLabel 5350 1850 0    50   BiDi ~ 0
GND
Text GLabel 5350 2350 0    50   BiDi ~ 0
GND
Text GLabel 5350 2850 0    50   BiDi ~ 0
GND
Text GLabel 5350 3350 0    50   BiDi ~ 0
GND
Text GLabel 6750 1850 2    50   BiDi ~ 0
GND
Text GLabel 6750 2350 2    50   BiDi ~ 0
GND
$Comp
L pico:Pico U1
U 1 1 60DAD490
P 6050 2600
F 0 "U1" H 6050 3815 50  0000 C CNN
F 1 "Pico" H 6050 3724 50  0000 C CNN
F 2 "_project:RPi_Pico_SMD_TH" V 6050 2600 50  0001 C CNN
F 3 "" H 6050 2600 50  0001 C CNN
	1    6050 2600
	1    0    0    -1  
$EndComp
Text GLabel 5350 1750 0    50   Input ~ 0
IO1
Text GLabel 5350 1950 0    50   Input ~ 0
IO2
Text GLabel 5350 2050 0    50   Input ~ 0
IO3
Text GLabel 5350 2150 0    50   Input ~ 0
IO4
Text GLabel 5350 2250 0    50   Input ~ 0
IO5
Text GLabel 5350 2450 0    50   Input ~ 0
IO6
Text GLabel 5350 2550 0    50   Input ~ 0
IO7
Text GLabel 5350 2650 0    50   Input ~ 0
IO8
Text GLabel 5350 2750 0    50   Input ~ 0
IO9
Text GLabel 5350 2950 0    50   Input ~ 0
IO10
Text GLabel 5350 3050 0    50   Input ~ 0
IO11
Text GLabel 5350 3150 0    50   Input ~ 0
IO12
Text GLabel 5350 3250 0    50   Input ~ 0
IO13
Text GLabel 5350 3450 0    50   Input ~ 0
IO14
Text GLabel 5350 3550 0    50   Input ~ 0
IO15
Text GLabel 6750 3550 2    50   Input ~ 0
IO16
Text GLabel 6750 3450 2    50   Input ~ 0
IO17
Text GLabel 6750 3250 2    50   Input ~ 0
IO18
Text GLabel 6750 3150 2    50   Input ~ 0
IO19
Text GLabel 6750 2950 2    50   Input ~ 0
MOTION
$Comp
L Connector:Screw_Terminal_01x08 J4
U 1 1 61086365
P 2960 4780
F 0 "J4" H 3040 4772 50  0000 L CNN
F 1 "Inputs" H 3040 4681 50  0000 L CNN
F 2 "_project:8pinscrew" H 2960 4780 50  0001 C CNN
F 3 "~" H 2960 4780 50  0001 C CNN
	1    2960 4780
	-1   0    0    -1  
$EndComp
Text GLabel 3160 4780 2    50   BiDi ~ 0
GND
Text GLabel 3160 5180 2    50   BiDi ~ 0
GND
Text GLabel 3160 2100 2    50   Output ~ 0
IO0
Text GLabel 3160 2200 2    50   Output ~ 0
IO1
Text GLabel 3160 2300 2    50   Output ~ 0
IO2
Text GLabel 3160 2500 2    50   Output ~ 0
IO3
Text GLabel 3160 2600 2    50   Output ~ 0
IO4
Text GLabel 3160 2700 2    50   Output ~ 0
IO5
Text GLabel 3160 3230 2    50   Output ~ 0
IO6
Text GLabel 3160 3330 2    50   Output ~ 0
IO7
Text GLabel 3160 3430 2    50   Output ~ 0
IO8
Text GLabel 3160 3630 2    50   Output ~ 0
IO9
Text GLabel 3160 3730 2    50   Output ~ 0
IO10
Text GLabel 3160 3830 2    50   Output ~ 0
IO11
Text GLabel 3160 4480 2    50   Output ~ 0
IO12
Text GLabel 3160 4580 2    50   Output ~ 0
IO13
Text GLabel 3160 4680 2    50   Output ~ 0
IO14
Text GLabel 3160 4880 2    50   Output ~ 0
IO15
Text GLabel 3160 4980 2    50   Output ~ 0
IO16
Text GLabel 3160 5080 2    50   Output ~ 0
IO17
Text GLabel 3160 5800 2    50   Output ~ 0
IO19
Text GLabel 3160 5700 2    50   Output ~ 0
IO18
$Comp
L Connector:Screw_Terminal_01x08 J6
U 1 1 6108929D
P 4540 5950
F 0 "J6" H 4620 5942 50  0000 L CNN
F 1 "4-Wire Connections" H 4620 5851 50  0000 L CNN
F 2 "_project:8pinscrew" H 4540 5950 50  0001 C CNN
F 3 "~" H 4540 5950 50  0001 C CNN
	1    4540 5950
	-1   0    0    -1  
$EndComp
Text GLabel 4740 6050 2    50   Output ~ 0
MOTION
Text GLabel 3160 6000 2    50   BiDi ~ 0
GND
Text GLabel 9990 4310 2    50   BiDi ~ 0
HW2
Text GLabel 9390 3340 0    50   BiDi ~ 0
12V
Text GLabel 9990 3340 2    50   Output ~ 0
ALARM
Text GLabel 4740 6350 2    50   BiDi ~ 0
12VGND
Text GLabel 5350 1650 0    50   Input ~ 0
IO0
Text GLabel 4750 4470 2    50   Input ~ 0
ALARM
Text GLabel 4740 6250 2    50   BiDi ~ 0
12V
Text GLabel 4750 4570 2    50   BiDi ~ 0
12VGND
Text GLabel 4750 4870 2    50   BiDi ~ 0
HW2
Text GLabel 4750 4970 2    50   BiDi ~ 0
HW1
Text GLabel 4740 6150 2    50   BiDi ~ 0
GND
$Comp
L Relay:G5Q-1A K1
U 1 1 60FE7538
P 9690 3140
F 0 "K1" V 9123 3140 50  0000 C CNN
F 1 "G5Q-1A" V 9214 3140 50  0000 C CNN
F 2 "Relay_THT:Relay_SPST_Omron-G5Q-1A" H 10040 3090 50  0001 L CNN
F 3 "https://www.omron.com/ecb/products/pdf/en-g5q.pdf" H 9690 3140 50  0001 C CNN
	1    9690 3140
	0    1    1    0   
$EndComp
$Comp
L Relay:G5Q-1A K2
U 1 1 60FE8BFE
P 9690 4110
F 0 "K2" V 9123 4110 50  0000 C CNN
F 1 "G5Q-1A" V 9214 4110 50  0000 C CNN
F 2 "Relay_THT:Relay_SPST_Omron-G5Q-1A" H 10040 4060 50  0001 L CNN
F 3 "https://www.omron.com/ecb/products/pdf/en-g5q.pdf" H 9690 4110 50  0001 C CNN
	1    9690 4110
	0    1    1    0   
$EndComp
Text GLabel 9990 2940 2    50   BiDi ~ 0
5V
Text GLabel 9990 3910 2    50   BiDi ~ 0
5V
$Comp
L Transistor_Array:ULN2003 U2
U 1 1 60FED454
P 8130 2550
F 0 "U2" H 8130 3217 50  0000 C CNN
F 1 "ULN2003" H 8130 3126 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 8180 2000 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 8230 2350 50  0001 C CNN
	1    8130 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 2250 7160 2250
Wire Wire Line
	7160 2250 7160 2350
Wire Wire Line
	8530 2350 8910 2350
Text GLabel 6750 3050 2    50   Input ~ 0
HWINPUT
$Comp
L Connector:Barrel_Jack_Switch J7
U 1 1 61000B58
P 9710 4990
F 0 "J7" H 9480 4940 50  0000 R CNN
F 1 "Barrel_Jack_Switch" H 9480 5031 50  0000 R CNN
F 2 "Connector_BarrelJack:BarrelJack_CUI_PJ-102AH_Horizontal" H 9760 4950 50  0001 C CNN
F 3 "~" H 9760 4950 50  0001 C CNN
	1    9710 4990
	-1   0    0    1   
$EndComp
Text GLabel 9350 5090 0    50   BiDi ~ 0
12V
Text GLabel 9350 4890 0    50   BiDi ~ 0
12VGND
$Comp
L Connector:Screw_Terminal_01x08 J1
U 1 1 610202BA
P 4550 4770
F 0 "J1" H 4630 4762 50  0000 L CNN
F 1 "External Devices" H 4630 4671 50  0000 L CNN
F 2 "_project:8pinscrew" H 4550 4770 50  0001 C CNN
F 3 "~" H 4550 4770 50  0001 C CNN
	1    4550 4770
	-1   0    0    -1  
$EndComp
Text GLabel 4750 5070 2    50   Input ~ 0
5V
Text GLabel 4750 5170 2    50   BiDi ~ 0
BUZZERGND
Text GLabel 6750 1650 2    50   BiDi ~ 0
5V
Text GLabel 8130 3150 3    50   BiDi ~ 0
GND
Text GLabel 8910 2150 2    50   BiDi ~ 0
5V
$Comp
L Switch:SW_Push SW1
U 1 1 6102A6C2
P 7770 1310
F 0 "SW1" H 7770 1595 50  0000 C CNN
F 1 "Reset" H 7770 1504 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_DIP_SPSTx01_Slide_6.7x4.1mm_W6.73mm_P2.54mm_LowProfile_JPin" H 7770 1510 50  0001 C CNN
F 3 "~" H 7770 1510 50  0001 C CNN
	1    7770 1310
	1    0    0    -1  
$EndComp
Text GLabel 7970 1310 2    50   BiDi ~ 0
RST
Text GLabel 7570 1310 0    50   BiDi ~ 0
GND
Text GLabel 6750 2650 2    50   BiDi ~ 0
RST
Text GLabel 9390 4310 0    50   BiDi ~ 0
HW1
Text GLabel 4740 5750 2    50   BiDi ~ 0
GND
Text GLabel 4740 5650 2    50   Output ~ 0
HWINPUT
Text GLabel 4740 5850 2    50   BiDi ~ 0
5V
Text GLabel 4740 5950 2    50   BiDi ~ 0
LEDGND
$Comp
L Connector:Screw_Terminal_01x08 J5
U 1 1 60FF03EC
P 2960 6000
F 0 "J5" H 3040 5992 50  0000 L CNN
F 1 "Inputs" H 3040 5901 50  0000 L CNN
F 2 "_project:8pinscrew" H 2960 6000 50  0001 C CNN
F 3 "~" H 2960 6000 50  0001 C CNN
	1    2960 6000
	-1   0    0    -1  
$EndComp
Text GLabel 3160 6400 2    50   BiDi ~ 0
5V
Text GLabel 8910 2350 2    50   BiDi ~ 0
LEDGND
Text GLabel 8910 2450 2    50   BiDi ~ 0
BUZZERGND
Wire Wire Line
	8530 2450 8910 2450
Wire Wire Line
	8960 2940 8960 2550
Wire Wire Line
	8960 2550 8530 2550
Wire Wire Line
	9390 2940 8960 2940
Wire Wire Line
	8530 2650 8890 2650
Wire Wire Line
	8890 2650 8890 3910
Wire Wire Line
	8890 3910 9390 3910
Text GLabel 3160 6300 2    50   BiDi ~ 0
5V
Text GLabel 3160 6200 2    50   BiDi ~ 0
5V
Text GLabel 3160 6100 2    50   BiDi ~ 0
5V
Wire Wire Line
	9350 4890 9410 4890
Wire Wire Line
	9350 5090 9410 5090
Wire Wire Line
	8530 2150 8910 2150
Text GLabel 7730 2750 0    50   BiDi ~ 0
GND
Text GLabel 7730 2850 0    50   BiDi ~ 0
GND
Text GLabel 7730 2950 0    50   BiDi ~ 0
GND
Wire Wire Line
	6750 2450 7730 2450
Wire Wire Line
	6750 2550 7730 2550
Wire Wire Line
	7160 2350 7730 2350
$Comp
L Mechanical:MountingHole H1
U 1 1 61053055
P 7990 6170
F 0 "H1" H 8090 6216 50  0000 L CNN
F 1 "MountingHole" H 8090 6125 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 7990 6170 50  0001 C CNN
F 3 "~" H 7990 6170 50  0001 C CNN
	1    7990 6170
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 610535D2
P 8980 6170
F 0 "H2" H 9080 6216 50  0000 L CNN
F 1 "MountingHole" H 9080 6125 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 8980 6170 50  0001 C CNN
F 3 "~" H 8980 6170 50  0001 C CNN
	1    8980 6170
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 2750 7160 2750
Wire Wire Line
	7160 2750 7160 2650
Wire Wire Line
	7160 2650 7730 2650
Text GLabel 3160 5900 2    50   BiDi ~ 0
GND
$EndSCHEMATC
