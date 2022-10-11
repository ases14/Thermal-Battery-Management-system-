#ifndef __utilis
#define __utilis

#include <Arduino.h>
#include <_config.h>
#include <Adafruit_INA219.h>

struct DataSet
{
    float voltage_mv = 0;
    float current_mA = 0;
    float power_mw = 0;
    float temp = 0;
};

void getPowerData(DataSet *dataSet, Adafruit_INA219 *ina219);

#endif