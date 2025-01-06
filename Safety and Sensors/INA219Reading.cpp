#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219; // Create INA219 object

void setup() {
  // Start serial communication
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Wait for serial port to connect
  }

  // Initialize the INA219 sensor
  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip...");
    while (1) {
      delay(10);
    }
  }
  Serial.println("INA219 Sensor Initialized!");

  // Optionally calibrate the sensor
  // ina219.setCalibration_32V_2A(); // Use default calibration for 32V, 2A
}

void loop() {
  // Read voltage, current, and power values from INA219 sensor
  float busVoltage = ina219.getBusVoltage_V();      // Voltage across load
  float shuntVoltage = ina219.getShuntVoltage_mV(); // Voltage across shunt resistor
  float current_mA = ina219.getCurrent_mA();        // Current through shunt
  float power_mW = ina219.getPower_mW();            // Power calculation
  
  // Display readings
  Serial.print("Bus Voltage:   "); Serial.print(busVoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntVoltage); Serial.println(" mV");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println();

  delay(1000); // Delay for 1 second
}
