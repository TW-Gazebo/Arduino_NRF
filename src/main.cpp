#include<RF24.h>
#include<SPI.h>
#include<Arduino.h>
#include "NRF_logger.hpp"
#include "logger_callbacks.hpp"

#define Node_1 00
#define Node_2 01

RF24 radio(7,8);
NRF_logger nrf_logger(radio,Node_1,Node_2);
logger_callbacks logger_callback;
void setup(){
 Serial.begin(9600);
 SPI.begin();
 nrf_logger.setupRadio();

 //callback using interface
 nrf_logger.setCallbacks(&logger_callback);

 //callback using func pointer
 nrf_logger.setCallbacks(logger_callbacks::staticOnAction, &logger_callback);
}
void loop(){
nrf_logger.ReadLog();
NRF_Data sendata;
memcpy(sendata.message,"Temeparature is ",24);
sendata.sensorData=67.5;
delay(2000);
nrf_logger.WriteLog(sendata);
}