#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include<NewPing.h>
#define trig 9
#define echo 8
#define max_distance 400
NewPing sensor(trig,echo,max_distance);
RF24 radio(40, 53);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      
void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
}
void loop() {
  network.update();
  //unsigned long potValue = analogRead(A0);  // Read the potentiometer value
  unsigned long Value = sensor.ping_cm();//map(potValue, 0, 1023, 0, 180); // Convert the value to 0-180
  RF24NetworkHeader header(node01);     // (Address where the data is going)
  bool ok = network.write(header, &Value, sizeof(Value)); // Send the data
  Serial.println(Value);
}
