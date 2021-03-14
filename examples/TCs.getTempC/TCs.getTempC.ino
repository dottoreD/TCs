// example how to use TCs.getTemp(float Val, float Val, char Val);
// hotJunctionVoltage is in mV
// ColdJunctionTemp is in °C
// ThermocoupleType is simply by respective Char

#include <TCs.h> 

TCs myTCs;    // create instance for TCs

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.println();
    delay(10);  // make sure print has ended

  float hotJunctionVoltage;
  int _mVmin = -11;
  int _mVmax = 76;
  char TcType [] = {'B', 'E', 'J', 'K', 'N', 'R', 'S', 'T'}; 
  float ColdJunction [] = { -10.0 , 0.0 , 10.0 , 20.0 , 30.0 };

 Serial.print ("[mV]");                   // creates table with all Thermocouple Types, 0°C coldJunctionTemp and increasing hotJunctionVoltage
 Serial.print ("\t\t");
  for (int i=0; i<=7; i++){
    Serial.print ( TcType [i]);
    Serial.print ("\t\t");
  }
    Serial.println ();
  
  for (hotJunctionVoltage = _mVmin; hotJunctionVoltage < _mVmax; hotJunctionVoltage ++) {
      Serial.print (hotJunctionVoltage, 1);
      Serial.print ("\t\t");
    for (int i=0; i<=7; i++){
      Serial.print (myTCs.getTemp_C (hotJunctionVoltage, ColdJunction [1], TcType [i]));
      Serial.print ("\t\t");
    }
  Serial.println ();
  }

  Serial.println ();


  Serial.print ("[mV]");                   // creates table for Thermocouple Type 'K', 5 coldJunctionTemps and increasing hotJunctionVoltage
  Serial.print ("\t\t");
   for (int i=0; i<=4; i++){
      Serial.print ( ColdJunction [i], 1);
      Serial.print ( " °C");
      Serial.print ("\t\t");
    }
      Serial.println ();
    
    for (hotJunctionVoltage = _mVmin; hotJunctionVoltage < _mVmax; hotJunctionVoltage ++) {
      Serial.print (hotJunctionVoltage, 1);
      Serial.print ("\t\t");
     for (int i=0; i<=4; i++){
        Serial.print (myTCs.getTemp_C (hotJunctionVoltage, ColdJunction [i], TcType [3]));
        Serial.print ("\t\t");
     }
    Serial.println ();
    }
}


void loop() {
  // put your main code here, to run repeatedly:

}
