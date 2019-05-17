#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
//#include <Servo.h>
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t node00 = 00;
//Servo myservo;  // create servo object to control a servo
void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  //myservo.attach(3);   // (servo pin)
}
void loop() {
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    Serial.println("incoming data");
    RF24NetworkHeader header(node00);
    unsigned long incomingData;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    Serial.println(incomingData);
    //myservo.write(incomingData);  // tell servo to go to a particular angle
  }

}
