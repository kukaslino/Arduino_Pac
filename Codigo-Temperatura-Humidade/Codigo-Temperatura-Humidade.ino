#include "DHT.h"
#include "WiFi.h"
#include <HTTPClient.h>
#define DHTPIN 4

# define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>

unsigned long previousMillis = 0;
const long interval = 30000;
const char* ssid = "Mi11";
const char* password =  "Kukaslino1";
String server = "https://pac6sensor.azurewebsites.net";

void setup() {
  Serial.begin(9600);

  dht.begin();

  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 Serial.println("Connected to the WiFi network");
}

void loop() {
  
  float h = 0.00;
 
  float t = 0.00;

  // Verifique se alguma leitura falhou e tenta novamente.
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha de leitura do sensor DHT!"));
    return;
  }
  else{

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {

      previousMillis = currentMillis;

      h = dht.readHumidity();

      t = dht.readTemperature();

      Serial.print("Temperatura em Celsius: ");
      Serial.println(t);
      Serial.print("Humidade relativa do ar: ");
      Serial.println(h);

      HTTPClient http;

      String serverPath = server + "/sensor?Humidity=" + h + "&Temperature=" + t + "&API_KEY=pac6";

      http.begin(serverPath.c_str());

      int httpResponseCode = http.GET();

      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    
    }

  }
  
}