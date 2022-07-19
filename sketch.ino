// please check the video
// https://www.youtube.com/watch?v=l8KpBxnYID4

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "ssid";
const char* password = "Password";

MDNSResponder mdns;

String Domain = "home";

ESP8266WebServer server(80);

void handleRoot() {
 server.send(200, "text/html", 
"<!DOCTYPE html>" \
"<html>" \
"<head>" \
"<title>home</title>" \
"</head>" \
"<body>" \
"<h1>Home Automation</h1>" \
"<h2>Switch1: status</h2>" \
"<p><a href=\"/Switch1ON\"><button class=\"button\">ON</button></a><a href=\"/Switch1OFF\"><button class=\"button\">OFF</button></a></p>" \
"</body>" \
"</html>" \
);
}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 

  if(mdns.begin(Domain)){
    Serial.println("MDNS Started: " + Domain + ".local/");
  }
 
  server.on("/", handleRoot);     

  server.begin();                 
  Serial.println("HTTP server started");
}

void loop(void){
  mdns.update();
  server.handleClient();  
}