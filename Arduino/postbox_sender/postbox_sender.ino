#include <WiFi.h>
#include <HTTPClient.h>
#include "credentials.h"

boolean debug = true;

void setup() {
  if (debug) { Serial.begin(115200); }






  WiFi.begin(WIFI_SSID, WIFI_PASS);
  if (debug) { Serial.println("Connecting"); }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (debug) { Serial.print("."); }
  }
  if (debug) { Serial.println(""); }
  if (debug) { Serial.print("Connected to WiFi network with IP Address: "); }
  if (debug) { Serial.println(WiFi.localIP()); }
  
  //Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    char requestURI[100];
    strcpy(requestURI, SERVER_ADDRESS);
    strcat(requestURI, "api/postbox/state/full");

    // Your Domain name with URL path or IP address with path
    http.begin(client, requestURI);
    
    // Data to send with HTTP POST
    if (debug) { Serial.println(requestURI); }

    // Send HTTP POST request
    int httpResponseCode = http.POST("");
    if (debug) { Serial.println(httpResponseCode); }
    // Free resources
    http.end();
    WiFi.disconnect();
  }
  else {
    if (debug) { Serial.println("WiFi Disconnected"); }
  }


  if (debug) { Serial.println("Going to sleep now..."); }
  touchSleepWakeUpEnable(T3, THRESHOLD);
  esp_deep_sleep_start();


}

void loop() {
}
