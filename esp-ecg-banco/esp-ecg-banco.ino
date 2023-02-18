#include <WiFi.h>
#include <HTTPClient.h>
#define sensorpin A0


const char WIFI_SSID[] = "AP02_VALLEY";
const char WIFI_PASSWORD[] = "amontada";

String HOST_NAME = "https://teste-arduino-banco.onrender.com"; // change to your PC's IP address
String PATH_NAME   = "/teste";



String header;
String valor;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(9600); 
  pinMode(34, INPUT); //Setup for leads off detection LO +
  pinMode(35, INPUT); //Setup for leads off detection LO -

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
  if((digitalRead(34) == 1)||(digitalRead(35) == 1)){ 
    valor = '!';
  } 
  else{  
    Serial.println(analogRead(sensorpin)); 
    valor = String(analogRead(sensorpin));
  }
  delay(100);

  HTTPClient http;
  String queryString = "/" + valor + "/";
  Serial.print(HOST_NAME + PATH_NAME + queryString);
  http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
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
