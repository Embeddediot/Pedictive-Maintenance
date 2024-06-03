#include "stts22h.h"
#include "stm32h7xx_hal.h" // Include your specific HAL header

extern I2C_HandleTypeDef hi2c2; // Declare your I2C handle

STTS22H::STTS22H() {
    // Initialization code here
}

bool STTS22H::initialize() {
    uint8_t who_am_i = 0;
    if (!readRegister(WHO_AM_I_REG, who_am_i) || who_am_i != WHO_AM_I_VAL) {
        return false;
    }
    // Additional initialization code
    return true;
}

bool STTS22H::readTemperature(float &temperature) {
    uint8_t buffer[2];
    if (!readRegisters(TEMP_L, buffer, 2)) {
        return false;
    }
    // Convert the data to temperature value (adjust the conversion as needed)
    int16_t tempRaw = (buffer[1] << 8) | buffer[0];
    temperature = tempRaw * 0.01; // Conversion factor for the STTS22H
    return true;
}

bool STTS22H::writeRegister(uint8_t reg, uint8_t value) {
    uint8_t data[2] = {reg, value};
    if (HAL_I2C_Master_Transmit(&hi2c2, SENSOR_ADDRESS, data, 2, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    return true;
}

bool STTS22H::readRegister(uint8_t reg, uint8_t &value) {
    if (HAL_I2C_Master_Transmit(&hi2c2, SENSOR_ADDRESS, &reg, 1, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    if (HAL_I2C_Master_Receive(&hi2c2, SENSOR_ADDRESS, &value, 1, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    return true;
}

bool STTS22H::readRegisters(uint8_t reg, uint8_t *buffer, uint16_t length) {
    if (HAL_I2C_Master_Transmit(&hi2c2, SENSOR_ADDRESS, &reg, 1, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    if (HAL_I2C_Master_Receive(&hi2c2, SENSOR_ADDRESS, buffer, length, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    return true;
}
