# Aquacheck_SDI12_Soil_moisture
Aquacheck SDI12 Soil moisture sensor | Logger | Parser

The examples are provided to demonstrate how easy it is to communicate with Aquacheck soil moisture probes. 

The examples are based on [EnviroDIY](https://github.com/EnviroDIY/Arduino-SDI-12) library. You have to install [EnviroDIY](https://github.com/EnviroDIY/Arduino-SDI-12) library before using these examples. 


#### If you are using SoftwareSerial in your project, read below:
Since the library has conflicts with SoftwareSerial library, some workarounds are provided in this [topic](https://github.com/EnviroDIY/Arduino-SDI-12/issues/8). Based on that, I made a clone of SoftwareSerial library that you can easily install next to original SoftwareSerial library. Although, you have to modify PCINT Request Vectors based on your request. For my work, data pin defined as D13, no change is required. To know mapping of PCINT Request Vectors, refer to [this page](http://gammon.com.au/interrupts) or have a look at following quick-hint.


* D0 to D7 ::: PCINT2_vect
* D8 to D13 ::: PCINT0_vect
* A0 to A5 ::: PCINT1_vect





