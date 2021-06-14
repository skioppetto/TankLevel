
class RadioMessage
{
private:
    unsigned char msg[3];
public:
    RadioMessage();
    RadioMessage(unsigned char type, unsigned char progressive, unsigned char key);
    ~RadioMessage();
    int getSize();
    unsigned char* encode(unsigned char value);
    unsigned char getType();
    unsigned char getProgressive();
    unsigned char getKey();
    unsigned char getValue();
    void decode(unsigned char* msg);
};

