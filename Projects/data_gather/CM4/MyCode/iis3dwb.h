/*
 * iis3dwb.h
 *
 *  Created on: Jun 3, 2024
 *      Author: bjs
 */
#ifndef IIS3DWB_H
#define IIS3DWB_H

#include <stdint.h>

class IIS3DWB {
public:
    IIS3DWB();
    bool initialize();
    bool readAcceleration(float &x, float &y, float &z);

private:
    bool writeRegister(uint8_t reg, uint8_t value);
    bool readRegister(uint8_t reg, uint8_t &value);
    bool readRegisters(uint8_t reg, uint8_t *buffer, uint16_t length);

    static const uint8_t WHO_AM_I_REG = 0x0F;
    static const uint8_t WHO_AM_I_VAL = 0x6B;
    static const uint8_t CTRL1_XL = 0x10;
    static const uint8_t OUTX_L_XL = 0x28;
    static const uint8_t OUTX_H_XL = 0x29;
    static const uint8_t OUTY_L_XL = 0x2A;
    static const uint8_t OUTY_H_XL = 0x2B;
    static const uint8_t OUTZ_L_XL = 0x2C;
    static const uint8_t OUTZ_H_XL = 0x2D;
};

#endif // IIS3DWB_H




