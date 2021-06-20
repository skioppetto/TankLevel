
class RadioMessage
{
private:
    unsigned char msg[4];
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
    void newUID();
    unsigned char getUID();
    void decode(unsigned char* msg);
};

