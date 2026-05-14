#include <DHT.h>
#include <SD.h>
#include <SPI.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define SD_CS_PIN 10

DHT dht(DHTPIN, DHTTYPE);
File dataFile;

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD Card failed");
    return;
  }
  Serial.println("Weather Logger Started");
  
  dataFile = SD.open("weather.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Time,Temperature,Humidity");
    dataFile.close();
  }
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Sensor Error");
    return;
  }
  
  // Log to Serial Monitor
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print("°C, Hum: "); Serial.print(hum); Serial.println("%");
  
  // Log to SD Card
  dataFile = SD.open("weather.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(millis()/1000); dataFile.print(",");
    dataFile.print(temp); dataFile.print(",");
    dataFile.println(hum);
    dataFile.close();
  }
  
  delay(5000); // Log every 5 seconds
}
