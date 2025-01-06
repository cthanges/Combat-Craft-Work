#include <Wire.h>
#include <Adafruit_AHT10.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

Adafruit_AHT10 aht;
const int chipSelect = 5; // Modify this with our CS pin number
File dataFile;

#define EEPROM_SIZE 512

void setup() {
  Serial.begin(9600);
  if (!aht.begin()) {
    Serial.println("Could not find AHT10 sensor!");
    while (1) delay(10);
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("Card initialization failed!");
  } else {
    Serial.println("Card initialized.");
  }

  EEPROM.begin(EEPROM_SIZE);
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

  if (SD.begin(chipSelect)) {
    writeDataToCSV(dataString);
  } else {
    Serial.println("SD card error. Logging to EEPROM.");
    logDataToEEPROM(temp.temperature, humidity.relative_humidity);
  }
  delay(1000);
}

void writeDataToCSV(String data) {
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
  }
}

void logDataToEEPROM(float temperature, float humidity) {
  int addr = 0;
  EEPROM.put(addr, temperature);
  addr += sizeof(temperature);
  EEPROM.put(addr, humidity);
  addr += sizeof(humidity);
  EEPROM.commit();
}

String getTimeStamp() {
  // Placeholder function
  // Need to replace with actual timestamp generation code
  return "2024-04-13 12:34:56";
}