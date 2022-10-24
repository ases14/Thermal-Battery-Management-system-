#include <Arduino.h>
// #include <_config.h>
#include <utilis.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;
DataSet dataSet;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1);
  }

  // uint32_t currentFrequency;

  Serial.println("Success: Serial communication established!");

  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  if (!ina219.begin())
  {
    Serial.println("Failed to find INA219 chip");
    while (1)
    {
      delay(10);
    }
  }

  Serial.println("Success: Found INA219!");

  // To use a slightly lower 32V, 1A range (higher precision on amps):
  // ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  // ina219.setCalibration_16V_400mA();
}

void loop()
{
  updatePowerData(&dataSet, &ina219);

  Serial.println(dataSet.voltage_mv);
  Serial.println(dataSet.current_mA);
  Serial.println(dataSet.power_mw);
  Serial.println();
  Serial.println();
}
