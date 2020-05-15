/*
It is written by Nima Sajedi on 02May2019, based on EnviroDIY-SDI12 library @ https://github.com/EnviroDIY/Arduino-SDI-12
This code is downloaded from https://github.com/nimasaj/Aquacheck_SDI12_Soil_moisture
*/

#define MAX(x,y) ((x) >= (y)) ? (x) : (y)
#define MIN(x,y) ((x) <= (y)) ? (x) : (y)

#include <SDI12.h>
#include <SoftwareSerialSoil.h> 

#define DATA_PIN 13          // Aquacheck probe data pin
boolean debug = true;
SDI12 mySDI12(DATA_PIN);

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
  int8_t sm[6]; 
  // -'-'-'-'-MEASUREMENT COMMAND-'-'-'-'-
  SDICommand(cmd3); //0M! |  Start a measurement on Soil Moisture
  delay(delay_t);
  
  //SDICommand(cmd4); //0M0! | Start a measurement on Soil Moisture
  //delay(delay_t);

  //SDICommand(cmd5); //0M1! | Start a measurement on Temperature
  //delay(delay_t);

  // -'-'-'-'-'-'-DATA COMMAND-'-'-'-'-'-'- // Reading data

  String valA=SDICommand(cmd6);  //0D0! | Read measured values
  delay(50);

  String valB=SDICommand(cmd7);  //0D1! | Read measured values
  delay(10);

  SDIparser(valA, sm[0],sm[1],sm[2]);
  SDIparser(valB, sm[3],sm[4],sm[5]);

  for (uint8_t n=0;n<6;n++){
    if (sm[n]<0){
      sm[n]=0;
    }
  }

  if(debug){
    Serial.println(sm[0]);
    Serial.println(sm[1]);
    Serial.println(sm[2]);
    Serial.println(sm[3]);
    Serial.println("-----\n");
    
  }
  delay(20*1000);
}


String SDIgetData(){
  String data = "";
  char output;

  while (!mySDI12.available()){
     //blink();
  }

  while(mySDI12.available()){
    output = mySDI12.read();
    if (output!=0x0A){ ///// Ignore new line feed (<lf>) in responses
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


int8_t SDIparser(String str, int8_t &v0, int8_t &v1, int8_t &v2){
  boolean SDIdebug = false;
  String plus="+", minus="-", dot=".";
  uint8_t mn=3; // number of values in each message
  int8_t sp[mn],sm[mn],s[mn],d[mn],parts[mn];
  
  sp[0]=str.indexOf(plus);
  sm[0]=str.indexOf(minus);
  d[0]=str.indexOf(dot);
  
  if (sm[0]<0){
    s[0]=sp[0];
  }
  else if (sp[0]<0){
    s[0]=sm[0];
  }
  else{
    s[0]=MIN(sm[0],sp[0]);
  }  

  for (uint8_t n=1; n<mn;n++){
    sp[n]=str.indexOf(plus,s[n-1]+1);
    sm[n]=str.indexOf(minus,s[n-1]+1);
    d[n]=str.indexOf(dot,d[n-1]+1);  

    if (sm[n]<0){
      s[n]=sp[n];
    }
    else if (sp[n]<0){
      s[n]=sm[n];
    }
    else{
      s[n]=MIN(sm[n],sp[n]);
    }  
  }

  
  if (SDIdebug){
    Serial.print("value: ");
    Serial.print(str);
    Serial.print("\tLen: ");
    Serial.println(str.length());
    for (uint8_t m=0;m<mn;m++){
      Serial.print("sp");
      Serial.print(m);
      Serial.print(": ");
      Serial.print(sp[m]);
      Serial.print("\t\t");
    }
    Serial.println("");  
    for (uint8_t m=0;m<mn;m++){
      Serial.print("sm");
      Serial.print(m);
      Serial.print(": ");
      Serial.print(sm[m]);
      Serial.print("\t\t");
    }
    Serial.println(""); 
    for (uint8_t m=0;m<mn;m++){
      Serial.print("d");
      Serial.print(m);
      Serial.print(": ");
      Serial.print(d[m]);
      Serial.print("\t\t");
    }    
    Serial.println("");  
    for (uint8_t m=0;m<mn;m++){
      Serial.print("s");
      Serial.print(m);
      Serial.print(": ");
      Serial.print(s[m]);
      Serial.print("\t\t");
    }
    Serial.println("");      
  }


  if (SDIdebug){
    Serial.println("\n");
  }

  for (uint8_t m=0;m<mn;m++){
    parts[m]=(str.substring(s[m],d[m])).toInt();
    if (SDIdebug){
      Serial.println(parts[m]);
    }
  }
  
  if (SDIdebug){
    Serial.println("\n");
  }
  //It's also possible to return the values in a vector.
  v0=parts[0];
  v1=parts[1];
  v2=parts[2];
}
