#include <WiFi.h>
#include <HTTPClient.h>
#include "credentials.h"
#include <WiFiClientSecure.h>

boolean debug = false;

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
    WiFiClientSecure client;
    HTTPClient http;

    char requestURI[100];
    strcpy(requestURI, SERVER_ADDRESS);
    strcat(requestURI, "api/postbox/state/full");

    // Your Domain name with URL path or IP address with path
    //http.begin(client, requestURI);
    client.setInsecure();
    http.begin(client, DISCORD_WEBHOOK);
    
    // Data to send with HTTP POST
    //if (debug) { Serial.println(requestURI); }
    if (debug) { Serial.println(DISCORD_WEBHOOK); }

    // Send HTTP POST request
    http.addHeader("Content-Type", "application/json"); 
    int httpResponseCode = http.POST(DISCORD_POST_DATA);
    if (debug) { Serial.println(DISCORD_POST_DATA); }
    if (debug) { Serial.println(httpResponseCode); }
    
    // Free resources
    http.end();
    WiFi.disconnect();
  }
  else {
    if (debug) { Serial.println("WiFi Disconnected"); }
  }


  if (debug) { Serial.println("Going to sleep now..."); }
  //delay(500);
  touchSleepWakeUpEnable(T3, THRESHOLD); // Touch on pin 15
  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); // Connect to ground on pin 15 (button)
  esp_deep_sleep_start();


}

void loop() {
}
