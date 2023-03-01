
enum Header_Types{
    HLOG=0,
    HACT,
    HDATA
};
struct  NRF_Data
{
    /* data */
    Header_Types header;
    char message[28];
    // double sensorData;
};

//NRF callback
typedef void(*OnDataPtr)(char data[]);
typedef void(*OnActionPtr)(char actionData[]);
typedef void(*OnLogPtr)(char logData[]);
