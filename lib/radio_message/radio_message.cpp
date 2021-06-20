#include <radio_message.h>
#include <stdlib.h>

RadioMessage::RadioMessage(unsigned char type, unsigned char progressive, unsigned char key)
{
    msg[0] = rand() % __UINT8_MAX__;
    msg[1] = type << 4 | progressive;
    msg[2] = key;
}

RadioMessage::RadioMessage()
{
}

RadioMessage::~RadioMessage()
{
}

int RadioMessage::getSize() { return 4; }
unsigned char RadioMessage::getType() { return msg[1] >> 4; }
unsigned char RadioMessage::getKey() { return msg[2]; }
unsigned char RadioMessage::getProgressive() { return msg[1] & 0x0F; }
unsigned char RadioMessage::getValue() { return msg[3]; }
unsigned char *RadioMessage::encode(unsigned char value)
{
    msg[3] = value;
    return msg;
}
void RadioMessage::decode(unsigned char *msg)
{
    for (int i = 0; i < getSize(); i++)
        this->msg[i] = msg[i];
}
unsigned char RadioMessage::getUID(){return msg[0];}
void RadioMessage::newUID(){++msg[0]%__UINT8_MAX__;}