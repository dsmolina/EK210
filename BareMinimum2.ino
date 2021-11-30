#include <LowPower.h>
#define LED 2
int sensePin = A0;  
int sensorInput;    
double temp;        
const int hot = 43; //This is the highest temperature
const int cold = -23; //This is the lowest temperature
unsigned long previousMillis = 0;
unsigned long interval = (unsigned long) 1000 * 60 * 60 * 24; //24 hours time interval in ms

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);      
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorInput = analogRead(A0);        //read the analog sensor and store it
  temp = (double)sensorInput / 1024;   
  temp = temp * 5;                     
  temp = temp - 0.5;                   
  temp = temp * 100;        // Temperature in celsius
  unsigned long currentMillis = millis(); //Get the current time in ms

  Serial.print("Current Temperature in celsius: ");
  Serial.println(temp);

  if (temp <= cold || temp >= hot || currentMillis - previousMillis >= interval)
  {
  digitalWrite(LED, HIGH);
  previousMillis = currentMillis; //Timer will reset because the rats were released at one particular circumstance, the amount of time passed is now zero.
  delay(1000);  
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); //Sleep for 8 seconds to lower the battery comsumption
  delay(1000);  
  }
  else
  {
  digitalWrite(LED, LOW);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  delay(1000);  
  }
}
