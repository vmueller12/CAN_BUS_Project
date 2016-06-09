// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 9;

MCP_CAN CAN(SPI_CS_PIN);                                 // Set CS to pin 10

void setup()
{
    Serial.begin(115200);

START_INIT:
    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
    }
    else
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
        goto START_INIT;
    }
}

// Function to override a value
void func(unsigned char *ptr, int sen){
  // change the value on the 4rd locaion
  *(ptr + 3) = sen;
  }

// CAN Bus 8 Byte Data Message
unsigned char stmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void loop()
{
    // Reading value of potentiometer
    int sen = analogRead(A0);
    // Value mapping
    int newValue = map(sen, 0,1023,0,120);
    //Calling function to override Data Message
    func(stmp, newValue);
    // send data:  id = 0x280, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x280, 0, 8, stmp);
    delay(100);                       // send data per 100ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
