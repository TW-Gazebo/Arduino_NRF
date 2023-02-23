// // /*
// //   Libraries:
// //   nRF24/RF24, https://github.com/nRF24/RF24
// //   nRF24/RF24Network, https://github.com/nRF24/RF24Network
// // */

// #include <RF24Network.h>
// #include <RF24.h>
// #include <SPI.h>
// #include<Arduino.h>

// RF24 radio(7,8);               // nRF24L01 (CE,CSN)
// RF24Network network(radio);      // Include the radio in the network
// const uint16_t this_node = 01;   // Address of this node in Octal format ( 04,031, etc)
// const uint16_t node01 = 00;      // Address of the other node in Octal format
// char input = 'A';

// void setup() {
//   Serial.begin(9600);
//   while (!Serial) {
//     // some boards need to wait to ensure access to serial over USB
//   }
//   SPI.begin();
//   radio.begin();
//   network.begin(90, this_node);  //(channel, node address)
//   radio.setDataRate(RF24_2MBPS);
// }

// void loop() {
//   network.update();
//   //===== Receiving =====//
//   while ( network.available() ) {     // Is there any incoming data?
//     RF24NetworkHeader header;
//     unsigned long incomingData;
//     network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
//     // Serial.print("incomingData: ");
//     // Serial.println(incomingData);
//     if(incomingData == 'A'){
//       input='A';
//     }
//     else{
//       input= 'B';
//     }
//   }
//   //===== Sending =====//
//   RF24NetworkHeader header2(node01);     // (Address where the data is going)
//   bool ok = network.write(header2, &input, sizeof(input)); // Send the data
  

// }