//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
//------------------------
#define FIREBASE_HOST "test-5d974-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xURW44Xcxr5Ql5sqsGo9EIGYE3r9wLyqym7JnMmD"
#define WIFI_SSID "Aziz97House"
#define WIFI_PASSWORD "Aziz#AES97"
//------------------------
FirebaseData firebaseData;
FirebaseJson json;

//------------------------

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);



  //json = Firebase.get("/").getJsonVariant().asObject();

  if (Firebase.getJSON(firebaseData, "req/active"))
  {
    //Success, then try to read the JSON payload value
    Serial.println(firebaseData.jsonString());
     Serial.println("-----------------");
  }
  else
  {
    //Failed to get JSON data at defined database path, print out the error reason
    Serial.println(firebaseData.errorReason());
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}