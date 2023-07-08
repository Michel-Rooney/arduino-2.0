#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "NetOnda=ITAREMA";
const char WIFI_PASSWORD[] = "Rooney06";

String HOST_NAME = "http://192.168.3.11:8000/";
String PATH_NAME = "arduino/heart_rate/?";
String USER_CODE = "code=316fc6ec40511933dc2c232a470144b24a18f22e5d26d5901b4f311b1e4da84b";
String queryString = "&beat=10";

int value = 1;

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
}

void loop() {
  HTTPClient http;

  char buf[100];
  sprintf(buf, "&beat=%d", value);
  value = value + 1;
  queryString = buf; 
  
  queryString = 
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
