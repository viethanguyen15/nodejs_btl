var express = require("express");// include pakage express
var app = express();
var server = require("http").Server(app);
var io =require("socket.io")(server);
var mysql = require('mysql');
var mqtt  = require('mqtt');
var options = {
  username: 'hamqtt',
  password: 'haha'
}

var client = mqtt.connect('mqtt://localhost:1883/', options);
var iot_toppic = 'thcstt';

var arrUsers = [];
function publish(topic,msg,options){
	
	if (client.connected == true){
		console.log("publishing",msg);
		client.publish(topic,msg,options);
	}
}
io.on("connection", function(socket){
	console.log("co client ket noi");
	console.log("User: " + socket.id + " connection!");
socket.on("disconnect", function(){
    console.log("User: " + socket.id + " disconnected!");
  });
socket.on("control-led", function(data){
	//console.log(data);
	publish(iot_toppic, data.toString(), options);
	//console.log("got it");
  });

  	socket.on("client-send-Username", function(data){
  		//console.log(data);
  		if(arrUsers.indexOf(data) >= 0){
  		//fail
  			socket.emit("server-send-thatbai");
  		}	
  		else{
  		//complete
  			arrUsers.push(data);
  			socket.Username = data;
  			socket.emit("server-send-thanhcong", data);
  			io.sockets.emit("server-send-danhsach", arrUsers);

  		}
  	});
  	socket.on("logout", function(){
  		arrUsers.splice(
  			arrUsers.indexOf(socket.Username), 1
  		);
  		socket.broadcast.emit("server-send-danhsach", arrUsers);
  	});
  	socket.on("user-send-message", function(data){
  		io.sockets.emit("server-send-message", {user: socket.Username, msg: data});
  	});
  	socket.on("user-dang-go-chu", function(){
  		var s = socket.Username + " is typing";
  		io.sockets.emit("user-typing", s);
  	})
  	socket.on("user-ngung-go-chu", function(){
  		//console.log(socket.Username + " ngung go chu");
  		io.sockets.emit("user-stop");
  	});

});

app.use(express.static("./public"));
app.set("view engine", "ejs");
app.set("views", "./views");

server.listen(8000, function(){
	console.log('http://localhost:8000/');	
});

app.get("/", function(req, res){
    res.render("index");
});

var connection = mysql.createConnection({
  host     : "localhost",
  user     : "sensor3user",
  password : "123456",
  database : "sensor3"
});

connection.connect(function(error) {
	if (error) {
		console.log('error connecting:');
		return;	
	}
	else{
		console.log('connected mysql');
	}
});

app.get("/data", function(req, res){
	connection.query("SELECT * FROM thcs_iot WHERE id = (SELECT max(id) FROM thcs_iot)", function(error, result){
	if(error) throw error;
	connection.query("SELECT max(Temp) as Temperature from thcs_iot", function(error, maxtemp){
		if(error) throw error;
		connection.query("SELECT max(Hum) as Humidity from thcs_iot", function(error, maxhum){
			if(error) throw error;
					connection.query("SELECT min(Temp) as Temperature from thcs_iot", function(error, mintemp){
						if(error) throw error;
						connection.query("SELECT min(Hum) as Humidity from thcs_iot", function(error, minhum){
							if(error) throw error;
						var array = {
							result: result[0],
							maxtemp: maxtemp[0], maxhum: maxhum[0],
							mintemp: mintemp[0], minhum: minhum[0]
						};
						res.json(array);
			
						
					});
				});
			});
		});	
	})
});