#include <RF24.h>
#include "INRF_logger.hpp"
#include "CallBackInerface.hpp"

class NRF_logger: public INRF_logger
{
private:
    /* data */
   RF24 radio;
   uint8_t node_1;
   uint8_t node_2;
   bool role;
   NRF_Data buffer;
   
   //callback using interface
   CallBackInerface* logger_callback;

   //callback using fun pointer
   CallbackFunctionPtr cbPtr;
   void* ptr;
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

    //callback using interface
    void setCallbacks(CallBackInerface* callback){
        this->logger_callback=callback;

    }

    //callback using function pointer
    void setCallbacks(CallbackFunctionPtr cb, void *p){
        this->cbPtr=cb;
        this->ptr=p;
    }
public:

    void WriteLog(NRF_Data data){
        this->radio.stopListening();
        
        bool ack=this->radio.write(&data,sizeof(this->buffer));
        // if(!ack){
        //     Serial.println("Transmission failed or timed out...");
        // }
        this->radio.startListening();
    }

    void ReadLog(){
        uint8_t pipe;
        if(this->radio.available(&pipe)){
            uint8_t bytes= radio.getPayloadSize();
            radio.read(&(this->buffer),bytes);
            
        }
       
       //callback using interface
       this->logger_callback->OnData(this->buffer);

       //callback using funtion pointer
       cbPtr(ptr,20);
    }

   
};






