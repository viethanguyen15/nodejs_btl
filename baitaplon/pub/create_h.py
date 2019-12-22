import MySQLdb
db = MySQLdb.connect("localhost", "sensor3user", "123456", "sensor3")
cursor = db.cursor()
sql = """CREATE TABLE thcs_iot (
		 id INT(10) PRIMARY KEY auto_increment,
		 Temp INT(3) NOT NULL,
		 Hum INT(3) NOT NULL,
		 Gas INT(5) NOT NULL,
		 Time datetime NOT NULL
	)
	"""

cursor.execute(sql)
db.close()	