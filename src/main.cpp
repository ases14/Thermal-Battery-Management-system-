#include <Arduino.h>
#include <_config.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

struct DataSet
{
  float voltage_mv = 0;
  float current_mA = 0;
  float power_mw = 0;
  float temp = 0;
};

bool getPowerData(DataSet dataSet)
{
  long int clock_1 = millis();

  double t_current = 0;
  double t_loadVoltage = 0;
  double t_power = 0;

  int counter = 0;

  while (millis() - clock_1 < 1000)
  {
    long int clock_2 = millis();

    float shuntvoltage = ina219.getShuntVoltage_mV();
    float busvoltage = ina219.getBusVoltage_V();

    t_current += ina219.getCurrent_mA();
    t_loadVoltage += busvoltage + (shuntvoltage / 1000);
    t_power += ina219.getPower_mW();

    counter++;

    long int clock_duration_2 = millis() - clock_2;
    int wait = int((float(1000) / Sample_Rate)) - clock_duration_2;
    delay(wait);
  }

  dataSet.current_mA = t_current / counter;
  dataSet.voltage_mv = t_loadVoltage / counter;
  dataSet.power_mw = t_power / counter;
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1);
  }

  uint32_t currentFrequency;

  Serial.println("Serial communication established successfully!");

  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  // if (!ina219.begin())
  // {
  //   Serial.println("Failed to find INA219 chip");
  //   while (1)
  //   {
  //     delay(10);
  //   }
  // }

  // To use a slightly lower 32V, 1A range (higher precision on amps):
  // ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  // ina219.setCalibration_16V_400mA();
}

void loop()
{
  DataSet dataSet;
  getPowerData(dataSet);
  Serial.println(dataSet.temp);
  delay(1000);
}
