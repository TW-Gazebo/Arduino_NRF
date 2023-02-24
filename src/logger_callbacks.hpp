#include "CallBackInerface.hpp"
#include<Arduino.h>
class logger_callbacks:public CallBackInerface
{
private:
    /* data */
public:
    logger_callbacks(){}
    ~logger_callbacks(){}

public:
    void OnData(NRF_Data data){
            Serial.print("NRF_data: ");
            Serial.print(data.message);
            Serial.print(data.sensorData);
        }

/* calllback fun using func pointer*/
public:
    static void staticOnAction(void* p,int data){
        ((logger_callbacks*)p)->OnAction(data);
    }

    void OnAction(int data){

        //Action on data;
        
    }
};


