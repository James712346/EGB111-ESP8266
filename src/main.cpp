#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Prince Network";
const char* password = "***REMOVED***";


void MotorControl(int Motor, int Speed){
  int Forward[2] = {0, 14};
  int Backward[2] = {4, 12};
  if (Speed > 0){
    analogWrite(Backward[Motor], 0);
    analogWrite(Forward[Motor], PWMRANGE * (Speed * 0.01));
  } else if (Speed < 0){
    analogWrite(Forward[Motor], 0);
    analogWrite(Backward[Motor], PWMRANGE * (Speed * -0.01));
  } else {
    analogWrite(Forward[Motor], 0);
    analogWrite(Backward[Motor], 0);
  }
}

void ConnectToWifi(){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
}
void setup() {
  Serial.begin(115200);

  pinMode(0, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(12, OUTPUT);
  ConnectToWifi();
}

void AskServer(String url, int motor){
  HTTPClient http;

  http.begin(url.c_str());

  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    Serial.println(http.getString().toInt());
    MotorControl(motor, http.getString().toInt());
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    AskServer("http://egb111-server.jamesprince.me/get/motor/1/", 0);
    AskServer("http://egb111-server.jamesprince.me/get/motor/2/", 1);
  } else {
    ConnectToWifi();
  }
  delay(500);
}
