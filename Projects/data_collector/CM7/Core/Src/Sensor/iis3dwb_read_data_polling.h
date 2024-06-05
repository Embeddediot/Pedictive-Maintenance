/*
 * iis3dwb_read_data_polling.h
 *
 *  Created on: Jun 5, 2024
 *      Author: bjs
 */

#ifndef IIS3DWB_IIS3DWB_READ_DATA_POLLING_H
#define IIS3DWB_READ_DATA_POLLING_H

#include <stdint.h>
#include "iis3dwb_reg.h"

/* Define communication interface based on the evaluation board */
#if defined(STEVAL_MKI109V3)
#define SENSOR_BUS hspi2
#define PWM_3V3 915

#elif defined(SPC584B_DIS)
#define SENSOR_BUS NULL
#endif

/* Define constants */
#define BOOT_TIME 10 // ms

/* Declare extern variables */
extern I2C_HandleTypeDef hi2c2;
extern UART_HandleTypeDef huart3;

/* Function prototypes */
float iis3dwb_read_data_polling(void);
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static void tx_com(uint8_t *tx_buffer, uint16_t len);
static void platform_delay(uint32_t ms);
static void platform_init(void);

#endif // IIS3DWB_READ_DATA_POLLING_H
