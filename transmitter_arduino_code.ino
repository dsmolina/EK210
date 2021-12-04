//Transmitter
#include <VirtualWire.h>


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

//tilt sensor
const int tiltPin = 3;

void setup() {
    Serial.begin(9600);
    vw_set_tx_pin(12);          // Sets pin D12 as the TX pin
    vw_setup(2000);          // Bits per sec
    // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(tiltPin, INPUT);
 }

void loop() {
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  int TiltSensorValue = digitalRead(tiltPin);
  // check if the tilt sensor position has tilted, if so, light LED and transmit data
    bool TiltSwitchVal = digitalRead(tiltPin);
    Serial.print(F("Val: ")); 
    Serial.println(TiltSwitchVal);
  if (TiltSensorValue == LOW) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    vw_send((uint8_t *)&TiltSwitchVal,1); //transmits the data
    vw_wait_tx(); // Wait until the whole message is gone
    delay(200);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
