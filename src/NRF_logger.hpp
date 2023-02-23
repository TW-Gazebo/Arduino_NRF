#include <RF24.h>
#include "INRF_logger.hpp"


class NRF_logger: public INRF_logger
{
private:
    /* data */
   RF24 radio;
   uint8_t node_1;
   uint8_t node_2;
   bool role;
   NRF_Data buffer;
public:
    NRF_logger(const RF24 &radio,uint8_t node_1, uint8_t node_2){
    this->radio=radio;
    this->node_1=node_1;
    this->node_2 =node_2;
    this->role=false;
    }

    ~NRF_logger(){}

public:
    void setupRadio(){
        if(!this->radio.begin()) // Start up the radio
        {
            Serial.println("Hardware not respomding");
        }
        this->radio.setPALevel(RF24_PA_MAX);
        this->radio.setPayloadSize(sizeof(this->buffer));
        this->radio.setDataRate(RF24_250KBPS);
        this->radio.openWritingPipe(this->node_1);
        this->radio.openReadingPipe(1,this->node_2);
        this->radio.startListening();
    }
    void WriteLog(NRF_Data data){
        this->radio.stopListening();
        
        bool ack=this->radio.write(&data,sizeof(this->buffer));
        // if(!ack){
        //     Serial.println("Transmission failed or timed out...");
        // }
        this->radio.startListening();
    }

    NRF_Data ReadLog(){
        uint8_t pipe;
        if(this->radio.available(&pipe)){
            uint8_t bytes= radio.getPayloadSize();
            radio.read(&(this->buffer),bytes);
            
        }
        return (this->buffer);

    }
};






