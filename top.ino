//Transmitter
#include <VirtualWire.h>


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

//tilt sensor
const int tiltPin = 4;

#include <IRremote.h>
int IRpin = 11;  // pin for the IR sensor
IRrecv irrecv(IRpin);
decode_results results;

int sensePin = A0;  
int sensorInput;    
double temp;        
const int hot = 40; //This is the highest temperature
const int cold = -23; //This is the lowest temperature
unsigned long previousMillis = 0;
int solenoidpin = 3;
unsigned long interval = (unsigned long) 1000*60*60*24; //24 hours time interval

void setup() {
    Serial.begin(9600);
    vw_set_tx_pin(12);          // Sets pin D12 as the TX pin
    vw_setup(2000);          // Bits per sec
    // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(tiltPin, INPUT);
   Serial.begin(9600);
 irrecv.enableIRIn(); // Start the receiver
 pinMode(ledPin,OUTPUT);
 pinMode(solenoidpin, OUTPUT);
 }

void loop() {
  sensorInput = analogRead(A0);        //read the analog sensor and store it
  temp = (double)sensorInput / 1024;   
  temp = temp * 5;                     
  temp = temp - 0.5;                   
  temp = temp * 100;        // Temperature in celsius
  unsigned long currentMillis = millis(); //Get the current time in ms

   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  int TiltSensorValue = digitalRead(tiltPin);
  // check if the tilt sensor position has tilted, if so, light LED and transmit data
    bool TiltSwitchVal = digitalRead(tiltPin);
    Serial.print(F("Val: ")); 
    Serial.println(TiltSwitchVal);
  if (TiltSensorValue == LOW) {
    // turn LED on:
    unsigned long previousMillis = 0;
    digitalWrite(ledPin, HIGH);
    vw_send((uint8_t *)&TiltSwitchVal,1); //transmits the data
    vw_wait_tx(); // Wait until the whole message is gone
    delay(200);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  if (temp <= cold || temp >= hot || currentMillis - previousMillis >= interval  || irrecv.decode())
 
   {
    digitalWrite(solenoidpin, HIGH);
     irrecv.resume();   // Receive the next value
     digitalWrite(ledPin,HIGH);
      previousMillis = currentMillis; //Timer will reset because the rats were released at one particular circumstance, the amount of time passed is now zero.
       delay(1000);  
       //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //Sleep for 8 seconds to lower the battery comsumption
       delay(100000);
       digitalWrite(solenoidpin,LOW); 
       exit(0); 
   }
  else
  {
  digitalWrite(ledPin, LOW);
  digitalWrite(solenoidpin,LOW);
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  delay(1000);  
  }
 delay(200);
}
