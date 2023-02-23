
struct  NRF_Data
{
    /* data */
    char message[24];
    double sensorData;
};
class INRF_logger
{
private:
    /* data */
public:
    INRF_logger(/* args */){}
    ~INRF_logger(){}
    virtual void WriteLog(NRF_Data data)=0;
    virtual NRF_Data ReadLog()=0;
};


