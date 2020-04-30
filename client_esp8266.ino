#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "ALIX";
const char* password = "36546921";

const char* host = "192.168.1.58";

const String json = "{\"user\":\"efrain\",\"password\":\"123456\",\"espID\":\"secretID\",\"state\":\"true\"}";  // Json Format {\"VALUE1\":\XXXX\",\"VALUE2\":\YYYY\",\"VALUE3\":\ZZZZ\", ...};

String payload;
int httpCode;

WiFiClient client;

byte relON[] = {0xA0, 0x01, 0x01, 0xA2};  //Hex command to send to serial for open relay
byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1}; //Hex command to send to serial for close relay


void setup() {

Serial.begin(9600);
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
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

//Serial.println(httpCode);   statusCode
//Serial.println(payload);    

DynamicJsonDocument doc(256);
deserializeJson(doc, payload);

const String status = doc["status"]; // "OK"
const bool esp_01 = doc["esp_01"]; // "false"
const bool esp_02 = doc["esp_02"]; // "true"
const bool esp_03 = doc["esp_03"];

//Serial.print("status: ");
//Serial.println(status);
//Serial.print("esp_01: ");
//Serial.println(esp_01);
//Serial.print("esp_02: ");
//Serial.println(esp_02);
//Serial.print("esp_03: ");
//Serial.println(esp_03);
//Serial.println(" ");

if (esp_01) {
  //Serial.println("prendi");
  Serial.write(relON, sizeof(relON));
}
else {
  //Serial.println("apague");
  Serial.write(relOFF, sizeof(relOFF));
}
 
http.end();  //Close connection
  
delay(1000);  //GET Data at every 5 seconds

}
