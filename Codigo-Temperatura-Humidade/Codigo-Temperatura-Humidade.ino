#include "DHT.h"
#define DHTPIN 2     // Pino digital sensor DHT

// Escolha o tipo de sensor!
# define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>

unsigned long previousMillis = 0;
const long interval = 30000;

void setup() {
  Serial.begin(9600);

  dht.begin();

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

      t = dht.readHumidity();

      h = dht.readTemperature();

      Serial.print("Temperatura em Celsius: ");
      Serial.println(h);
      Serial.print("Humidade relativa do ar: ");
      Serial.println(t);

    }

  }
  
}
