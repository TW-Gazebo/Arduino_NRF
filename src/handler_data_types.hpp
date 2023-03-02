
enum Header_Types{
    HERRLOG=0,
    HDBGLOG,
    HACT,
    HDATA
};
struct Comm_Data
{
    /* data */
    Header_Types header;
    char message[26];
    // double sensorData;
};

//NRF callback
typedef void(*OnDataPtr)(Comm_Data data);
typedef void(*OnActionPtr)(Comm_Data actionData);
typedef void(*OnLogPtr)(Comm_Data logData);
// typedef void(*OnHM10DataPtr)(Comm_Data data);
