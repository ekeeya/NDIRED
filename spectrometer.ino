// include the library code:
#include <LiquidCrystal.h>
#include "SparkFun_AS7265X.h" 
#include "Sim800L.h"
#include <Wire.h> //for I2C

double determineEthanolContent(double sensorValue);
boolean isDrunk(double ethanolContent);
void sendSMS(char* msg);
void lcdPrint(char data[]);
void deviceReset();


AS7265X sensor;

// lcd instance has to be global so its aavailable to every function
const int rs = 4, en = 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void lcdPrint (char data[]){
  lcd.clear();
  lcd.print(data);
  lcd.display();
  }

// C's wiered array return function
double * sensorRead(){
  sensor.takeMeasurementsWithBulb(); //This is a hard wait while all 18 channels are measured
  double channel0 = sensor.getCalibratedA();
  double channel1 = sensor.getCalibratedB();
  double channel2 = sensor.getCalibratedC();
  double channel3 = sensor.getCalibratedD();
  double channel4 = sensor.getCalibratedE();
  double channel5 = sensor.getCalibratedF();
  
  double channel6 = sensor.getCalibratedG();
  double channel7 = sensor.getCalibratedH();
  double channel8 = sensor.getCalibratedI();
  double channel9 = sensor.getCalibratedJ();
  double channel10 = sensor.getCalibratedK();
  double channel11 = sensor.getCalibratedL();

  double channel12 = sensor.getCalibratedR();
  double channel13 = sensor.getCalibratedS();
  double channel14 = sensor.getCalibratedT();
  double channel15 = sensor.getCalibratedU();
  double channel16 = sensor.getCalibratedV();
  double channel17 = sensor.getCalibratedW();

  static double channels[] = {channel0, channel1,channel2, channel3, channel4,channel5, channel6,channel7, channel8, channel9,
                       channel10, channel11,channel12, channel13, channel14,channel15, channel16,channel17};
                 
  return channels;
  
  }

  
void setup() {
  Serial.begin(115200); // according to docs serial listens at 115200 not 9600 baund rate
  sensor.disableIndicator(); //Turn off the blue status LED for accuracy
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  if(sensor.begin() == false)
  {
    lcdPrint("BAD CONNECTION");
    Serial.println("Sensor does not appear to be connected. Please check wiring."); // debugging
    while(1); // hange till good sensor wiring
  }

  //button pin set as input pullup
  pinMode(6,INPUT_PULLUP); //LED
  
  // for testing purposes wen button is pressed
  //pinMode(7, OUTPUT); //switch
  
  
}





int count = 0;
void loop() {
  
  if(digitalRead(6) ==LOW){
    // If button is pressed then take the measurement
      delay(250); // wait for the button bounce
      count+=250;
        if (count==1000){
          double *allChannels;
          allChannels = sensorRead(); //Take the reading and get all the light channels
          
          // Determine ethanol content takes the above array
          double ethanalPercentage = determineEthanolContent(allChannels);
          // Determine if Drunk
          boolean is_drunk = isDrunk(ethanalPercentage);

          if(is_drunk == true){
            //send SMS to user
            char* smsBody = "I am a Drunk Driver" // Number that sends this message is the driver's no.
            sendSMS(smsBody);
            // Display on the LCD the percentage content
            }
            else{
              //Display on the LCD that all is clear
              
              }

          // reset the sensor.
      }
    //digitalWrite(7,HIGH);
    
    }else{
      //digitalWrite(7,LOW);
      }
}
