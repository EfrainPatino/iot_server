#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "ALIX";
const char* pass = "36546921";

const char* host = "192.168.1.58";

String json = "{\"status\":\"ok\",\"user\":\"efrain\",\"password\":\"123456\",\"espID\":\"secretID_1\",\"state\":\"init\"}";  // Json Format {\"VALUE1\":\XXXX\",\"VALUE2\":\YYYY\",\"VALUE3\":\ZZZZ\", ...};

String payload;
int httpCode;
int Output = 3;

long previousMillis = 0;
long interval = 1000;

WiFiClient client;

//byte relON[] = {0xA0, 0x01, 0x01, 0xA2};  //Hex command to send to serial for open relay
//byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1}; //Hex command to send to serial for close relay

void setup() {

  Serial.begin(115200); //9600 para modulos con driver serial
  pinMode(0, OUTPUT);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
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

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {

    previousMillis = currentMillis;

    HTTPClient http;
    http.begin("http://192.168.1.58:5000/api/esp/refresh");
    http.addHeader("Content-Type", "application/json");
    httpCode = http.POST(json);

    payload = http.getString();

    DynamicJsonDocument doc(356);
    deserializeJson(doc, payload);
    const String status = doc["status"];
    const String user = doc["user"];
    const String password = doc["password"];
    const String espID = doc["espID"];
    const bool state = doc["state"];


    if ( state == true && status == "ok") {
      Serial.println("Server connection successful, State: On");
      Output = 1;
      digitalWrite(0, Output);
      json = "{\"status\":\"ok\",\"user\":\"efrain\",\"password\":\"123456\",\"espID\":\"secretID_1\",\"state\":\"true\"}";
    }
    else if ( state == false && status == "ok") {
      Serial.println("Server connection successful, State: Off");
      Output = 0;
      digitalWrite(0, Output);
      json = "{\"status\":\"ok\",\"user\":\"efrain\",\"password\":\"123456\",\"espID\":\"secretID_1\",\"state\":\"false\"}";
    }
    else {
      Serial.print("Server connection lost, State: ");
      if (Output == 1 ) {
        Serial.println("On");
      }
      else if (Output == 0) {
        Serial.println("Off");
      }
      else {
        Serial.println("Scaning");
      }
    }

    //    Serial.print("status: ");
    //    Serial.println(status);
    //    Serial.print("user: ");
    //    Serial.println(user);
    //    Serial.print("password: ");
    //    Serial.println(password);
    //    Serial.print("espID: ");
    //    Serial.println(espID);
    //    Serial.print("state: ");
    //    Serial.println(state);
    //    Serial.println(" ");




    //http.end();  //Close connection
  }
}
