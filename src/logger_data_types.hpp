struct  NRF_Data
{
    /* data */
    char message[28];
    // double sensorData;
};

// Callback function pointer.
typedef void(*CallbackFunctionPtr)(void*, int);