#include "handler_data_types.hpp"
class DataHandlerInterface
{
private:
    /* data */
public:
    DataHandlerInterface(/* args */){}
    ~DataHandlerInterface(){}
    virtual void WriteData(NRF_Data data)=0;
    virtual void ReadData()=0;


};


