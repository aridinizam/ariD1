#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
const char* ssid = "ssid";
const char* password = "password";
 
ESP8266WebServer server(80);
 
/*/ defines pins numbers trigger and echo
const int trigPin = 14;  //Digital port D5
const int echoPin = 12;  //Digital port D6
*/ 
/*----------------------------------------- defines variables
long duration;
float distance;
float Mdistance;
 */
//const int led = LED_BUILTIN;
 
void setup(void){
 // pinMode(led, OUTPUT);
 // pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
 // pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", webserver);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();
}


void webserver() {
  
  int outputpin= A0; 
  int analogValue = analogRead(outputpin);
  float millivolts = (analogValue/1024.0) * 5000; //3300 is the voltage provided by NodeMCU
  float suhu = (millivolts/10) + 5 - 17.76;
  
  String content = "<html> <head> <meta http-equiv='refresh' content='1'> </head><body>";
  content += suhu;

  server.send(200, "text/html", content);
}
 
void handleNotFound(){

  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

//hello yong
