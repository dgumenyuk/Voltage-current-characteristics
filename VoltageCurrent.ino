
#include <Wire.h>
#include "Arduino.h"
#include <SPI.h>
#include <Adafruit_INA219.h>
#include <AD56X4.h>

Adafruit_INA219 ina219;

int AD56X4_SS_pin = 10; //slave select pin used for spi communication

float busvoltage;
float current_mA;
String Current;
String Voltage;
String SendData;

String Space;

word y;
word i;
word output;

void setup()
{
  Serial.begin(9600);
  delay(10);

  //set up spi communiction with ADC
  pinMode(10,OUTPUT);
  pinMode(AD56X4_SS_pin,OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.begin();
  AD56X4.reset(AD56X4_SS_pin,true);

  //set up communication with INA219
  ina219.begin();
  ina219.setCalibration_16V_400mA(); // max. current 400mA, max.resolution 100uA
  busvoltage = 0;
  current_mA = 0;
  Space = " ";
  y=0x00;


}

void loop()
{
  Serial.print("0.00 0.00 ");
  delay(1000);
  AD56X4.useInternalReference(AD56X4_SS_pin, true);
  for(i=0x000; i<0xB33; i+=0x029) // choose ADC step of 50mV, set max. output value to 4V
  {
   y=i;
   y=y<<4;
   output = word(y);
   AD56X4.setChannel(AD56X4_SS_pin, AD56X4_SETMODE_INPUT, AD56X4_CHANNEL_A, output); //use channel A
   AD56X4.updateChannel(AD56X4_SS_pin, AD56X4_CHANNEL_A);
   delay(100);
   busvoltage = ina219.getBusVoltage_V();
   current_mA = ina219.getCurrent_mA();
   
   //form string to send to a laptop
   Current = String(current_mA);
   Voltage = String(busvoltage);
   SendData =  Voltage  + Space + Current + Space;

   Serial.println(SendData);

   delay(300);
  }
  
}
