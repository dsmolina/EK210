// receiver sketch

#include <VirtualWire.h>
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
int ledpin = 2;
const int receive_pin = 11;

void setup()
{
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_inverted(true); // Required for RF link modules
  vw_setup(300);
  vw_rx_start();
  pinMode(ledpin, OUTPUT);
}

void loop()
{
  if (vw_have_message()){
    vw_get_message(buf, &buflen);
        switch(buf[0])
    {
    case 'a':
      digitalWrite(ledpin, HIGH);
      Serial.println("MESSAGE RECEIVED");
      break;
    case 'b':
      digitalWrite(ledpin, LOW);
      break;
  }
  }
}
