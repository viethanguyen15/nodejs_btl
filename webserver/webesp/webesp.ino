#include "DHT.h"
#include <Adafruit_Sensor.h>
#define DHTPIN 4 //khai bao chan data GPIO4 = D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <ESP8266WiFi.h>

const char* ssid = "264A";
const char* password = "12345678";

WiFiServer server(80);
int led = D1;
void setup() {
  //khoi tao cong serial baud       
  Serial.begin(115200);
  //pinMode(2, OUTPUT);
  //pinMode(12, OUTPUT);
  
  pinMode(led, OUTPUT);

  dht.begin();
}
void loop() {
  Serial.print("Ket noi toi mang ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("Da ket noi WiFi");
  server.begin();
  Serial.println("Khoi dong Server");
  
  // In ra dia chi IP
  Serial.println(WiFi.localIP());

  WiFiClient client = server.available(); 
  if (!client) {
      return;
    }

  Serial.println("new client");
  while(!client.available()) {
       delay(1);
    }
   /*if (req.indexOf("/off") != -1){
      Serial.println("GPIO 13 off");
      output13 = "off";
      digitalWrite(13, LOW);
   }
   if (req.indexOf("/on") != -1){
      Serial.println("GPIO 13 on");
      output13 = "on";
      digitalWrite(13, HIGH);
   }*/
  int a = 10;
 
  //float h = dht.readHumidity();
  //float t = dht.readTemperature();
  /*String a;
  Serial.println(analogRead(A0));
  if (analogRead(A0) <=500 )
  //if (digitalRead(5) == 1)
    a = "sang";
  else a = "toi";*/
  
   String req = client.readStringUntil('\r');
   Serial.println(req);
   client.flush();

   int value = 0;
   if(req.indexOf("/LED=ON") != -1) {
    digitalWrite(led, HIGH);
    value = 1;
  }
  if(req.indexOf("/LED=OFF") != -1) {
    digitalWrite(led, LOW);
    value = 0;
  }
 

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s +="<style type=\"text/css\">";
    s+=".button1{";
      s+="display: block";
      s+="width: 115px";
      s+="height: 25px";
      s+="background-color: #4E9CAF";
      s+="padding: 10px";
      s+="text-align: center";
      s+="border-radius: 5px";
      s+="color: white";
      s+="font-weight: bold";
    s+="}";
  s +="</style>";
  s += "<meta http-equiv=\"refresh\" content=\"120\" />";
  s += "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\">";
  s += "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\"></script>";
  s += "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\"></script>";
  s += "</head>";

    s+="<nav class=\"navbar navbar-expand-md bg-dark navbar-dark\">";
      s+="<a class=\"navbar-brand\" href=\"#\">Thuc Hanh Chuyen Sau</a>";
      s+="<button class=\"navbar-toggler\" type=\"button\" data-toggle=\"collapse\" data-target=\"#collapsibleNavbar\">";
        s+="<span class=\"navbar-toggler-icon\"></span>";
      s+="</button>";
      s+="<div class=\"collapse navbar-collapse\" id=\"collapsibleNavbar\">";
        s+="<ul class=\"navbar-nav\">";
          s+="<li class=\"nav-item\">";
            s+="<a class=\"nav-link\" href=\"#\">IoT System</a>";
          s+="</li>";
          s+="<li class=\"nav-item\">";
            s+="<a class=\"nav-link\" href=\"#\">Categories</a>";
          s+="</li>";
          s+="<li class=\"nav-item\">";
            s+="<a class=\"nav-link\" href=\"#\">Products</a>";
          s+="</li>"; 
        s+="</ul>";

        s+="<form class=\"form-inline my-2 my-lg-0\">";
          s+="<input class=\"form-control mr-sm-2\" type=\"search\" placeholder=\"Search\" aria-label=\"Search\">";
          s+="<button class=\"btn btn-outline-success my-2 my-sm-0\" type=\"submit\">Search</button>";
        s+="</form>";
        
        s+="<ul class=\"navbar-nav\">";
          s+="<li class=\"nav-item\">";
            s+="<a class=\"nav-link\" href=\"#\">Log in</a>";
          s+="</li>";
          s+="<li class=\"nav-item\">";
            s+="<a class=\"nav-link\" href=\"#\">Log out</a>";
          s+="</li>";  
        s+="</ul>";

        s+="<form class=\"form-inline my-2 my-lg-0\">";
          s+="<button class=\"btn btn-success my-2 my-sm-0\" type=\"submit\">Sign up</button>";
        s+="</form>";     
      s+="</div>"; 
    s+="</nav>";
    
s+="<div style=\"background-color : #A9A9A9; width: 900px; height: 500px; margin: 0px auto;\">";
  s+="<div id=\"demo\" class=\"carousel slide\" data-ride=\"carousel\">";
    s+="<ul class=\"carousel-indicators\">";
      s+="<li data-target=\"#demo\" data-slide-to=\"0\" class=\"active\"></li>";
      s+="<li data-target=\"#demo\" data-slide-to=\"1\"></li>";
      s+="<li data-target=\"#demo\" data-slide-to=\"2\"></li>";
    s+="</ul>";
  
    s+="<div class=\"carousel-inner\">";
      s+="<div class=\"carousel-item active\">";
        s+="<img src=\"http://kbcs.in:8080/iot/img/iotproject2.jpg\" alt=\"iot system\" width=\"900\" height=\"500\">";
      s+="</div>";
      s+="<div class=\"carousel-item\">";
        s+="<img src=\"http://www.geekstips.com/wp-content/uploads/2017/10/ESP32-complete-review-and-programming-tutorial.jpg\" alt=\"esp8266\" width=\"900\" height=\"500\">";
      s+="</div>";
      s+="<div class=\"carousel-item\">";
        s+="<img src=\"http://kbcs.in:8080/iot/img/iotproject.png\" alt=\"smarthome\" width=\"900\" height=\"500\">";
      s+="</div>";
    s+="</div>";

    s+="<a class=\"carousel-control-prev\" href=\"#demo\" data-slide=\"prev\">";
      s+="<span class=\"carousel-control-prev-icon\"></span>";
    s+="</a>";
    s+="<a class=\"carousel-control-next\" href=\"#demo\" data-slide=\"next\">";
      s+="<span class=\"carousel-control-next-icon\"></span>";
    s+="</a>";

  s+="</div>";
 s+="</div>";
s+="<div>";

s+="<h1 style=\"text-align:center; color: green;\">About IoT</h1>";
s+="<div style=\"text-align:center;\">There are billions of devices in homes, factories, oil wells, hospitals,</div>";
s+="<div style=\"text-align:center;\">cars, and thousands of other places. With the proliferation of devices,</div>";
s+="<div style=\"text-align:center;\">you increasingly need solutions to connect them, and collect, store, and analyze device data.</div>";  
s+="<h2 style=\"color: #ADD8E6; margin-left: 150px;\">Show Data</h2>";
s+="<div class=\"container p-4\">";
  s+="<div class=\"row\">";
    s+="<div class=\"col-md-8\">";
      s+="<table class=\"table text-center\">";
        s+="<thead class=\"thead-dark\">";
          s+="<tr>";
            s+="<td style=\"background-color: green; color: #FFFFFF; border-right: 1px solid #ddd;\">nhiet do</td>";
            s+="<td style=\"background-color: green; color: #FFFFFF;\">do am</td>";
          s+="</tr>";
         s+="</thead>";
          s+="<tbody>";
           s+="<tr>"; 
            s+="<td>" + String(a) +"</td>";
            //s+="<td>" + String(h) +"</td>";
           s+="</tr>";    
        s+="</tbody>";      
      s+="</table>";
    s+="</div>";
  s+="</div>";
s+="</div>";

/*s += "<div class=\"row\">";
  s += "<div class=\"col-md-5\"><input class=\"btn btn-primary\" type=\"button\" value=\"BAT LED\" onclick=\"on()\"></div>";
  s += "<div class=\"col-md-5\"><input class=\"btn btn-danger\" type=\"button\" value=\"TAT LED\" onclick=\"off()\"></div>";
  s += "</div>";
  s += "<script>function on() {$.get(\"/on\");}</script>";
  s += "<script>function off() {$.get(\"/off\");}</script>";
  s+="<p>trang thai den</p>";
  */
  /*if(value == 0){
      s+="<p>Tat</p>";
    }
  if(value == 1){
      s+="<p>den sang</p>";
    }*/
    s+="<style type=\"text/css\">";
      s+=".b1";
      s+="{";
        s+="font-size: 25px;";
        s+="text-decoration: none;";
        s+="display: block;";
        s+="background-color: green;";
        s+="width: 70px;";
        s+="height: 47px;";
        s+="text-align: center;";
        s+="padding: 5px;";
        s+="border-radius: 8px;";
        s+="color: #FFFFFF;";
      s+="}";

      s+=".b1:hover";
      s+="{";
        s+="background-color: #87CEFA;";
      s+="}";

      s+=".b1:focus{";
        s+="background-color: red;";
      s+="}";

      s+=".b2";
      s+="{";
        s+="font-size: 25px;";
        s+="text-decoration: none;";
        s+="display: block;";
        s+="background-color: #9ACD32;";
        s+="width: 70px;";
        s+="height: 47px;";
        s+="text-align: center;";
        s+="padding: 5px;";
        s+="border-radius: 8px;";
        s+="color: #FFFFFF;";
      s+="}";

      s+=".b2:hover";
      s+="{";
        s+="background-color: #FFFF00;";
      s+="}";

      s+=".b2:focus{";
        s+="background-color: #C71585;";
      s+="}";
    s+="</style>";
  s+="<div>";
    s+="<center>LED: <a href=\"/LED=ON\" class=\"b1\">ON</a></center><br>";
    if (value == 1){
        s+="<p style=\"color: green; text-align: center; font-size: 20px;\">trang thai: Led ON</p>";
      }
    s+="<center>LED: <a href=\"/LED=OFF\"class=\"b2\">OFF</a></center><br>";
    if(value == 0) {
        s+="<p style=\"color: #696969; text-align: center; font-size: 20px;\">trang thai: Led OFF</p>";
      }
    //if(value == 1){
      //s+="<p style=\"text-align:center;\">bat led</p>";
    //}
    //else {
      //s+="<p style=\"text-align:center;\">tat led</p>";
    //}
  s+="</div>";
  /*s+="width: 115px";
      s+="height: 25px";
      s+="background-color: #4E9CAF";
      s+="padding: 10px";
      s+="text-align: center";
      s+="border-radius: 5px";
      s+="color: white";
      s+="font-weight: bold";
   */      
   
  // Gui phan hoi toi client (o day la giao dien web)
  client.print(s);
  delay(1);
  Serial.println("Client da thoat");
  
}
