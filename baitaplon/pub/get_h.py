import MySQLdb
import json
#============================================================================================
def Sensor_iot(jsonData):
	print(jsonData)
	json_Dict = json.loads(jsonData)
	Temperature = json_Dict['temp']
	Humidity = json_Dict['hum']
	Gas = json_Dict['mq2']
	db = MySQLdb.connect("localhost","sensor3user","123456","sensor3")
	cursor = db.cursor()
	sql = """INSERT INTO thcs_iot(Temp, Hum, Gas, Time) VALUES(%s,%s,%s,now())""" %(Temperature, Humidity, Gas)
	cursor.execute(sql)
	db.commit()
	print("Sensor created new value")
	
	db.close()
