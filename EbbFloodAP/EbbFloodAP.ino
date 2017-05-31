#define RELAY_PIN 2
#define SENSOR_PIN A0
#define COUNT 3600
#define DELAY 1000
#define SENSOR_TIMEOUT 10
#define MAX_PUMP 10

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

const char *ssid = "Ebb Flood Controller";
const char *password = "thereisnospoon";

int counter = 0;
int pumpCounter = 0;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup() {
  //WiFi
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	WiFi.softAP(ssid, password);
	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
  //EbbFlood
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(SENSOR_PIN,INPUT);
  digitalWrite(RELAY_PIN,HIGH);
  flooding();
}

void loop() {
	server.handleClient();
  if (counter==COUNT) {
    counter = 0;
    flooding();
  } else {
    counter++;
  }
  delay(DELAY);
}

boolean checkSensor() {
  int sensor = analogRead(SENSOR_PIN);
  Serial.println(sensor);
  if(sensor>200) {
    return true;
  } else {
    return false;
  }
}

void flooding() {
  pumpCounter=0;
  digitalWrite(RELAY_PIN,LOW);
  boolean check = checkSensor();
  while (check == false) {
    check = checkSensor();
    delay(100);
    pumpCounter++;
    if(pumpCounter >= MAX_PUMP) {
      digitalWrite(RELAY_PIN,HIGH);
      sendError("Sensor Timeout");
      check = true;
    }
  }   
  digitalWrite(RELAY_PIN,HIGH);
  if (pumpCounter <= SENSOR_TIMEOUT) sendError("Sensor shorted");
  pumpCounter=0;
}

void sendError(String message) {
  while (true==true) {
    server.send(200, "text/html", message);
    server.handleClient();
  }
}

