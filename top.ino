//Transmitter
#include <VirtualWire.h>
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
const char *on2 = "a";
const char *off2 = "b";
int button = 8;
const int transmit_pin = 11;

//tilt sensor
const int DO1=9;

//servo motor
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    

//remote

#include <IRremote.h>
#include <Servo.h>
int IRpin = 11;  // pin for the IR sensor
IRrecv irrecv(IRpin);
decode_results results;
Servo myservo;


void setup() {
   vw_set_tx_pin(transmit_pin);
  vw_set_ptt_inverted(true); //required for rf link modules
  vw_setup(300); //set data speed
  vw_set_tx_pin(11);
  pinMode(button,INPUT);
      pinMode(DO1, INPUT);
    Serial.begin(9600);
    myservo.attach(2);  // attaches the servo on pin 2 to the servo object
//remote
     Serial.begin(9600);
 irrecv.enableIRIn(); // Start the receiver

}

void loop() {
  //transmitter
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

  //servo motor
  for (pos = 0; pos <= 100; pos += 1) { 
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
//tilt sensor
      int sensorValue = digitalRead(DO1);
    if(sensorValue==LOW){ 
        Serial.println("DO1 more than 10 degree");
        delay(1000);
        while(sensorValue==HIGH){}
   }
    else{
        Serial.println("DO1 less than 10 degree");
        delay(1000);
    }
    bool TiltSwitchVal = digitalRead(DO1);
    Serial.print(F("Val: ")); 
    Serial.println(TiltSwitchVal);

//remote  if (irrecv.decode(&results)) 
   {
     irrecv.resume();   // Receive the next value
   }
  if (results.value == 33441975)  // change according to your IR remote button number
    {
      myservo.write(0);
      delay(15);
    }
    if (results.value == 33446055)  // change according  to your IR remote button number
    {
      myservo.write(30);
    delay(15);
    }

}
