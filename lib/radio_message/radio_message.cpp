#include <radio_message.h>

RadioMessage::RadioMessage(unsigned char type, unsigned char progressive, unsigned char key)
{
    msg[0] = type << 4 | progressive;
    msg[1] = key;
}

RadioMessage::RadioMessage()
{
}

RadioMessage::~RadioMessage()
{
}

int RadioMessage::getSize() { return 3; }
unsigned char RadioMessage::getType() { return msg[0] >> 4; }
unsigned char RadioMessage::getKey() { return msg[1]; }
unsigned char RadioMessage::getProgressive() { return msg[0] & 0x0F; }
unsigned char RadioMessage::getValue() { return msg[2]; }
unsigned char *RadioMessage::encode(unsigned char value)
{
    msg[2] = value;
    return msg;
}
void RadioMessage::decode(unsigned char *msg)
{
    for (int i = 0; i < 3; i++)
        this->msg[i] = msg[i];
}