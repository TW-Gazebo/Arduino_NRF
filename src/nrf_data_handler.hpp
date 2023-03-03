#include <RF24.h>
#include "data_handler_interface.hpp"

class NRFDataHandler: public DataHandlerInterface
{
private:
    /* data */
   RF24 radio;
   uint8_t node_1;
   uint8_t node_2;
   bool role;
   Comm_Data buffer;

   //callabcks pointers
   OnDataPtr p_OnData;
   OnActionPtr p_OnAction;
   OnLogPtr p_OnLog; 

public:
    NRFDataHandler(const RF24 &radio,uint8_t node_1, uint8_t node_2){
    this->radio=radio;
    this->node_1=node_1;
    this->node_2 =node_2;
    this->role=false;
    }

    ~NRFDataHandler(){}

public:
    void SetupRadio(){
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

    //initialize callbacks 
    void InitializeCallbacks(OnDataPtr dataPtr, OnLogPtr logPtr,OnActionPtr actPtr){
        if(dataPtr != nullptr && logPtr != nullptr){
            this->p_OnData=dataPtr;
            this->p_OnAction=actPtr;
            this->p_OnLog=logPtr;
        }
        else
            Serial.println("callbacks pointer are null");
    }
public:

    void WriteData(Comm_Data data){
        this->radio.stopListening();
        
        if ((data.header > -1) && (strlen(data.message) != 0))
        {
            bool ack=this->radio.write(&data,sizeof(this->buffer));
            if(!ack){
                Serial.println("Transmission failed or timed out...");
            }
            this->radio.startListening();

        }
        else
            Serial.println("Data is empty");
    }

    void ReadData(){
        uint8_t pipe;
        if(this->radio.available(&pipe)){
            uint8_t bytes= radio.getPayloadSize();
            radio.read(&(this->buffer),bytes);
            
        }

        if ((this->buffer.header > -1) && (strlen(this->buffer.message) != 0))
        {
            if(this->buffer.header == HDATA){
                if(this->p_OnData != nullptr)
                this->p_OnData(this->buffer);
                else
                Serial.println("p_OnData is mull");
            }
            if(this->buffer.header == HACT){
                if(this->p_OnAction != nullptr)
                this->p_OnAction(this->buffer);
                else
                Serial.println("p_OnData is mull");
            }
            if ((this->buffer.header == HERRLOG) || (this->buffer.header == HDBGLOG)){
                if(this->p_OnLog != nullptr)
                this->p_OnLog(this->buffer);
                else
                Serial.println("p_OnLog is null");
            }
        
        }
        else
            Serial.println("buffer is empty...!");
        
        
        
    }

   
};






