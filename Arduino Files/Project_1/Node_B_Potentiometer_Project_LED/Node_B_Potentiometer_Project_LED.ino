/*
  NODE B: CAN-BUS Shield, send potentiometer value and receive button state from Node A to switch off/on LED  

  Created 24/07/2016
  By Vitali Mueller

  http://vitalimueller.com

*/


#include <SPI.h>
#include "mcp_can.h"

const int SPI_CS_PIN = 9;
// Output LED Pin
const int LED = 8;

// used to store the mapped potentiometer value 0 - 1023 -> 0 - 255
int outputValue;

// Set CS pin
MCP_CAN CAN(SPI_CS_PIN);                                    

void setup()
{
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
    
    // init can bus : baudrate = 500k
    while (CAN_OK != CAN.begin(CAN_500KBPS))              
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}
// CAN Bus Data Frame - sending only one byte of data - max value 255
unsigned char stmp[1] = {0};

// Function to change the Data Frame value
void changeValue(unsigned char *arr, int state){
  *arr = state;    
}

void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];
    // Reading Potentiometer value
    int sensorValue = analogRead(A0);
    // Mapping the value from 0 - 1023 to 0 - 255
    outputValue = map(sensorValue, 0, 1023, 0, 255);    

    /** Reading incoming CAN Bus Messages */ 
    if(CAN_MSGAVAIL == CAN.checkReceive())      
    {
        CAN.readMsgBuf(&len, buf);  

        unsigned char canId = CAN.getCanId();

        Serial.println("-- New Iteration -- ");
        Serial.println("get data from ID: ");
        Serial.println(canId, HEX);
        // print the data
        for(int i = 0; i<len; i++)    
        {
            Serial.print(buf[i]);
            digitalWrite(LED, buf[i]);
        }
    }
    /** End reading incoming CAN Bus Messages */

    /** Sending CAN Bus Messages */
    changeValue(stmp, outputValue);
    // send data:  id = 0x00, standard frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x90,0, 1, stmp);
    /** End sending CAN Bus Messages */
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
