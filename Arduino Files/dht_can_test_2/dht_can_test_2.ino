// demo: CAN-BUS Shield, send data

/* Humidity Sensor Lib and Pin define */
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
/* End */

#include <mcp_can.h>
#include <SPI.h>

const int SPI_CS_PIN = 9;


DHT dht(DHTPIN, DHTTYPE);


MCP_CAN CAN(SPI_CS_PIN);                                 // Set CS to pin 10

void setup()
{
    Serial.begin(115200);
    Serial.println("DHT22 TEST!");

START_INIT:
    if(CAN_OK == CAN.begin(CAN_500KBPS))                   // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init ok!");
        dht.begin();
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
    delay(2000);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);


    // Compute heat index in Fahrenheit (the default)
      
      float hif = dht.computeHeatIndex(f, h);
      
      // Compute heat index in Celsius (isFahreheit = false)
      
      float hic = dht.computeHeatIndex(t, h, false);
      
      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print(f);
      Serial.print(" *F\t");
      Serial.print("Heat index: ");
      Serial.print(hic);
      Serial.print(" *C ");
      Serial.print(hif);
      Serial.println(" *F");

    

    if(isnan(h) || isnan(t) || isnan(f)){
      Serial.println("Failed to read from DHT Sensor!");
      }
    // send data:  id = 0x280, standrad flame, data len = 8, stmp: data buf
    CAN.sendMsgBuf(0x280, 0, 8, stmp);
    //delay(100);                       // send data per 100ms
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
