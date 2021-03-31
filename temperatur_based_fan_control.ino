
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11


int ledPin = 10;                // LED 
int pirPin = 3;                 // PIR Out pin 
int pirStat = 0; 

int led1 =4,led2=5,led3=6;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
   pinMode(ledPin, OUTPUT);     
   pinMode(pirPin, INPUT);    
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {

  pirStat = digitalRead(pirPin); 
 if (pirStat == HIGH) {
          {
          delay(2000);
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          float f = dht.readTemperature(true);
          if (isnan(h) || isnan(t) || isnan(f)) {
            Serial.println(F("Failed to read from DHT sensor!"));
            return;
          }
        
          float hif = dht.computeHeatIndex(f, h);
          float hic = dht.computeHeatIndex(t, h, false);
        
          Serial.print(F(" Humidity: "));
          Serial.print(h);
          Serial.print(F("%  Temperature: "));
          Serial.print(t);
          Serial.print(F("C "));
          Serial.print(f);
          Serial.print(F("F  Heat index: "));
          Serial.print(hic);
          Serial.print(F("C "));
          Serial.print(hif);
          Serial.println(F("F"));
          if(t>=20 && t<=27){
            digitalWrite(led1,HIGH);
            digitalWrite(led3,LOW);
            digitalWrite(led2,LOW);
          }
          else if(t>=27 && t<35){
            digitalWrite(led2,HIGH);
            digitalWrite(led1,LOW);
            digitalWrite(led3,LOW);
          }
          else if(t>=35){
            digitalWrite(led3,HIGH);
            digitalWrite(led1,LOW);
            digitalWrite(led2,LOW);
          }
          else{
            digitalWrite(led3,LOW);
            digitalWrite(led1,LOW);
            digitalWrite(led2,LOW);
          }
          delay(5000);
          }
}
else {
  Serial.println("motion not detected");
  digitalWrite(led3,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  delay(2000);
}
}


 
