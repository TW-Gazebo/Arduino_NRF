#include "logger_data_types.hpp"
class INRF_logger
{
private:
    /* data */
public:
    INRF_logger(/* args */){}
    ~INRF_logger(){}
    virtual void WriteLog(NRF_Data data)=0;
    virtual void ReadLog()=0;


};


