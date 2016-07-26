/*
  NODE A: CAN-BUS Shield, send button state and receive analog value from Node B to control the LED brightness  

  Created 24/07/2016
  By Vitali Mueller

  http://vitalimueller.com

*/

#include <mcp_can.h>
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
// Button declaration
const int buttonPin = 10;
// State of the button, assigned initial value of 0
int buttonState = 0;
// LED output
const int led = 3;

// Set CS pin
MCP_CAN CAN(SPI_CS_PIN);    

void setup()
{
    
    Serial.begin(9600);
    pinMode(buttonPin, INPUT);
    pinMode(led, OUTPUT);
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
            analogWrite(led, buf[i]);
        }
    }
    /** End reading incoming CAN Bus Messages */

    /** Sending CAN Bus Messeges */

    // Reading Button State
    buttonState = digitalRead(buttonPin);
    // Changing Value of the Data Frame
    changeValue(stmp, buttonState);
    // send data:  id = 0x00, standard frame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x70,0, 1, stmp);
    
    /** End sending CAN Bus Messages */
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
