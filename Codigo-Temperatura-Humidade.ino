#include "DHT.h"
#define DHTPIN 2     // Pino digital sensor DHT

// Escolha o tipo de sensor!
# define DHTTYPE DHT11     // DHT 11
//# define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
//# define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx teste!"));

  dht.begin();

}

void loop() {
  
  float h = dht.readHumidity();
 
  float t = dht.readTemperature();

  // Verifique se alguma leitura falhou e tenta novamente.
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha de leitura do sensor DHT!"));
    return;
  }
  
}
