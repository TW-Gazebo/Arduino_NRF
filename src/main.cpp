#include<RF24.h>
#include<SPI.h>
#include<Arduino.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<SoftwareSerial.h>
#include"nrf_data_handler.hpp"
#include"hm-10_data_handler.hpp" 

using namespace std;

#define Node_1 00
#define Node_2 01




void SendDataToNRF();


/*Setting up the NRF data handler*/
RF24 radio(7,8);
SoftwareSerial HM10(4,5); //Rx-4, TX-5
NRFDataHandler nrfDataHandler(radio,Node_1,Node_2);
HM10DataHandler hm10datahandler(&HM10);

void setup(){
 Serial.begin(9600);
 SPI.begin();
 nrfDataHandler.SetupRadio();
 nrfDataHandler.InitializeCallbacks(OnData,OnLog);
 hm10datahandler.InitializeCallbacks(OnAction);
}
void loop(){
/*Reading data from NRF*/
nrfDataHandler.ReadData();

delay(3000);

/*Sending data to NRF*/
SendDataToNRF();
}

void SendDataToNRF(){
Comm_Data data;
data.header=(Header_Types)HDATA;
memcpy(data.message,"67.5",24);
delay(2000);
nrfDataHandler.WriteData(data);
}


void OnData(Comm_Data data){
    Serial.print("Temperature data in string format: ");
    Serial.println(data.message);
    Serial.print("Temperature data in double: ");
    float value=atof(data.message);
    Serial.println(value);

    /*concatenate _D char to log msg to differentiate the msg as info(sensor values) data msg*/
    char destStr[28]="_G";
    strcat(data.message,destStr);
    hm10datahandler.WriteData(data); 

}

void OnAction(Comm_Data actdata){
    Serial.print("Commands from mobile using HM10");
    Serial.println(actdata.message);

}

void OnLog(Comm_Data logData){
    /*Log data for err and debug*/
    if(logData.header == HERRLOG){
        Serial.print("Err log: ");
        Serial.println(logData.message);

        /*concatenate _E char to log msg to differentiate the msg as Err msg*/
        char destStr[28]="_E";
        strcat(logData.message,destStr);
        
        hm10datahandler.WriteData(logData);   
    }
    if (logData.header == HDBGLOG)
    {
        Serial.print("Debug log: ");
        Serial.println(logData.message);

        /*concatenate _G char to log msg to differentiate the msg as debug msg*/
        char destStr[28]="_G";
        strcat(logData.message,destStr);

        hm10datahandler.WriteData(logData); 
    }
    
}
