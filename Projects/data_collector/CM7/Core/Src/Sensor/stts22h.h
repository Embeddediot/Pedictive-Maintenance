#ifndef STTS22H_H
#define STTS22H_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32h7xx_hal.h" // Include your specific HAL header

typedef struct {
    I2C_HandleTypeDef *i2c_handle;
    uint16_t address;
} STTS22H;

bool STTS22H_Initialize(STTS22H *sensor);
bool STTS22H_ReadTemperature(STTS22H *sensor, float *temperature);

bool STTS22H_WriteRegister(STTS22H *sensor, uint8_t reg, uint8_t value);
bool STTS22H_ReadRegister(STTS22H *sensor, uint8_t reg, uint8_t *value);
bool STTS22H_ReadRegisters(STTS22H *sensor, uint8_t reg, uint8_t *buffer, uint16_t length);

#define WHO_AM_I_REG 0x01
#define WHO_AM_I_VAL 0xA0
#define TEMP_L 0x02
#define TEMP_H 0x03
#define CONFIG 0x04

#define STTS22H_ADDRESS (0x4A << 1) // Replace with the actual I2C address of your sensor

#endif // STTS22H_H
