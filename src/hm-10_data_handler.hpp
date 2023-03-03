// #ifndef HM10DataHandler_H
// #define HM10DataHandler_H
#pragma once
#include<SoftwareSerial.h>
#include "data_handler_interface.hpp"

class HM10DataHandler:public DataHandlerInterface
{
private:
    SoftwareSerial* HM10;
    OnActionPtr p_OnAction;
public:
    HM10DataHandler(SoftwareSerial* hm10)
    {
        this->HM10=hm10;
    }

    ~HM10DataHandler(){

    }

public:
    void SetupHM10(){
        this->HM10->begin(9600);

    }

     //initialize callbacks 
    void InitializeCallbacks(OnActionPtr actPtr){
        if(actPtr != nullptr){
            this->p_OnAction=actPtr;
        }
        else
            Serial.println("callbacks pointer is null");
    }

    void WriteData(Comm_Data hmData){
        // Serial.print("Writing data on HM10: ");
        // Serial.println(hmData.message);
        if(this->HM10 != nullptr){
            this->HM10->write(hmData.message);
        }
        
    }
    void ReadData(){
        String inData="";
        char appData;
        String res="";
        // if(this->HM10 != nullptr){
            HM10->listen();
            while (HM10->available() > 0) {   // if HM10 sends something then read

                appData = HM10->read();

                inData = String(appData);  // save the data in string format
                // Serial.print("HM10 data in string ");
                // Serial.println(inData);
                res=res+inData;
            }
        // }
        Comm_Data tmpbuffer;
        tmpbuffer.header=(Header_Types)HACT;
        // strcpy(tmpbuffer.message,inData.c_str());
        // String data="atul";
        memcpy(tmpbuffer.message,res.c_str(),26);
        if(this->p_OnAction != nullptr)
            this->p_OnAction(tmpbuffer);
        else
            Serial.println("p_OnAction is null");
    }

};

// #endif