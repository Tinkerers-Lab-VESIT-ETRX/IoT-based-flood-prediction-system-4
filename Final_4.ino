#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11
#define RainPin A2 
DHT dht(DHTPIN, DHTTYPE);
const int sensorMin = 0; 
const int sensorMax = 1024;
const int trigPin = 6;
const int echoPin = 7;

float critical_a = 39.7;
float normal_b = 100;
float max_distance = 200;

int ledA=13;

void setup() {
  // put your setup code here, to run once:
  pinMode (ledA,OUTPUT);
  pinMode(trigPin,INPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(ledA, LOW);
  
  Serial.begin(9600);
  delay(500);
   dht.begin();

  

}

void loop() {
  // put your main code here, to run repeatedly:
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

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F(",  Temperature: "));
  Serial.print(t);
  //Serial.print(F("°C "));
  //Serial.print(f);
  //Serial.print(F("°F  Heat index: "));
  //Serial.print(hic);
  //Serial.print(F("°C "));
  //Serial.print(hif);
 // Serial.println(F("°F"));


   int sensorReading = 0; //analogRead(A2)
   //int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
   Serial.print(", Rain_DetectionRange: ");
   Serial.print(sensorReading);
   

  ///switch (range)
    //{
      //case 0:
        //Serial.print("RAINING");
        //break;

      //case 1:
        //Serial.println("RAIN WARNING");
        //break;

      //case 2:
        //Serial.println("NOT RAINING");
        //break;
    //}

  delay(1000); 

  long duration, inches, m;
  pinMode(trigPin,OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = 10312;//pulseIn(echoPin, HIGH);

  inches = microsecondsToInches(duration);
  m = microsecondsToMeters(duration);
if (inches <max_distance){ Serial.print(", Distance above mean sea level: "); Serial.print(m); Serial.print(" m"); Serial.println(); delay(100); } 
if (inches >= critical_a){digitalWrite (ledA,HIGH); }
else if (inches >= normal_b){digitalWrite (ledA,LOW); } }
//Serial.println("Humidity= "+ String(h)+ ", Temperature= " + String(t)+  ", Rain_DetectionRange= " +String(sensorReading)+ ", Distance_above_MSL= " +String(inches));

long microsecondsToInches(long microseconds) {
return (microseconds / 74) / 2;
}
long microsecondsToMeters(long microseconds) {
return ((microseconds / 29) / 2)/100;}
