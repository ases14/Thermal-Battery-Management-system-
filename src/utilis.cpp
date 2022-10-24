#include <utilis.h>
// #include <_config.h>
// #include <Arduino.h>
// #include <Adafruit_INA219.h>

double getTemparature(int ANALOG_PIN)
{
    double temp;
    int data = analogRead(ANALOG_PIN);
    temp = log(10000.0 * ((1024.0 / data - 1)));
    temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp)) * temp); // in kelvin
    temp = temp - 273.15; //in celceus
    return temp;
}

void updatePowerData(DataSet *dataSet, Adafruit_INA219 *ina219)
{
    long int clock_1 = millis();

    double t_current = 0;
    double t_loadVoltage = 0;
    double t_power = 0;

    int counter = 0;

    while (millis() - clock_1 < 1000)
    {
        long int clock_2 = millis();

        float shuntvoltage = ina219->getShuntVoltage_mV();
        float busvoltage = ina219->getBusVoltage_V();

        t_current += ina219->getCurrent_mA();
        t_loadVoltage += busvoltage + (shuntvoltage / 1000);
        t_power += ina219->getPower_mW();

        counter++;

        long int clock_duration_2 = millis() - clock_2;
        int wait = int((float(1000) / Sample_Rate)) - clock_duration_2;
        delay(wait);
    }

    dataSet->current_mA = -1 * t_current / counter;
    dataSet->voltage_mv = t_loadVoltage / counter;
    dataSet->power_mw = t_power / counter;
}
