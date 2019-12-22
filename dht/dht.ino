#include "DHT.h"
#include <Adafruit_Sensor.h>
#define DHTPIN 18
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin();
  //pinMode(18, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Do am la: "); 
  Serial.println(float(h));
  Serial.print(" Nhiet do la: ");
  Serial.println(float(t));
  //Serial.print("anh sang la: ");
  //Serial.println(analogRead(A0));
  //Serial.print("mq2 la: ");
  //Serial.println(analogRead(A0));
//  if(analogRead(A0) < 500){
//      digitalWrite(13, HIGH);
//    }
//  else{
//      digitalWrite(13, LOW);
//    }  
 
  delay(1000);
}
