// receiver sketch

#include <Wire.h>
#include <VirtualWire.h>
int sensorInput;    //The variable we will use to store the sensor input
int ledpin = 13;
int sensePin = A0;  //This is the Arduino Pin that will read the sensor output

void setup()
{
   Serial.begin(9600); //Start the Serial Port at 9600 baud (default)
vw_set_rx_pin(12);       //Sets pin D12 as the RX Pin
  vw_setup(2000);       // Bits per sec
  vw_rx_start();           // Start the receiver PLL running
  pinMode(ledpin, OUTPUT);

}

void loop()
{
 // digitalWrite(ledpin, HIGH);
  uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if( vw_get_message(buf, &buflen))
      {
        digitalWrite(ledpin, HIGH);
          Serial.println("");
      }

delay(200);

}
