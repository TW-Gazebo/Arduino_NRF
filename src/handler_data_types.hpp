
enum Header_Types{
    HERRLOG=0,
    HDBGLOG,
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
typedef void(*OnDataPtr)(NRF_Data data);
typedef void(*OnActionPtr)(NRF_Data actionData);
typedef void(*OnLogPtr)(NRF_Data logData);
