EESchema Schematic File Version 4
LIBS:RRAT-cache
EELAYER 26 0
EELAYER END
$Descr User 17018 11968
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
Wire Wire Line
	10900 6400 11625 6400
Text Label 11625 6400 0    70   ~ 0
SPI_SCK
Text Label 7000 1500 2    70   ~ 0
SPI_SCK
Text Label 3300 1700 2    70   ~ 0
SPI_SCK
Wire Wire Line
	10900 6200 11625 6200
Text Label 11625 6200 0    70   ~ 0
SPI_MOSI
Text Label 7000 1600 2    70   ~ 0
SPI_MOSI
Wire Wire Line
	4400 1700 3900 1700
Text Label 4400 1700 2    70   ~ 0
SPI_MOSI
Wire Wire Line
	10900 6300 11625 6300
Text Label 11625 6300 0    70   ~ 0
SPI_MISO
Text Label 7000 1700 2    70   ~ 0
SPI_MISO
Text Label 3300 1600 2    70   ~ 0
SPI_MISO
Wire Wire Line
	10900 6100 11625 6100
Text Label 11625 6100 0    70   ~ 0
SPI_NSS
Text Label 7000 1400 2    70   ~ 0
SPI_NSS
Text Label 8150 4100 0    70   ~ 0
RESET
Text Label 1800 1550 0    70   ~ 0
RESET
Text Label 5000 1050 1    70   ~ 0
XTAL1
Text Label 8150 4900 0    70   ~ 0
XTAL1
Text Label 5600 1050 1    70   ~ 0
XTAL2
Text Label 8150 4700 0    70   ~ 0
XTAL2
Text Label 1800 1900 0    70   ~ 0
TX
Wire Wire Line
	10900 5000 11625 5000
Text Label 11625 5000 0    70   ~ 0
TX
Wire Wire Line
	10900 5100 11625 5100
Text Label 11625 5100 0    70   ~ 0
RX
Text Label 11650 6000 0    70   ~ 0
RFM_IRQ
Text Label 12600 750  2    70   ~ 0
RFM_IRQ
Wire Wire Line
	14650 4200 12025 4200
Wire Wire Line
	12025 4200 12025 4300
Wire Wire Line
	12025 4300 10900 4300
Text Label 11725 4300 0    70   ~ 0
A2
Wire Wire Line
	10900 5500 12525 5500
Wire Wire Line
	12525 5500 12525 4700
Wire Wire Line
	12525 4700 14650 4700
Text Label 11725 5500 0    70   ~ 0
D5
Wire Wire Line
	10900 5700 12725 5700
Wire Wire Line
	12725 5700 12725 4900
Wire Wire Line
	12725 4900 14650 4900
Text Label 11725 5700 0    70   ~ 0
D7
Wire Wire Line
	11625 5200 10900 5200
Text Label 11625 5200 0    70   ~ 0
D2
Wire Wire Line
	13725 5000 14650 5000
Text Label 13725 5000 0    70   ~ 0
D2
Wire Wire Line
	10900 4200 11925 4200
Wire Wire Line
	11925 4200 11925 4100
Wire Wire Line
	11925 4100 14650 4100
Text Label 11725 4200 0    70   ~ 0
A1
Wire Wire Line
	10900 5300 12425 5300
Wire Wire Line
	12425 5300 12425 4600
Wire Wire Line
	12425 4600 14650 4600
Text Label 11725 5300 0    70   ~ 0
D3
Wire Wire Line
	10900 4400 12125 4400
Wire Wire Line
	12125 4400 12125 4300
Wire Wire Line
	12125 4300 14650 4300
Text Label 11725 4400 0    70   ~ 0
A3
Wire Wire Line
	10900 4700 12125 4700
Wire Wire Line
	12125 4700 12125 4500
Wire Wire Line
	12125 4500 12225 4500
Wire Wire Line
	12225 4500 12225 4400
Wire Wire Line
	12225 4400 14650 4400
Text Label 11725 4700 0    70   ~ 0
A6
Wire Wire Line
	10900 4800 12325 4800
Wire Wire Line
	12325 4800 12325 4500
Wire Wire Line
	12325 4500 14650 4500
Text Label 11725 4800 0    70   ~ 0
A7
Wire Wire Line
	10900 5400 11625 5400
Text Label 11625 5400 0    70   ~ 0
LED_HEATCALL_L
$Comp
L RRAT_consolidated:Crystal Q1
U 1 1 89B80503
P 5300 1200
F 0 "Q1" H 5150 1050 59  0000 L BNN
F 1 "32768Hz" H 5150 950 59  0000 L BNN
F 2 "RRAT Consolidated:Crystal" H 5300 1200 50  0001 C CNN
F 3 "" H 5300 1200 50  0001 C CNN
	1    5300 1200
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:GND #GND07
U 1 1 E3161DBF
P 10050 1775
F 0 "#GND07" H 10050 1775 50  0001 C CNN
F 1 "GND" H 9950 1600 59  0000 L BNN
F 2 "" H 10050 1775 50  0001 C CNN
F 3 "" H 10050 1775 50  0001 C CNN
	1    10050 1775
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:ATMEGA168-AU IC1
U 1 1 BC34DC86
P 9700 5200
F 0 "IC1" H 8700 6500 59  0000 L TNN
F 1 "ATMEGA168-AU" H 8700 3800 59  0000 L BNN
F 2 "RRAT Consolidated:TQFP32-08" H 9700 5200 50  0001 C CNN
F 3 "" H 9700 5200 50  0001 C CNN
	1    9700 5200
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:SMD2 ANT1
U 1 1 9927FDA6
P 9250 1100
F 0 "ANT1" H 8950 1050 59  0000 L BNN
F 1 "SMD2" H 9205 970 59  0001 L BNN
F 2 "RRAT Consolidated:SMD1,27-2,54" H 9250 1100 50  0001 C CNN
F 3 "" H 9250 1100 50  0001 C CNN
	1    9250 1100
	-1   0    0    1   
$EndComp
Text Notes 1200 10000 0    59   ~ 0
Copyright and related rights are licensed  under the Solderpad Hardware License,
Text Notes 1200 10100 0    59   ~ 0
Version 0.51 (the "Licence"); you may not use this file except in compliance
Text Notes 1200 10200 0    59   ~ 0
with the Licence. You may obtain a copy of the Licence at
Text Notes 1200 10300 0    59   ~ 0
http://solderpad.org/licenses/SHL-0.51.
Text Notes 1200 10400 0    59   ~ 0
Unless required by applicable law or agreed to in writing, 
Text Notes 1200 10500 0    59   ~ 0
software, hardware and materials distributed under this Licence
Text Notes 1200 10600 0    59   ~ 0
is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
Text Notes 1200 10700 0    59   ~ 0
" "
Text Notes 1200 10700 0    59   ~ 0
OF ANY KIND, either express or implied. See the Licence for the
Text Notes 1200 10800 0    59   ~ 0
specific language governing permissions and limitations under the Licence.
Text Notes 8875 975  0    59   ~ 0
50 ohm track 86mm
Wire Notes Line
	2700 700  2700 2900
Text Notes 1200 11000 0    59   ~ 0
Copyright: Bo Herrmannsen 2018, Deniz Erbilgin 2019
$Comp
L RRAT_consolidated:Conn_02x03_Odd_Even J2
U 1 1 5BA40FB2
P 3600 1700
F 0 "J2" H 3650 2017 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 3650 1926 50  0001 C CNN
F 2 "RRAT Consolidated:Pin_Header_Straight_2x03_Pitch2.54mm" H 3600 1700 50  0001 C CNN
F 3 "~" H 3600 1700 50  0001 C CNN
	1    3600 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1800 3300 1800
Text Label 3300 1800 2    70   ~ 0
RESET
Wire Wire Line
	4400 1600 3900 1600
Text Label 4400 1600 2    70   ~ 0
VCC
Text Label 3350 3700 2    70   ~ 0
TX
Text Label 3200 4900 0    70   ~ 0
RESET
Text Label 3200 4100 0    70   ~ 0
SPI_MOSI
Text Label 3200 4400 0    70   ~ 0
SPI_MISO
$Comp
L Connector_Generic:Conn_01x12 J4
U 1 1 5BC0BE7C
P 14850 4600
F 0 "J4" H 14930 4592 50  0000 L CNN
F 1 "Conn_01x12" H 14930 4501 50  0000 L CNN
F 2 "RRAT Consolidated:Pin_Header_Straight_1x12_Pitch2.54mm" H 14850 4600 50  0001 C CNN
F 3 "~" H 14850 4600 50  0001 C CNN
	1    14850 4600
	1    0    0    -1  
$EndComp
Wire Notes Line
	3800 2900 3800 5675
Wire Notes Line
	4600 750  4600 2900
Wire Notes Line
	900  2900 16200 2900
Text Notes 15225 4925 0    50   ~ 0
Unused pins: 23-27-28-2-12
Text Label 12600 1650 2    70   ~ 0
SDN
Text Label 11350 1650 2    70   ~ 0
SPI_SCK
Text Label 7000 1300 2    70   ~ 0
RFM_IRQ
Text Label 11350 750  2    70   ~ 0
SPI_NSS
Text Label 1800 1800 0    70   ~ 0
RX
$Comp
L RRAT_consolidated:R R5
U 1 1 5BB830D2
P 1700 1250
F 0 "R5" V 1493 1250 50  0000 C CNN
F 1 "4.7K" V 1584 1250 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 1630 1250 50  0001 C CNN
F 3 "~" H 1700 1250 50  0001 C CNN
	1    1700 1250
	-1   0    0    1   
$EndComp
$Comp
L RRAT_consolidated:C C4
U 1 1 5BBAA711
P 8250 5850
F 0 "C4" H 8365 5896 50  0000 L CNN
F 1 "100nF" H 8365 5805 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 8288 5700 50  0001 C CNN
F 3 "~" H 8250 5850 50  0001 C CNN
	1    8250 5850
	1    0    0    -1  
$EndComp
Text Label 7000 1900 2    70   ~ 0
SDN
$Comp
L RRAT_consolidated:R R4
U 1 1 5BBBC122
P 11250 6000
F 0 "R4" V 11150 6000 50  0000 C CNN
F 1 "1K" V 11250 6000 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 11180 6000 50  0001 C CNN
F 3 "~" H 11250 6000 50  0001 C CNN
	1    11250 6000
	0    1    1    0   
$EndComp
$Comp
L RRAT_consolidated:C C5
U 1 1 5BBBC50F
P 10050 1425
F 0 "C5" H 10165 1471 50  0000 L CNN
F 1 "100nF" H 10165 1380 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 10088 1275 50  0001 C CNN
F 3 "~" H 10050 1425 50  0001 C CNN
	1    10050 1425
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:CP C6
U 1 1 5BB8BB13
P 10550 1425
F 0 "C6" H 10668 1471 50  0000 L CNN
F 1 "10uF" H 10668 1380 50  0000 L CNN
F 2 "RRAT Consolidated:EIA3216" H 10588 1275 50  0001 C CNN
F 3 "~" H 10550 1425 50  0001 C CNN
	1    10550 1425
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:C C1
U 1 1 5BB93A2E
P 1450 1550
F 0 "C1" V 1198 1550 50  0000 C CNN
F 1 "100nF" V 1289 1550 50  0000 C CNN
F 2 "RRAT Consolidated:C0603" H 1488 1400 50  0001 C CNN
F 3 "~" H 1450 1550 50  0001 C CNN
	1    1450 1550
	0    1    1    0   
$EndComp
$Comp
L RRAT_consolidated:R R1
U 1 1 5BB9403D
P 1450 1800
F 0 "R1" V 1400 1950 50  0000 C CNN
F 1 "4.7K" V 1450 1800 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 1380 1800 50  0001 C CNN
F 3 "~" H 1450 1800 50  0001 C CNN
	1    1450 1800
	0    1    1    0   
$EndComp
$Comp
L RRAT_consolidated:R R2
U 1 1 5BB941B8
P 1450 1900
F 0 "R2" V 1400 2050 50  0000 C CNN
F 1 "4.7K" V 1450 1900 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 1380 1900 50  0001 C CNN
F 3 "~" H 1450 1900 50  0001 C CNN
	1    1450 1900
	0    1    1    0   
$EndComp
$Comp
L RRAT_consolidated:C C7
U 1 1 5BB949D5
P 11450 1000
F 0 "C7" H 11565 1046 50  0000 L CNN
F 1 "47pF" H 11565 955 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 11488 850 50  0001 C CNN
F 3 "~" H 11450 1000 50  0001 C CNN
	1    11450 1000
	1    0    0    -1  
$EndComp
Wire Notes Line
	3800 5675 875  5675
$Comp
L RRAT_consolidated:C C12
U 1 1 5BBD039E
P 5600 1850
F 0 "C12" H 5715 1896 50  0000 L CNN
F 1 "0nF" H 5715 1805 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 5638 1700 50  0001 C CNN
F 3 "~" H 5600 1850 50  0001 C CNN
	1    5600 1850
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:C C11
U 1 1 5BBD0456
P 5000 1850
F 0 "C11" H 5115 1896 50  0000 L CNN
F 1 "0nF" H 5115 1805 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 5038 1700 50  0001 C CNN
F 3 "~" H 5000 1850 50  0001 C CNN
	1    5000 1850
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:GND #GND0102
U 1 1 5BBD0690
P 5300 2200
F 0 "#GND0102" H 5300 2200 50  0001 C CNN
F 1 "GND" H 5200 2025 59  0000 L BNN
F 2 "" H 5300 2200 50  0001 C CNN
F 3 "" H 5300 2200 50  0001 C CNN
	1    5300 2200
	1    0    0    -1  
$EndComp
Text Label 11650 5600 0    70   ~ 0
SDN
$Comp
L RRAT_consolidated:R R9
U 1 1 5BBE9C11
P 11250 5600
F 0 "R9" V 11275 5450 50  0000 C CNN
F 1 "1K" V 11250 5575 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 11180 5600 50  0001 C CNN
F 3 "~" H 11250 5600 50  0001 C CNN
	1    11250 5600
	0    1    1    0   
$EndComp
$Comp
L RRAT_consolidated:R R12
U 1 1 5BC30A50
P 2950 3700
F 0 "R12" V 2975 3550 50  0000 C CNN
F 1 "1K" V 2950 3700 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 2880 3700 50  0001 C CNN
F 3 "~" H 2950 3700 50  0001 C CNN
	1    2950 3700
	0    -1   -1   0   
$EndComp
$Comp
L RRAT_consolidated:R R15
U 1 1 5BC30D90
P 2950 4200
F 0 "R15" V 2925 4345 50  0000 C CNN
F 1 "1K" V 2950 4200 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 2880 4200 50  0001 C CNN
F 3 "~" H 2950 4200 50  0001 C CNN
	1    2950 4200
	0    1    1    0   
$EndComp
$Comp
L RRAT_consolidated:R R14
U 1 1 5BC30E7B
P 2950 4400
F 0 "R14" V 2915 4560 50  0000 C CNN
F 1 "1K" V 2950 4400 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 2880 4400 50  0001 C CNN
F 3 "~" H 2950 4400 50  0001 C CNN
	1    2950 4400
	0    1    1    0   
$EndComp
$Comp
L RRAT_consolidated:R R13
U 1 1 5BC30F0B
P 2950 4100
F 0 "R13" V 2905 4250 50  0000 C CNN
F 1 "1K" V 2950 4100 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 2880 4100 50  0001 C CNN
F 3 "~" H 2950 4100 50  0001 C CNN
	1    2950 4100
	0    1    1    0   
$EndComp
Text Label 3200 4200 0    70   ~ 0
SPI_SCK
$Comp
L RRAT_consolidated:R R10
U 1 1 5BC5050C
P 2950 3800
F 0 "R10" V 2975 3650 50  0000 C CNN
F 1 "1K" V 2950 3800 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 2880 3800 50  0001 C CNN
F 3 "~" H 2950 3800 50  0001 C CNN
	1    2950 3800
	0    -1   -1   0   
$EndComp
$Comp
L RRAT_consolidated:R R18
U 1 1 5BCD3F81
P 7450 5500
F 0 "R18" V 7542 5456 50  0000 C CNN
F 1 "1R" V 7450 5500 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 7380 5500 50  0001 C CNN
F 3 "~" H 7450 5500 50  0001 C CNN
	1    7450 5500
	0    -1   -1   0   
$EndComp
$Comp
L RRAT_consolidated:R R16
U 1 1 5BCE5187
P 2650 5350
F 0 "R16" V 2675 5200 50  0000 C CNN
F 1 "1K" V 2650 5350 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 2580 5350 50  0001 C CNN
F 3 "~" H 2650 5350 50  0001 C CNN
	1    2650 5350
	0    -1   -1   0   
$EndComp
$Comp
L RRAT_consolidated:R R17
U 1 1 5BCE524A
P 1150 5200
F 0 "R17" V 1175 5050 50  0000 C CNN
F 1 "1K" V 1150 5200 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 1080 5200 50  0001 C CNN
F 3 "~" H 1150 5200 50  0001 C CNN
	1    1150 5200
	0    1    1    0   
$EndComp
Text Label 750  5200 0    70   ~ 0
D7
Wire Wire Line
	12925 4800 14650 4800
Text Label 12925 4800 0    70   ~ 0
LED_HEATCALL_L
$Comp
L RRAT_consolidated:R R3
U 1 1 5BC58475
P 1450 2100
F 0 "R3" V 1475 1950 50  0000 C CNN
F 1 "1K" V 1450 2100 50  0000 C CNN
F 2 "RRAT Consolidated:R0603" V 1380 2100 50  0001 C CNN
F 3 "~" H 1450 2100 50  0001 C CNN
	1    1450 2100
	0    -1   -1   0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5BC72BE1
P 2050 2000
F 0 "JP1" H 2050 2113 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 2050 2114 50  0001 C CNN
F 2 "RRAT Consolidated:JUMPER-SOLDER-SMD" H 2050 2000 50  0001 C CNN
F 3 "~" H 2050 2000 50  0001 C CNN
	1    2050 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 4200 1300 4200
Wire Wire Line
	1300 4200 1300 3400
$Comp
L power:+3V3 #PWR0101
U 1 1 5CF9DFEF
P 1300 3250
F 0 "#PWR0101" H 1300 3100 50  0001 C CNN
F 1 "+3V3" H 1315 3423 50  0000 C CNN
F 2 "" H 1300 3250 50  0001 C CNN
F 3 "" H 1300 3250 50  0001 C CNN
	1    1300 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3250 1300 3400
Connection ~ 1300 3400
Text Label 3350 3800 2    70   ~ 0
RX
Text Label 3050 5350 2    70   ~ 0
D2
Wire Wire Line
	2800 3700 2300 3700
Wire Wire Line
	2800 3800 2300 3800
Wire Wire Line
	2800 4400 2300 4400
Wire Wire Line
	2800 4100 2300 4100
Wire Wire Line
	2800 4200 2300 4200
Wire Wire Line
	3100 3700 3350 3700
Wire Wire Line
	3100 3800 3350 3800
Wire Wire Line
	3100 4400 3200 4400
Wire Wire Line
	3100 4100 3200 4100
Wire Wire Line
	3100 4200 3200 4200
Wire Wire Line
	750  5200 1000 5200
Wire Wire Line
	1300 5200 1800 5200
Wire Wire Line
	1650 3800 1800 3800
Wire Wire Line
	2300 4000 2600 4000
Wire Wire Line
	2300 4900 3200 4900
Wire Wire Line
	2600 4000 2600 4300
$Comp
L RRAT_consolidated:Conn_02x20_Odd_Even J3
U 1 1 5BBF9168
P 2000 4300
F 0 "J3" H 2050 5417 50  0000 C CNN
F 1 "Conn_02x20_Odd_Even" H 2050 5326 50  0001 C CNN
F 2 "RRAT Consolidated:Pin_Header_Straight_2x20_Pitch2.54mm" H 2000 4300 50  0001 C CNN
F 3 "~" H 2000 4300 50  0001 C CNN
	1    2000 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 5000 2600 5000
Wire Wire Line
	2300 4800 2600 4800
Connection ~ 2600 4800
Wire Wire Line
	2600 4800 2600 5000
Wire Wire Line
	2600 5050 2600 5000
Connection ~ 2600 5000
Wire Wire Line
	2300 5100 2450 5100
Wire Wire Line
	2450 5100 2450 5350
Wire Wire Line
	2450 5350 2500 5350
Wire Wire Line
	2300 3600 2600 3600
Wire Wire Line
	2600 3600 2600 4000
Connection ~ 2600 4000
Wire Wire Line
	1800 5300 1650 5300
Wire Wire Line
	1650 5300 1650 4600
Wire Wire Line
	1650 5350 1650 5300
Connection ~ 1650 5300
Wire Wire Line
	1800 4600 1650 4600
Connection ~ 1650 4600
Wire Wire Line
	1650 4600 1650 3800
NoConn ~ 1800 3500
NoConn ~ 1800 3600
NoConn ~ 1800 3700
NoConn ~ 1800 3900
NoConn ~ 1800 4000
NoConn ~ 1800 4100
NoConn ~ 1800 4300
NoConn ~ 1800 4400
NoConn ~ 1800 4500
NoConn ~ 1800 4700
NoConn ~ 1800 4800
NoConn ~ 1800 4900
NoConn ~ 1800 5000
NoConn ~ 1800 5100
NoConn ~ 2300 5300
NoConn ~ 2300 5200
NoConn ~ 2300 4700
NoConn ~ 2300 4600
NoConn ~ 2300 4500
NoConn ~ 2300 3500
NoConn ~ 2300 3400
$Comp
L RRAT_consolidated:Conn_01x06 J1
U 1 1 5BA41073
P 900 2000
F 0 "J1" V 866 1612 50  0000 R CNN
F 1 "Conn_01x06" V 775 1612 50  0001 R CNN
F 2 "RRAT Consolidated:Pin_Header_Straight_1x06_Pitch2.54mm" H 900 2000 50  0001 C CNN
F 3 "~" H 900 2000 50  0001 C CNN
	1    900  2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	1100 2100 1300 2100
Wire Wire Line
	1600 2100 1700 2100
Wire Wire Line
	1700 2100 1700 2200
Wire Wire Line
	1100 2200 1700 2200
Connection ~ 1700 2200
Wire Wire Line
	1700 2200 1700 2350
Wire Wire Line
	1100 2000 1900 2000
Wire Wire Line
	1100 1900 1300 1900
Wire Wire Line
	1600 1900 1800 1900
Wire Wire Line
	1100 1800 1300 1800
Wire Wire Line
	1600 1800 1800 1800
Wire Wire Line
	1100 1700 1200 1700
Wire Wire Line
	1200 1700 1200 1550
Wire Wire Line
	1200 1550 1300 1550
Wire Wire Line
	1600 1550 1700 1550
Wire Wire Line
	1700 1400 1700 1550
Connection ~ 1700 1550
Wire Wire Line
	1700 1550 1800 1550
$Comp
L power:VCC #PWR0102
U 1 1 5D683E7D
P 1700 950
F 0 "#PWR0102" H 1700 800 50  0001 C CNN
F 1 "VCC" H 1717 1123 50  0000 C CNN
F 2 "" H 1700 950 50  0001 C CNN
F 3 "" H 1700 950 50  0001 C CNN
	1    1700 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 950  1700 1100
Wire Wire Line
	2800 5350 3050 5350
Wire Wire Line
	3400 1600 3300 1600
Wire Wire Line
	3400 1700 3300 1700
Wire Notes Line
	6100 750  6100 2900
Wire Wire Line
	5000 1700 5000 1200
Wire Wire Line
	5000 1200 5200 1200
Wire Wire Line
	5400 1200 5600 1200
Wire Wire Line
	5600 1200 5600 1700
Wire Wire Line
	5000 1050 5000 1200
Connection ~ 5000 1200
Wire Wire Line
	5600 1050 5600 1200
Connection ~ 5600 1200
Wire Wire Line
	5000 2000 5000 2100
Wire Wire Line
	5000 2100 5300 2100
Wire Wire Line
	5600 2100 5600 2000
Wire Wire Line
	5300 2200 5300 2100
Connection ~ 5300 2100
Wire Wire Line
	5300 2100 5600 2100
$Comp
L power:VCC #PWR0103
U 1 1 5D8AAF5C
P 10050 1075
F 0 "#PWR0103" H 10050 925 50  0001 C CNN
F 1 "VCC" H 10067 1248 50  0000 C CNN
F 2 "" H 10050 1075 50  0001 C CNN
F 3 "" H 10050 1075 50  0001 C CNN
	1    10050 1075
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 1075 10050 1175
Wire Wire Line
	10050 1175 10550 1175
Wire Wire Line
	10550 1175 10550 1275
Connection ~ 10050 1175
Wire Wire Line
	10050 1175 10050 1275
Wire Wire Line
	10050 1575 10050 1675
Wire Wire Line
	10050 1675 10550 1675
Wire Wire Line
	10550 1675 10550 1575
Connection ~ 10050 1675
Wire Wire Line
	10050 1675 10050 1775
$Comp
L power:VCC #PWR0104
U 1 1 5D8E06B8
P 7500 1000
F 0 "#PWR0104" H 7500 850 50  0001 C CNN
F 1 "VCC" H 7517 1173 50  0000 C CNN
F 2 "" H 7500 1000 50  0001 C CNN
F 3 "" H 7500 1000 50  0001 C CNN
	1    7500 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1000 7500 1100
Wire Wire Line
	7500 1100 7600 1100
Wire Wire Line
	7000 1400 7600 1400
Wire Wire Line
	7000 1500 7600 1500
Wire Wire Line
	7000 1600 7600 1600
Wire Wire Line
	7000 1700 7600 1700
$Comp
L RRAT_consolidated:RFM26 U1
U 1 1 5BA609EE
P 8100 1600
F 0 "U1" H 8100 2386 59  0000 C CNN
F 1 "RFM26" H 8100 2281 59  0000 C CNN
F 2 "RRAT Consolidated:RFM26" H 8100 1600 50  0001 C CNN
F 3 "" H 8100 1600 50  0001 C CNN
	1    8100 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 2000 7500 2000
Wire Wire Line
	7500 2000 7500 2200
Wire Wire Line
	7600 2200 7500 2200
Connection ~ 7500 2200
Wire Wire Line
	7500 2200 7500 2350
Wire Wire Line
	8600 1100 9150 1100
Wire Wire Line
	8600 1450 8900 1450
Wire Wire Line
	8900 1450 8900 1950
Wire Wire Line
	8900 1950 8600 1950
Wire Wire Line
	8600 1600 8750 1600
Wire Wire Line
	8750 1600 8750 2050
Wire Wire Line
	8750 2050 8600 2050
NoConn ~ 8600 2150
NoConn ~ 8600 2250
Wire Wire Line
	11350 750  11450 750 
Wire Wire Line
	11450 750  11450 850 
Wire Wire Line
	11450 1150 11450 1250
Wire Wire Line
	11350 1650 11450 1650
Wire Wire Line
	11450 1650 11450 1750
Wire Wire Line
	12600 750  12700 750 
Wire Wire Line
	12700 750  12700 850 
Wire Wire Line
	12700 1150 12700 1250
Wire Wire Line
	12600 1650 12700 1650
Wire Wire Line
	12700 1650 12700 1750
Wire Wire Line
	12700 2050 12700 2150
Text Notes 10400 2600 0    50   ~ 0
Caps C5, C6, C7, C8, C9 and C10 should\nbe placed as close to the pins as possible\nand have a via to ground as close as possible.
$Comp
L power:GND #PWR0105
U 1 1 5CF0E5E4
P 14575 5275
F 0 "#PWR0105" H 14575 5025 50  0001 C CNN
F 1 "GND" H 14580 5102 50  0000 C CNN
F 2 "" H 14575 5275 50  0001 C CNN
F 3 "" H 14575 5275 50  0001 C CNN
	1    14575 5275
	1    0    0    -1  
$EndComp
Wire Wire Line
	14575 5275 14575 5200
Wire Wire Line
	14575 5200 14650 5200
$Comp
L power:VCC #PWR0106
U 1 1 5CF183FE
P 14275 5250
F 0 "#PWR0106" H 14275 5100 50  0001 C CNN
F 1 "VCC" H 14292 5423 50  0000 C CNN
F 2 "" H 14275 5250 50  0001 C CNN
F 3 "" H 14275 5250 50  0001 C CNN
	1    14275 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	14275 5250 14275 5300
Wire Wire Line
	14275 5300 14425 5300
Wire Wire Line
	14425 5300 14425 5100
Wire Wire Line
	14425 5100 14650 5100
Wire Wire Line
	8250 6500 8250 6400
Wire Wire Line
	8500 6100 8250 6100
Connection ~ 8250 6100
Wire Wire Line
	8250 6100 8250 6000
Wire Wire Line
	8500 6300 8250 6300
Connection ~ 8250 6300
Wire Wire Line
	8250 6300 8250 6100
Wire Wire Line
	8500 6400 8250 6400
Connection ~ 8250 6400
Wire Wire Line
	8250 6400 8250 6300
Wire Wire Line
	8250 5700 8250 5600
Wire Wire Line
	8250 5600 8500 5600
Wire Wire Line
	8500 5200 8400 5200
Wire Wire Line
	8400 5200 8400 5300
Wire Wire Line
	8400 5300 8500 5300
Wire Wire Line
	7600 5500 7700 5500
$Comp
L power:VCC #PWR0107
U 1 1 5D05ECA3
P 7200 5050
F 0 "#PWR0107" H 7200 4900 50  0001 C CNN
F 1 "VCC" H 7217 5223 50  0000 C CNN
F 2 "" H 7200 5050 50  0001 C CNN
F 3 "" H 7200 5050 50  0001 C CNN
	1    7200 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5050 7200 5200
Connection ~ 8400 5200
Wire Wire Line
	7300 5500 7200 5500
Wire Wire Line
	7200 5500 7200 5200
Connection ~ 7200 5200
Wire Wire Line
	7200 5700 7200 5500
Connection ~ 7200 5500
Wire Wire Line
	7700 5700 7700 5500
Connection ~ 7700 5500
Wire Wire Line
	7700 5500 8500 5500
Wire Wire Line
	7200 6000 7200 6250
Wire Wire Line
	7700 6000 7700 6250
Wire Wire Line
	7700 6250 7200 6250
Connection ~ 7200 6250
Wire Wire Line
	7200 6250 7200 6500
Text Notes 6900 7050 0    50   ~ 0
Caps C2, C3 and C4 should be placed\nas close to the pins as possible and have\na via to ground as close as possible.
$Comp
L RRAT_consolidated:C C3
U 1 1 5D0DBC2B
P 7700 5850
F 0 "C3" H 7815 5896 50  0000 L CNN
F 1 "100nF" H 7815 5805 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 7738 5700 50  0001 C CNN
F 3 "~" H 7700 5850 50  0001 C CNN
	1    7700 5850
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:C C2
U 1 1 5D0E5FCA
P 7200 5850
F 0 "C2" H 7315 5896 50  0000 L CNN
F 1 "100nF" H 7315 5805 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 7238 5700 50  0001 C CNN
F 3 "~" H 7200 5850 50  0001 C CNN
	1    7200 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 4700 8500 4700
Wire Wire Line
	8150 4900 8500 4900
Wire Wire Line
	8150 4100 8500 4100
Wire Wire Line
	2200 2000 2300 2000
Wire Wire Line
	2300 2000 2300 1900
$Comp
L power:VCC #PWR0108
U 1 1 5D12FBC3
P 2300 1900
F 0 "#PWR0108" H 2300 1750 50  0001 C CNN
F 1 "VCC" H 2317 2073 50  0000 C CNN
F 2 "" H 2300 1900 50  0001 C CNN
F 3 "" H 2300 1900 50  0001 C CNN
	1    2300 1900
	1    0    0    -1  
$EndComp
NoConn ~ 10900 4100
NoConn ~ 10900 4500
NoConn ~ 10900 4600
NoConn ~ 10900 5900
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D1CB8FB
P 3850 6900
F 0 "#FLG0101" H 3850 6975 50  0001 C CNN
F 1 "PWR_FLAG" H 3850 7074 50  0000 C CNN
F 2 "" H 3850 6900 50  0001 C CNN
F 3 "~" H 3850 6900 50  0001 C CNN
	1    3850 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 6900 3850 7050
$Comp
L power:GND #PWR0109
U 1 1 5D1D5C5D
P 1350 6700
F 0 "#PWR0109" H 1350 6450 50  0001 C CNN
F 1 "GND" H 1355 6527 50  0000 C CNN
F 2 "" H 1350 6700 50  0001 C CNN
F 3 "" H 1350 6700 50  0001 C CNN
	1    1350 6700
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5D1D5D58
P 1350 6450
F 0 "#FLG0102" H 1350 6525 50  0001 C CNN
F 1 "PWR_FLAG" H 1350 6624 50  0000 C CNN
F 2 "" H 1350 6450 50  0001 C CNN
F 3 "~" H 1350 6450 50  0001 C CNN
	1    1350 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 6450 1350 6550
Wire Wire Line
	3900 1800 4000 1800
Wire Wire Line
	4000 1800 4000 1900
$Comp
L RRAT_consolidated:MIC9409x U2
U 1 1 5D240996
P 2750 6550
F 0 "U2" H 2750 6965 50  0000 C CNN
F 1 "MIC94092YC6" H 2750 6874 50  0000 C CNN
F 2 "sc-70-6:SOT-363_SC-70-6" H 2950 5800 50  0001 C CNN
F 3 "" H 2950 5800 50  0001 C CNN
	1    2750 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 5D24B44E
P 3400 6650
F 0 "#PWR0110" H 3400 6400 50  0001 C CNN
F 1 "GND" H 3405 6477 50  0000 C CNN
F 2 "" H 3400 6650 50  0001 C CNN
F 3 "" H 3400 6650 50  0001 C CNN
	1    3400 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 6550 3400 6650
Wire Wire Line
	2350 6550 1350 6550
Connection ~ 1350 6550
Wire Wire Line
	1350 6550 1350 6700
Wire Wire Line
	1700 6400 1700 6250
$Comp
L power:VCC #PWR0111
U 1 1 5D295E62
P 1700 6250
F 0 "#PWR0111" H 1700 6100 50  0001 C CNN
F 1 "VCC" H 1717 6423 50  0000 C CNN
F 2 "" H 1700 6250 50  0001 C CNN
F 3 "" H 1700 6250 50  0001 C CNN
	1    1700 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 6550 3150 6550
Wire Wire Line
	3150 6400 3400 6400
Text Label 3400 6400 0    50   ~ 0
~SHUTDOWN
Wire Wire Line
	3150 6700 3250 6700
Wire Wire Line
	3250 6700 3250 7050
Wire Wire Line
	3250 7050 3850 7050
Wire Wire Line
	4200 7050 4200 6800
$Comp
L power:+3V3 #PWR0112
U 1 1 5D2C1F13
P 4200 6800
F 0 "#PWR0112" H 4200 6650 50  0001 C CNN
F 1 "+3V3" H 4215 6973 50  0000 C CNN
F 2 "" H 4200 6800 50  0001 C CNN
F 3 "" H 4200 6800 50  0001 C CNN
	1    4200 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3400 1800 3400
Connection ~ 3850 7050
Wire Wire Line
	3850 7050 4200 7050
Wire Wire Line
	7200 5200 8400 5200
Text Label 3250 3900 0    50   ~ 0
~SHUTDOWN
Wire Wire Line
	1700 6400 2350 6400
Wire Wire Line
	2300 3900 3250 3900
Wire Wire Line
	11450 2050 11450 2150
Wire Wire Line
	2300 4300 2600 4300
Connection ~ 2600 4300
Wire Wire Line
	2600 4300 2600 4800
$Comp
L power:GND #PWR0113
U 1 1 5D3995CD
P 7500 2350
F 0 "#PWR0113" H 7500 2100 50  0001 C CNN
F 1 "GND" H 7505 2177 50  0000 C CNN
F 2 "" H 7500 2350 50  0001 C CNN
F 3 "" H 7500 2350 50  0001 C CNN
	1    7500 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5D399B1C
P 11450 2150
F 0 "#PWR0115" H 11450 1900 50  0001 C CNN
F 1 "GND" H 11455 1977 50  0000 C CNN
F 2 "" H 11450 2150 50  0001 C CNN
F 3 "" H 11450 2150 50  0001 C CNN
	1    11450 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5D399C55
P 12700 2150
F 0 "#PWR0114" H 12700 1900 50  0001 C CNN
F 1 "GND" H 12705 1977 50  0000 C CNN
F 2 "" H 12700 2150 50  0001 C CNN
F 3 "" H 12700 2150 50  0001 C CNN
	1    12700 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5D3A5383
P 12700 1250
F 0 "#PWR0116" H 12700 1000 50  0001 C CNN
F 1 "GND" H 12705 1077 50  0000 C CNN
F 2 "" H 12700 1250 50  0001 C CNN
F 3 "" H 12700 1250 50  0001 C CNN
	1    12700 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5D3B0AB1
P 11450 1250
F 0 "#PWR0117" H 11450 1000 50  0001 C CNN
F 1 "GND" H 11455 1077 50  0000 C CNN
F 2 "" H 11450 1250 50  0001 C CNN
F 3 "" H 11450 1250 50  0001 C CNN
	1    11450 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5D3BC437
P 1700 2350
F 0 "#PWR0118" H 1700 2100 50  0001 C CNN
F 1 "GND" H 1705 2177 50  0000 C CNN
F 2 "" H 1700 2350 50  0001 C CNN
F 3 "" H 1700 2350 50  0001 C CNN
	1    1700 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5D3BC491
P 4000 1900
F 0 "#PWR0119" H 4000 1650 50  0001 C CNN
F 1 "GND" H 4005 1727 50  0000 C CNN
F 2 "" H 4000 1900 50  0001 C CNN
F 3 "" H 4000 1900 50  0001 C CNN
	1    4000 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 5D3C7D38
P 1650 5350
F 0 "#PWR0120" H 1650 5100 50  0001 C CNN
F 1 "GND" H 1655 5177 50  0000 C CNN
F 2 "" H 1650 5350 50  0001 C CNN
F 3 "" H 1650 5350 50  0001 C CNN
	1    1650 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5D3C7F1F
P 2600 5050
F 0 "#PWR0121" H 2600 4800 50  0001 C CNN
F 1 "GND" H 2605 4877 50  0000 C CNN
F 2 "" H 2600 5050 50  0001 C CNN
F 3 "" H 2600 5050 50  0001 C CNN
	1    2600 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5D3DF00D
P 7200 6500
F 0 "#PWR0122" H 7200 6250 50  0001 C CNN
F 1 "GND" H 7205 6327 50  0000 C CNN
F 2 "" H 7200 6500 50  0001 C CNN
F 3 "" H 7200 6500 50  0001 C CNN
	1    7200 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5D3DF067
P 8250 6500
F 0 "#PWR0123" H 8250 6250 50  0001 C CNN
F 1 "GND" H 8255 6327 50  0000 C CNN
F 2 "" H 8250 6500 50  0001 C CNN
F 3 "" H 8250 6500 50  0001 C CNN
	1    8250 6500
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:C C13
U 1 1 5D3EAEAB
P 2050 7600
F 0 "C13" H 2165 7646 50  0000 L CNN
F 1 "0nF" H 2165 7555 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 2088 7450 50  0001 C CNN
F 3 "~" H 2050 7600 50  0001 C CNN
	1    2050 7600
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR01
U 1 1 5D3F66CC
P 2050 7350
F 0 "#PWR01" H 2050 7200 50  0001 C CNN
F 1 "VCC" H 2067 7523 50  0000 C CNN
F 2 "" H 2050 7350 50  0001 C CNN
F 3 "" H 2050 7350 50  0001 C CNN
	1    2050 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 7350 2050 7450
$Comp
L power:GND #PWR02
U 1 1 5D40203D
P 2050 7850
F 0 "#PWR02" H 2050 7600 50  0001 C CNN
F 1 "GND" H 2055 7677 50  0000 C CNN
F 2 "" H 2050 7850 50  0001 C CNN
F 3 "" H 2050 7850 50  0001 C CNN
	1    2050 7850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 7750 2050 7850
$Comp
L RRAT_consolidated:C C14
U 1 1 5D430695
P 2800 7600
F 0 "C14" H 2915 7646 50  0000 L CNN
F 1 "100nF" H 2915 7555 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 2838 7450 50  0001 C CNN
F 3 "~" H 2800 7600 50  0001 C CNN
	1    2800 7600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D453252
P 2800 7850
F 0 "#PWR04" H 2800 7600 50  0001 C CNN
F 1 "GND" H 2805 7677 50  0000 C CNN
F 2 "" H 2800 7850 50  0001 C CNN
F 3 "" H 2800 7850 50  0001 C CNN
	1    2800 7850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 7750 2800 7850
$Comp
L power:+3V3 #PWR03
U 1 1 5D45ED58
P 2800 7350
F 0 "#PWR03" H 2800 7200 50  0001 C CNN
F 1 "+3V3" H 2815 7523 50  0000 C CNN
F 2 "" H 2800 7350 50  0001 C CNN
F 3 "" H 2800 7350 50  0001 C CNN
	1    2800 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 7350 2800 7450
Text Notes 1900 8500 0    50   ~ 0
Caps C13* and C14 should be placed\nas close to the pins as possible and have\na via to ground as close as possible.\n\n*C13 should not be fitted.
$Comp
L RRAT_consolidated:C C8
U 1 1 5D476DFB
P 11450 1900
F 0 "C8" H 11565 1946 50  0000 L CNN
F 1 "47pF" H 11565 1855 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 11488 1750 50  0001 C CNN
F 3 "~" H 11450 1900 50  0001 C CNN
	1    11450 1900
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:C C9
U 1 1 5D482968
P 12700 1000
F 0 "C9" H 12815 1046 50  0000 L CNN
F 1 "47pF" H 12815 955 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 12738 850 50  0001 C CNN
F 3 "~" H 12700 1000 50  0001 C CNN
	1    12700 1000
	1    0    0    -1  
$EndComp
$Comp
L RRAT_consolidated:C C10
U 1 1 5D48E4D3
P 12700 1900
F 0 "C10" H 12815 1946 50  0000 L CNN
F 1 "47pF" H 12815 1855 50  0000 L CNN
F 2 "RRAT Consolidated:C0603" H 12738 1750 50  0001 C CNN
F 3 "~" H 12700 1900 50  0001 C CNN
	1    12700 1900
	1    0    0    -1  
$EndComp
Text Notes 4650 2800 0    50   ~ 0
NOTE:\nSpecial considerations on placement\nand keepouts.\n\nSee existing designs.
Wire Wire Line
	7000 1300 7600 1300
Wire Wire Line
	11650 6000 11400 6000
Wire Wire Line
	11100 6000 10900 6000
Text Notes 12150 6000 0    50   ~ 0
Not sure R4 or R9 are necessary.\n1) They are on board connections\n2) The rest of the RFM26 pins do not have resistors.
Wire Wire Line
	10900 5600 11100 5600
Wire Wire Line
	11400 5600 11650 5600
Wire Wire Line
	7600 1900 7000 1900
$EndSCHEMATC
