#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

const char* ssid = "........";
const char* password = "........";
const char* host = "0.0.0.0";
const int httpsPort = 8000;

int Rx=D9;

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      int message= analogRead(Rx);
      Serial.println(message);
      char smessage[5];
      itoa(message, smessage, 10);
      http.begin("http://192.168.1.88:8085/hello");
      http.addHeader("Content-Type", "text/plain");
      int httpCode = http.POST(smessage);
      
      String payload = http.getString();
      http.end();  //Close connection
 
    }
}
