#include<Arduino.h>
#include<radio_message.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
RadioMessage rmReceived;

void setup(){
    #ifdef DEBUG
    Serial.begin(9600);
    #endif
    driver.init(); // TODO: should I do something if driver init fail? see #53
}

void loop(){
    uint8_t msg[rmReceived.getSize()];
    uint8_t size = sizeof(msg);
    if (driver.recv(msg, &size)){
        rmReceived.decode(msg);
        #ifdef DEBUG
        Serial.print("Message received:: type: ");
        Serial.print(rmReceived.getType());
        Serial.print("\tprogressive: ");
        Serial.print(rmReceived.getProgressive());
        Serial.print("\tkey: ");
        Serial.print(rmReceived.getKey());
        Serial.print("\tvalue: ");
        Serial.println(rmReceived.getValue());
        #endif   
    }
}