#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ESP";
const char* password = "Galaxy@123";

// LED pins using GPIO numbers
const int greenLED = 5;  // GPIO5 (was D1)
const int redLED = 4;    // GPIO4 (was D2)

// LED states
bool greenState = false;
bool redState = false;

// Web server on port 80
ESP8266WebServer server(80);

// HTML content
String htmlPage() {
  String html = "<!DOCTYPE html><html><head><title>LED Control</title>";
  html += "<style>body{text-align:center;font-family:sans-serif;}";
  html += ".btn{padding:20px 40px;font-size:20px;margin:20px;border:none;border-radius:10px;cursor:pointer;}";
  html += ".green{background-color:green;color:white;}";
  html += ".red{background-color:red;color:white;}";
  html += "</style></head><body>";
  html += "<h1>ESP8266 LED Control</h1>";
  html += "<form action=\"/green\"><button class=\"btn green\">Green LED</button></form>";
  html += "<form action=\"/red\"><button class=\"btn red\">Red LED</button></form>";
  html += "</body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void toggleGreen() {
  greenState = !greenState;
  digitalWrite(greenLED, greenState);
  handleRoot();
}

void toggleRed() {
  redState = !redState;
  digitalWrite(redLED, redState);
  handleRoot();
}

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);

  // Start Wi-Fi Access Point
  WiFi.softAP(ssid, password);
  Serial.begin(115200);
  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());

  // Setup web routes
  server.on("/", handleRoot);
  server.on("/green", toggleGreen);
  server.on("/red", toggleRed);
  
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
