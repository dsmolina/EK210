//Transmitter
#include <VirtualWire.h>
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
const char *on2 = "a";
const char *off2 = "b";
int button = 8;
const int transmit_pin = 12;



void setup() {
  vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true); //required for rf link modules
  vw_setup(300); //set data speed
  vw_set_tx_pin(12);
  pinMode(button,INPUT);
 }

void loop() {
  if (digitalRead(button) == HIGH){
    vw_send((uint8_t *)on2, strlen(on2)); // send the data out to the world
    vw_wait_tx(); // wait a moment
    delay(200);
  }
  if (digitalRead(button)==LOW){
    vw_send((uint8_t *)off2, strlen(off2));
    vw_wait_tx();
    delay(200);
  }
}
