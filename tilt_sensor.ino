
const int DO1=2;

 
void setup() {
    pinMode(DO1, INPUT);
    Serial.begin(9600);
}
 
void loop() {
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
}
