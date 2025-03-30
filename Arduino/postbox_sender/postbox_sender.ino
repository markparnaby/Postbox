#include <WiFi.h>
#include <HTTPClient.h>
#include "credentials.h"

void setup() {
  Serial.begin(115200); 

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  
  HTTPClient http;
  String serverPath = SERVER + "api/postbox/state/full";

  Serial.print("Sending the following as a POST request:");
  Serial.println(serverPath.c_str());

  http.begin(serverPath.c_str());
  int httpResponseCode = http.POST();

  
  Serial.print("Response:");
  Serial.println(httpResponseCode);
}

void loop() {
}
