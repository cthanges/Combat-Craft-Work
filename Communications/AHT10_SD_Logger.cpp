#include <Wire.h>
#include <Adafruit_AHT10.h>
#include <SPI.h>
#include <SD.h>

Adafruit_AHT10 aht;
const int chipSelect = 5; // Modify this with our CS pin number
File dataFile;

void setup() {
  Serial.begin(9600);
  if (!aht.begin()) {
    Serial.println("Could not find AHT10 sensor!");
    while (1) delay(10);
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("Card initialization failed!");
    return;
  }
  Serial.println("Card initialized.");

  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Timestamp, Temperature (C), Humidity (%)");
    dataFile.close();
  }
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);  // Populate temp and humidity objects with new data

  String dataString = "";
  dataString += getTimeStamp();
  dataString += ",";
  dataString += String(temp.temperature);
  dataString += ",";
  dataString += String(humidity.relative_humidity);

  writeDataToCSV(dataString);
  delay(1000);
}

void writeDataToCSV(String data) {
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  }
}

String getTimeStamp() {
  // Placeholder function
  // Need to replace with actual timestamp generation code
  return "2024-04-13 12:34:56";
}
