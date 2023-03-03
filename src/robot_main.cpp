#include<RF24.h>
#include<SPI.h>
#include<Arduino.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include"nrf_data_handler.hpp"

using namespace std;

#define Node_1 01
#define Node_2 00

void SendDataToNRF();
void OnData(Comm_Data data);
void OnAction(Comm_Data actdata);
void OnLog(Comm_Data logData);

/*Setting up the NRF data handler*/
RF24 radio(7,8);
NRFDataHandler nrfDataHandler(radio,Node_1,Node_2);

void setup(){
 Serial.begin(9600);
 SPI.begin();
 nrfDataHandler.SetupRadio();
 nrfDataHandler.InitializeCallbacks(OnData,OnLog,OnAction);
}
void loop(){
/*Reading data from NRF*/
nrfDataHandler.ReadData();

delay(500);

/*Sending data to NRF*/
SendDataToNRF();
}

void SendDataToNRF(){
    Comm_Data data;
    data.header=(Header_Types)HDATA;
    memcpy(data.message,"67.5",24);
    // delay(2000);
    nrfDataHandler.WriteData(data);

    // delay(200);
    data.header=(Header_Types)HERRLOG;
    memcpy(data.message,"ERROR",24);
    nrfDataHandler.WriteData(data);

    // delay(200);
    data.header=(Header_Types)HDBGLOG;
    memcpy(data.message,"DEBUG",24);
    nrfDataHandler.WriteData(data);
}


void OnData(Comm_Data data){
    // Serial.print("Temperature data in string format: ");
    // Serial.println(data.message);
    // Serial.print("Temperature data in double: ");
    // float value=atof(data.message);
    // Serial.println(value);

}

void OnAction(Comm_Data actdata){
    Serial.print("Commands from mobile using HM10 ");
    Serial.println(actdata.message);

}

void OnLog(Comm_Data logData){
    // /*Log data for err and debug*/
    // if(logData.header == HERRLOG){
    //     Serial.print("Err log: ");
    //     Serial.println(logData.message);

    //     /*concatenate _E char to log msg to differentiate the msg as Err msg*/
    //     char destStr[28]="_E";
    //     strcat(logData.message,destStr);
        
    //     hm10datahandler.WriteData(logData);   
    // }
    // if (logData.header == HDBGLOG)
    // {
    //     Serial.print("Debug log: ");
    //     Serial.println(logData.message);

    //     /*concatenate _G char to log msg to differentiate the msg as debug msg*/
    //     char destStr[28]="_G";
    //     strcat(logData.message,destStr);

    //     hm10datahandler.WriteData(logData); 
    // }
    
}