#include <INA226.h>

#include <Adafruit_INA219.h>

//#include <Adafruit_INA219.h>

#include <Wire.h>
#include "Arduino.h"
#include <SPI.h>
//#include <Adafruit_INA219.h>
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

uint16_t value2 = 3;
uint16_t value1 = 4;
uint16_t value3 = 7;

uint16_t config_;

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
   AD56X4.reset(AD56X4_SS_pin,true);
AD56X4.useInternalReference(AD56X4_SS_pin, false);
  //set up communication with INA219
  ina219.begin();
  ina219.setCalibration_16V_400mA(); // max. current 400mA, max.resolution 100uA
  config_ = INA219_CONFIG_BVOLTAGERANGE_16V |
            INA219_CONFIG_GAIN_1_40MV |
            INA219_CONFIG_BADCRES_12BIT |
            INA219_CONFIG_SADCRES_12BIT_1S_532US |
            INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
 // config_ |= value1;
 // config_ &= ~value2; 
  config_ &= ~value3;
  busvoltage = 0;
  current_mA = 0;
  ina219.wireWriteRegister(INA219_REG_CONFIG,config_);
  
  Space = " ";
  y=0x00;
delay(100);
  //startup



y=0x00000000;
   y=y<<4;
   output = word(y);
   AD56X4.setChannel(AD56X4_SS_pin, AD56X4_SETMODE_INPUT, AD56X4_CHANNEL_ALL, output); //use channel A
   AD56X4.updateChannel(AD56X4_SS_pin, AD56X4_CHANNEL_ALL);
   delay(10);

}

void loop()
{
    AD56X4.useInternalReference(AD56X4_SS_pin, false);
    
y=0x000E;
   y=y<<4;
   output = word(y);
   AD56X4.setChannel(AD56X4_SS_pin, AD56X4_SETMODE_INPUT, AD56X4_CHANNEL_ALL, output); //use channel A
   AD56X4.updateChannel(AD56X4_SS_pin, AD56X4_CHANNEL_ALL);
   delay(10);
    
   /*  Serial.print("0.00 0.00 ");
  delay(200);
  
  
 Current = String(current_mA);
   Voltage = String(busvoltage);
   SendData =  Voltage  + Space + Current + Space;

   Serial.print(SendData);

   delay(300);
  
  for(i=0x000; i<0x0999; i+=0x000) // choose ADC step of 50mV, set max. output value to 4V
  {
   y=i;
   y=y<<4;
   output = word(y);
   AD56X4.setChannel(AD56X4_SS_pin, AD56X4_SETMODE_INPUT, AD56X4_CHANNEL_ALL, output); //use channel A
   AD56X4.updateChannel(AD56X4_SS_pin, AD56X4_CHANNEL_ALL);
   delay(10);
  // busvoltage = ina219.getBusVoltage_V();
  // current_mA = ina219.getCurrent_mA();
   
   //form string to send to a laptop
  // Current = String(current_mA);
  // Voltage = String(busvoltage);
 //  SendData =  Voltage  + Space + Current + Space;

   //Serial.print(SendData);

   //delay(2000);*/
  
  
}
