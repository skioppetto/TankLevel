// Tank Level message types 
const unsigned char TANK_LEVEL_MSG_TYPE = 0XA;
const unsigned char TANK_LEVEL_MSG_PROGRESSIVE = 0x01;  // only one tank level in the network
const unsigned char TANK_LEVEL_MSG_LEVEL_KEY = 0X01;    // this key contains the current level
const unsigned char TANK_LEVEL_MSG_CM_KEY = 0X02;       // this key contains the current level in cm 
const unsigned char TANK_LEVEL_MSG_TOF_KEY = 0X03;       // this is the tof of the sensor in us
