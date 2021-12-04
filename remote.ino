
//https://create.arduino.cc/projecthub/Raushancpr/servo-motor-control-with-remote-fd6d95


#include <IRremote.h>
int IRpin = 11;  // pin for the IR sensor
IRrecv irrecv(IRpin);
decode_results results;
int ledPin = 13;

//#include <LowPower.h>
int sensePin = A0;  
int sensorInput;    
double temp;        
const int hot = 40; //This is the highest temperature
const int cold = -23; //This is the lowest temperature
unsigned long previousMillis = 0;
int solenoidpin = 3;
unsigned long interval = (unsigned long) 1000 * 60; //24 hours time interval would be 1000*60*60*24, this is a minute
void setup()
{
 Serial.begin(9600);
 irrecv.enableIRIn(); // Start the receiver
 pinMode(ledPin,OUTPUT);
 pinMode(solenoidpin, OUTPUT);
 
}
void loop() 
{

  sensorInput = analogRead(A0);        //read the analog sensor and store it
  temp = (double)sensorInput / 1024;   
  temp = temp * 5;                     
  temp = temp - 0.5;                   
  temp = temp * 100;        // Temperature in celsius
  unsigned long currentMillis = millis(); //Get the current time in ms

  Serial.print("Current Temperature in celsius: ");
  Serial.println(temp);

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
