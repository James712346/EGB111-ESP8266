#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "James_iPhone";
const char* password = "PasswordsAreCool"; //There you go github, you can connect to my localhost if you ever meet me in rl


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
  digitalWrite(2, LOW);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(2, HIGH);
}
void setup() {
  Serial.begin(115200);

  pinMode(0, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, OUTPUT);
  ConnectToWifi();
}

void AskServer(String url, int motor){
  HTTPClient http;

  http.begin(url.c_str());

  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    MotorControl(motor, http.getString().toInt());
  }
  else {
    Serial.print("Error code: ");
    digitalWrite(2, LOW);
    Serial.println(httpResponseCode);
    delay(500);
    digitalWrite(2, HIGH);
  }

  http.end();
}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    AskServer("http://egb111.jamesprince.me/get/motor/1/", 0);
    AskServer("http://egb111.jamesprince.me/get/motor/2/", 1);
  } else {
    ConnectToWifi();
  }
  delay(500);
}
