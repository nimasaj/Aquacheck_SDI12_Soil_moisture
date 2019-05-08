/*
It is written by Nima Sajedi on 02May2019, based on EnviroDIY-SDI12 library @ https://github.com/EnviroDIY/Arduino-SDI-12
This code is downloaded from https://github.com/nimasaj/Aquacheck_SDI12_Soil_moisture

Make sure AquaCheck probe is powered up before running this code.
Aquacheck probes can run from 3.3 up tp 12V. However, those are not stable on 3.3V. 
So it is better to power them up on a higher voltage. Maybe 3.6V or 5V if you are interfacing with Arduino.
*/

#include <SDI12.h>
#define DATA_PIN 13 //data pin

SDI12 mySDI12(DATA_PIN);
boolean debug = true;


String cmd1="0I!"; //ID - 013AquaChckACHSDI042S211658
String cmd2="0X#!"; //Config - 0#04L04

String cmd3="0M!"; //Start a measurement on Soil Moisture
String cmd4="0M0!"; //Start a measurement on Soil Moisture | same as 0M!
String cmd5="0M1!"; //Start a measurement on Temperature

String cmd6="0D0!"; // Return measured values for 1st 3 sensors | 00+057.0281+098.3593+098.1937
String cmd7="0D1!"; // Return measured values for 2nd 3 sensors | 0+098.4437

String cmd8="0C1!"; //Same as M | for probes with more than 9 sensors
String cmd9="0C0!";  //Same as M | for probes with more than 9 sensors
//String cmd10="0R0!";  //

uint16_t delay_t=2500;

void setup() {
  if (debug){
    Serial.begin(9600);
  }
  mySDI12.begin();
  delay(500); 
  if (debug){
    Serial.println("Hello there!");
    // -'-'-'-'-'-'-INFO COMMAND-'-'-'-'-'-'-
    SDICommand(cmd1);  //"0I!" | ID - 013AquaChckACHSDI042S211658
    delay(delay_t);
    SDICommand(cmd2);  //"0X#!" | Config - 0#04L04
    delay(delay_t);  
    //SDICommand(cmd8);  //"0C1!" | Same as M - Read Temperature values
    //delay(delay_t);     
  }
}

void loop()
{
  // -'-'-'-'-MEASUREMENT COMMAND-'-'-'-'-
  SDICommand(cmd3); //0M! |  Start a measurement on Soil Moisture
  delay(delay_t);
  
  //SDICommand(cmd4); //0M0! | Start a measurement on Soil Moisture
  //delay(delay_t);

  //SDICommand(cmd5); //0M1! | Start a measurement on Temperature
  //delay(delay_t);
  
  // -'-'-'-'-'-'-DATA COMMAND-'-'-'-'-'-'- // Reading data
  SDICommand(cmd6);  //0D0! | Read measured values
  delay(delay_t);

  SDICommand(cmd7);  //0D1! | Read measured values
  delay(delay_t);

  Serial.println("");

  delay(10*1000);
}

String SDIgetData(){
  String data = "";
  char output;

  while (!mySDI12.available()){
     //blink();
  }

  while(mySDI12.available()){
    output = mySDI12.read();
    if (output!=0x0A){ ///// Ignore <lf> new line feed in responses
      data += output;      
    }
    delay(10);
  }  
  return data; 
}

String SDICommand(String cmd){
  mySDI12.sendCommand(cmd);
  String ret=SDIgetData();
  if (debug){
    Serial.print("Response of "+cmd+" : ");
    Serial.println(ret);
  }
  //delay(2*500);
  mySDI12.flush();
  return ret;
}
