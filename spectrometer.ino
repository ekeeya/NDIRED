
#include "SparkFun_AS7265X.h" 
AS7265X sensor;

#include <Wire.h>

void setup() {
  Serial.begin(115200); // according to docs serial listens at 115200 not 9600 baund rate
  Serial.println("Spectroscopy sensor");

  Serial.println("Point sensor to target and press any key");
  
  while(Serial.available() == false) {} //Do nothing while we wait for user to press a key to simulate a button
  
  Serial.read(); //Throw away pressed button

  if(sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while(1);
  }

  sensor.disableIndicator(); //Turn off the blue status LED for accuracy
  Serial.println("A,B,C,D,E,F,G,H,I,J,K,L,R,S,T,U,V,W");
  
}
void sonsorRead(){
    sensor.takeMeasurementsWithBulb(); 
    Serial.print(sensor.getCalibratedA());
    Serial.print(",");
    Serial.print(sensor.getCalibratedB());
    Serial.print(",");
    Serial.print(sensor.getCalibratedC());
    Serial.print(",");
    Serial.print(sensor.getCalibratedD());
    Serial.print(",");
    Serial.print(sensor.getCalibratedE());
    Serial.print(",");
    Serial.print(sensor.getCalibratedF());
    // Read more 12 channels 
    sensor.softReset();
    
 }

int count = 0;
void loop() {
  delay(250);
  count+=250;
    if (count==1000){
      sonsorRead();
  }
  
}
