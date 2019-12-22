#include <NTPClient.h>
#include <Arduino_JSON.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>
#include "DHT.h"


#define mqttport  1883
#define mqttuser  "hamqtt"
#define mqttpass  "haha"
#define mqtttopic "test"


#define pinlight A0
#define LEDPIN 5

const int DHTPIN = 4;
const int DHTTYPE = DHT11;

const char* ssid     = "ZTE-e55b1a";
const char* password = "98f428e5";
const char* mqttip   = "192.168.1.5";

DHT dht(DHTPIN, DHTTYPE);
WiFiClient ha;
PubSubClient client(ha);

/*---------------------------------setup wifi--------------------------------*/
void setupwifi(){
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
/*--------------------------------setup mqtt ---------------------------------*/
void setupmqtt(){
  while (!client.connected()){
    Serial.println("Dang ket noi vao QMTT!");
    if (client.connect("ESPclient",mqttuser,mqttpass)){
      Serial.println("Da ket noi thanh cong vao MQTT!");
      client.publish(mqtttopic,"ESP da ket noi");
      client.subscribe(mqtttopic);
      client.subscribe("iot_toppic");
    }else{
      Serial.println("Ket noi that bai!");
      delay(5000);
      Serial.println("Dang thu lai!");
    }
  }
}

/*callback*/
void callback(char* toppic,byte* message,unsigned int length){
  Serial.print("Topic: ");
  Serial.print(toppic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (String(toppic) == "iot_toppic") {
    Serial.print("setup led1 ");
    if (messageTemp.toInt() == 1){
      digitalWrite(LEDPIN, HIGH);
      Serial.println("led-on");
    }
    else if(messageTemp.toInt() == 0){
      digitalWrite(LEDPIN, LOW);
      Serial.println("led-off");
    }else{
      analogWrite(LEDPIN,messageTemp.toInt());
    }
    Serial.println(messageTemp);
  }
}
/*publish*/
void pubdata(){
  String temp = String(int(dht.readTemperature()));
  String hum = String(int(dht.readHumidity()));
  String light = String(int(analogRead(pinlight)));
  String payload = "{";
  payload += "\"temp\": "; payload += temp; payload += ",";
  payload += "\"hum\": "; payload += hum; payload += ",";
  payload += "\"light\": "; payload += light;
  payload += "}";
  char datapub[100];
  payload.toCharArray(datapub, 100);
  client.publish(mqtttopic, datapub);
  //delay(1000);
}
/*------------------------------------setup tong------------------------------------*/
void setup(){
  Serial.begin(115200);
  dht.begin();
  setupwifi();
  client.setServer(mqttip,mqttport);
  client.setCallback(callback);
  pinMode(LEDPIN, OUTPUT);
}
void loop(){
  if(!client.connected()){
    setupmqtt();
  }
  if(client.loop())
  client.connect("ESPclient");
  pubdata();
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  Serial.print("Anh sang: ");
//  Serial.print(analogRead(pinlight));
//  Serial.print(" Do am: ");
//  Serial.print(h);
//  Serial.print(" % ");
//  Serial.print("Nhiet do: ");
//  Serial.print(t);
//  Serial.println(" *C ");
  //delay(1000);
}
