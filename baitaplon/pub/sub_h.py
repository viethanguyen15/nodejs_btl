import paho.mqtt.client as mqtt
from get_h import *

 
MQTT_Broker = "localhost"
MQTT_Port = 1883
Keep_Alive_Interval = 45
MQTT_Topic = "test"

def on_connect(client, userdata, flags, rc):
    if rc != 0:
        pass
        print ("Unable to connect to MQTT Broker...")
    else:
        print ("Connected with MQTT Broker: " + str(MQTT_Broker))

    client.subscribe(MQTT_Topic,0)

def on_message(client, userdata, msg):
    print ("MQTT Data Received...")
    print ("MQTT Topic: " + msg.topic)  
    print ("Data: " + str(msg.payload))

    Sensor_iot(msg.payload)

client = mqtt.Client()
client.username_pw_set(username="hamqtt",password="haha")
client.on_connect = on_connect
client.on_message = on_message
client.connect(MQTT_Broker,MQTT_Port, Keep_Alive_Interval)

client.loop_forever()
