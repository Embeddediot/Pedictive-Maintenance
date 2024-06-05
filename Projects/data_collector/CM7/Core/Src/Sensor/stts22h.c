#include "stts22h.h"
#include "stm32h7xx_hal.h" // Include your specific HAL header

bool STTS22H_Initialize(STTS22H *sensor) {
    uint8_t who_am_i = 0;
    if (!STTS22H_ReadRegister(sensor, WHO_AM_I_REG, &who_am_i) || who_am_i != WHO_AM_I_VAL) {
        return false;
    }
    // Additional initialization code
    return true;
}

bool STTS22H_ReadTemperature(STTS22H *sensor, float *temperature) {
    uint8_t buffer[2];
    if (!STTS22H_ReadRegisters(sensor, TEMP_L, buffer, 2)) {
        return false;
    }
    // Convert the data to temperature value (adjust the conversion as needed)
    int16_t tempRaw = (buffer[1] << 8) | buffer[0];
    *temperature = tempRaw * 0.01f; // Conversion factor for the STTS22H
    return true;
}

bool STTS22H_WriteRegister(STTS22H *sensor, uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    if (HAL_I2C_Master_Transmit(sensor->i2c_handle, sensor->address, data, 2, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    return true;
}

bool STTS22H_ReadRegister(STTS22H *sensor, uint8_t reg, uint8_t *value) {
    if (HAL_I2C_Master_Transmit(sensor->i2c_handle, sensor->address, &reg, 1, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    if (HAL_I2C_Master_Receive(sensor->i2c_handle, sensor->address, value, 1, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    return true;
}

bool STTS22H_ReadRegisters(STTS22H *sensor, uint8_t reg, uint8_t *buffer, uint16_t length) {
    if (HAL_I2C_Master_Transmit(sensor->i2c_handle, sensor->address, &reg, 1, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    if (HAL_I2C_Master_Receive(sensor->i2c_handle, sensor->address, buffer, length, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    return true;
}
