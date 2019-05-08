/*
It is written by Nima Sajedi on 02May2019, based on EnviroDIY-SDI12 library @ https://github.com/EnviroDIY/Arduino-SDI-12
This parser is downloaded from https://github.com/nimasaj/Aquacheck_SDI12_Soil_moisture
*/

#define MAX(x,y) ((x) >= (y)) ? (x) : (y)
#define MIN(x,y) ((x) <= (y)) ? (x) : (y)


//const int8_t min_val=-4; // the minimum SFU the sensor will return
//const uint8_t max_val=120; // the maximum SFU the sensor will return
//int8_t parts[3]; //uncomment if you want to have this array defined globally

int8_t SDIparser(String str, int8_t &v0, int8_t &v1, int8_t &v2){
  boolean SDIdebug = true; // if you do not want to see debug data, change it to false.
  String plus="+", minus="-", dot=".";
  uint8_t mn=3; // Max. number of sensor values in each message
  int8_t sp[mn],sm[mn],s[mn],d[mn],parts[mn];
  //int8_t sp[mn],sm[mn],s[mn],d[mn]; // if you defined array parts[] globally, uncomment this line and comment out above line.
  
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

  for (uint8_t n=1; n<3;n++){
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
      Serial.print("s");
      Serial.print(m);
      Serial.print(": ");
      Serial.print(s[m]);
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
  //return(parts);  
  // Since in C and Arduino it is not possible to return arrays in
  // functions, I had to do it in this way. https://forum.arduino.cc/index.php?topic=42934.0
  // The other way would be defining array "parts" globally. Therefore, you ccould access it
  // directly in Loop();
  v0=parts[0];
  v1=parts[1];
  v2=parts[2];
  
}


void setup() {
  Serial.begin(9600);
  delay(500); 
  Serial.println("Hello parser!");

}

void loop() {
  int8_t readings[3];  
  String valA;
  //valA="00+057.0281+098.3593+098.1937";
  //valA="00-000.9781+000.0000+048.5187";
  valA="00-001.0031+000.0250+048.2125";
  
  String valB="0+098.4437";
  //valA=valB;


  SDIparser(valA, readings[0],readings[1],readings[2]);

  /*Serial.println(readings[0]);
  Serial.println(readings[1]);
  Serial.println(readings[2]);
  Serial.println("-----");*/
        
  delay(2*5000);
    
}
