#include<RF24.h>
#include<SPI.h>
#include<Arduino.h>
#include "NRF_logger.hpp"

#define Node_1 00
#define Node_2 01

RF24 radio(7,8);
NRF_logger nrf_logger(radio,Node_1,Node_2);
void setup(){
 Serial.begin(9600);
 SPI.begin();
 nrf_logger.setupRadio();
}
void loop(){
NRF_Data data=nrf_logger.ReadLog();
Serial.print(data.message);
Serial.println(data.sensorData);
NRF_Data sendata;
memcpy(sendata.message,"Temeparature is ",24);
sendata.sensorData=67.5;
delay(2000);
nrf_logger.WriteLog(sendata);
}