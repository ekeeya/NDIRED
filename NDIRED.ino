#include "SparkFun_AS7265X.h" 
#include <Wire.h> //for I2C
#include <LiquidCrystal.h>
#define BUTTONPIN 6


AS7265X sensor;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// variables will change:
int buttonState = 0;         

void setup() {
  // initialize the LED pin as an output:
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("Hello world");
  
  pinMode(BUTTONPIN, INPUT_PULLUP);
  if(sensor.begin() == false)
  {
    Serial.println("SENSOR OFF");
    while(1);
  }
  Serial.println("PRESS BUTTON");
  lcd.print("PRESS BUTTON");
}

double * sensorRead(){
  sensor.takeMeasurementsWithBulb();
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


void loop() {
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTONPIN);

  // check if the pushbutton is pressed
  if (buttonState == LOW) {
    double *allChannels;
    allChannels = sensorRead();
    for(int i = 0;i<18; i++){
      Serial.println(allChannels[i]);  
    }
    Serial.println("RESET DEVICE!");
    lcd.print("RESET DEVICE");
  }
}
