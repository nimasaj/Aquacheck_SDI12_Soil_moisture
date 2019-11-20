# Aquacheck SDI12 Soil moisture
Aquacheck SDI12 Soil moisture sensor | Logger | Parser

The examples are provided to demonstrate how easy it is to communicate with Aquacheck soil moisture probes. 

The examples are based on [EnviroDIY](https://github.com/EnviroDIY/Arduino-SDI-12) library. You have to install [EnviroDIY](https://github.com/EnviroDIY/Arduino-SDI-12) library before using these examples. 
Looking for more examples? Head over to the [library repository](https://github.com/EnviroDIY/Arduino-SDI-12).

A copy of a EnviroDIY library is also provided [here](https://github.com/nimasaj/Aquacheck_SDI12_Soil_moisture/tree/master/EnviroDIY/src), as a backup.

#### If you are using SoftwareSerial in your project, read below:
Since the library has conflicts with SoftwareSerial library, some workarounds are provided in this [topic](https://github.com/EnviroDIY/Arduino-SDI-12/issues/8). Based on that, I made a clone of SoftwareSerial library that you can easily install next to original SoftwareSerial library. Although, you have to modify PCINT Request Vectors in both SoftwareSerial library and SDI-12 library based on your request. For my work, data pin defined as D13 and SoftwareSerial pins as D5 & D6, no change is required. To know mapping of PCINT Request Vectors, refer to [this page](http://gammon.com.au/interrupts) or have a look at following quick-hint.


* D0 to D7 ::: PCINT2_vect
* D8 to D13 ::: PCINT0_vect
* A0 to A5 ::: PCINT1_vect

For ATMEGA328P, in "PCICR – Pin Change Interrupt Control Register" section, datasheet page 56. Then, finding mapping of PCINTxx pins with pinout of MCU, datasheet page 3, and Arduino.



