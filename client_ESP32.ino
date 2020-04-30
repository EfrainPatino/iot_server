#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "ALIX";
const char* password = "36546921";

const char* host = "http://192.168.1.58";

const String json = "{\"user\":\"efrain\",\"password\":\"123456\",\"espID\":\"secretID\",\"state\":\"true\"}";  // Json Format {\"VALUE1\":\XXXX\",\"VALUE2\":\YYYY\",\"VALUE3\":\ZZZZ\", ...};

String payload;
int httpCode;

void setup() {
  Serial.begin(115200); 
  Serial.println();
  Serial.println("Connecting to");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  HTTPClient http;
  
  http.begin("http://192.168.1.58:4000/api/esp/refresh");
  http.addHeader("Content-Type", "application/json");
  httpCode = http.POST(json);
  payload = http.getString();    

  DynamicJsonDocument doc(256);
  deserializeJson(doc, payload);

  const String status = doc["status"]; 
  const bool esp_01 = doc["esp_01"]; 
  const bool esp_02 = doc["esp_02"]; 
  const bool esp_03 = doc["esp_03"];

//  Serial.print("status: ");
//  Serial.println(status);
//  Serial.print("esp_01: ");
//  Serial.println(esp_01);
//  Serial.print("esp_02: ");
//  Serial.println(esp_02);
//  Serial.print("esp_03: ");
//  Serial.println(esp_03);
//  Serial.println(" ");

delay(1000);
}
