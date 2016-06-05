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

unsigned char stmp[8] = {0, 100, 200, 300, 4, 5, 6, 7};
void loop()
{
    // send data:  id = 0x280, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x280, 0, 8, stmp);
    delay(100);                       // send data per 100ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
