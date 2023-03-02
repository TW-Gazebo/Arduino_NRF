#include<RF24.h>
#include<SPI.h>
#include<Arduino.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "nrf_data_handler.hpp"

using namespace std;

#define Node_1 00
#define Node_2 01


void OnData(char data[]){
    Serial.print("Temperature data in string format: ");
    Serial.println(data);
    Serial.print("Temperature data in double: ");
    float value=atof(data);
    Serial.println(value);
    


}

void OnAction(char actdata[]){

}

void OnLog(char logData[]){

}

void SendDataToNRF();


/*Setting up the NRF data handler*/
RF24 radio(7,8);
NRFDataHandler nrfDataHandler(radio,Node_1,Node_2);

void setup(){
 Serial.begin(9600);
 SPI.begin();
 nrfDataHandler.SetupRadio();
 nrfDataHandler.InitializeCallbacks(OnData,OnAction,OnLog);
}
void loop(){
/*Reading data from NRF*/
nrfDataHandler.ReadData();

delay(3000);

/*Sending data to NRF*/
SendDataToNRF();
}

void SendDataToNRF(){
NRF_Data data;
data.header=HDATA;
memcpy(data.message,"67.5",24);
delay(2000);
nrfDataHandler.WriteData(data);
}

