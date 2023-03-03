// #ifndef Data_Handler_Interface_H
// #define Data_Handler_Interface_H
#pragma once
#include "handler_data_types.hpp"
class DataHandlerInterface
{
private:
    /* data */
public:
    DataHandlerInterface(/* args */){}
    ~DataHandlerInterface(){}
    virtual void WriteData(Comm_Data data)=0;
    virtual void ReadData()=0;


};
// #endif

