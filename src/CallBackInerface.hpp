#include"logger_data_types.hpp"
class CallBackInerface
{
private:
    /* data */
public:
    // CallBackInerface(/* args */);
    ~CallBackInerface(){}

public:
    virtual void OnData(NRF_Data data)=0;
};

