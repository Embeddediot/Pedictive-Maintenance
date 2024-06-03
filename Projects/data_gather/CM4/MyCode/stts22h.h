#ifndef STTS22H_H
#define STTS22H_H

#include <stdint.h>

class STTS22H {
public:
    STTS22H();
    bool initialize();
    bool readTemperature(float &temperature);

private:
    bool writeRegister(uint8_t reg, uint8_t value);
    bool readRegister(uint8_t reg, uint8_t &value);
    bool readRegisters(uint8_t reg, uint8_t *buffer, uint16_t length);

    static const uint8_t WHO_AM_I_REG = 0x01;
    static const uint8_t WHO_AM_I_VAL = 0xA0;
    static const uint8_t TEMP_L = 0x02;
    static const uint8_t TEMP_H = 0x03;
    static const uint8_t CONFIG = 0x04;

    static const uint16_t SENSOR_ADDRESS = 0x4A << 1; // Replace with the actual I2C address of your sensor
};

#endif // STTS22H_H
