/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-mysql
 */

#include <WiFi.h>
#include <HTTPClient.h>

//const char WIFI_SSID[] = "Marqueza";
//const char WIFI_PASSWORD[] = "19381980";

const char WIFI_SSID[] = "NetOnda=ITAREMA";
const char WIFI_PASSWORD[] = "Rooney06";

//const char WIFI_SSID[] = "JOEL10 9678";
//const char WIFI_PASSWORD[] = "joel12344321";

//const char WIFI_SSID[] = "AP02_VALLEY";
//const char WIFI_PASSWORD[] = "amontada";

String HOST_NAME = "http://192.168.3.11:8000/"; // change to your PC's IP address
String PATH_NAME = "arduino/heart_rate/?";
String USER_CODE = "code=aa79b1970021a51c3eed9a6409d883cbcecb73896f10277a5a93900b183ae880";
String queryString = "&beat=10";

void setup() {
  Serial.begin(9600); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  HTTPClient http;
  http.begin(HOST_NAME + PATH_NAME + USER_CODE + queryString); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop() {
  HTTPClient http;
  http.begin(HOST_NAME + PATH_NAME + USER_CODE + queryString); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}
