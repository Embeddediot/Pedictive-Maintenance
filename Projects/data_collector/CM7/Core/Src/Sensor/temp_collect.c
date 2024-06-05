/*
 * temp_collect.c
 *
 *  Created on: Jun 5, 2024
 *      Author: bjs
 */

/*
 ******************************************************************************
 * @file    read_data_polling.c
 * @author  Sensors Software Solution Team
 * @brief   This file shows how to get data from the sensor.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "stts22h_reg.h"
#include "main.h"

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static int16_t data_raw_temperature;
static float temperature_degC;
static uint8_t whoamI;
//static uint8_t tx_buffer[1000];

/* Extern variables ----------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c2; // Ensure this matches your I2C handle

/* Private functions ---------------------------------------------------------*/
/*
 *   WARNING:
 *   Functions declared in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void tx_com(uint8_t *tx_buffer, uint16_t len);
static void platform_delay(uint32_t ms);
static void platform_init(void);
static int connect_flag=0;

/* Main Example --------------------------------------------------------------*/
float stts22h_read_data_polling(void)
{
  /* Initialize mems driver interface */

	 stmdev_ctx_t dev_ctx;
	   dev_ctx.write_reg = platform_write;
	   dev_ctx.read_reg = platform_read;
	   dev_ctx.mdelay = platform_delay;
	   dev_ctx.handle = &hi2c2; // Use the correct I2C handle

  /* Check device ID */


  if (connect_flag==0)
  {
	   stts22h_dev_id_get(&dev_ctx, &whoamI);
	   connect_flag=1;
	  if (whoamI == STTS22H_ID)
	    {
	  	  stts22h_temp_data_rate_set(&dev_ctx, STTS22H_1Hz);

	    }
	  else
	  {
		connect_flag=0;
		return 1000;
	  }

  }
	  /* Enable interrupt on high(=49.5 degC)/low(=2.5 degC) temperature. */
	  //float temperature_high_limit = 49.5f;
	  //stts22h_temp_trshld_high_set(&dev_ctx, (int8_t)(temperature_high_limit / 0.64f) + 64 );

	  //float temperature_low_limit = 2.5f;
	  //stts22h_temp_trshld_low_set(&dev_ctx, (int8_t)(temperature_low_limit / 0.64f) + 64 );

	  /* Read samples in polling mode */
		/*
		 * Read output only if not busy
		 * WARNING: _flag_data_ready_get works only when the device is in single
		 *          mode or with data rate set at 1Hz (this function use the busy
		 *          bit in status register please see the DS for details)
		 */
		uint8_t flag;
		stts22h_temp_flag_data_ready_get(&dev_ctx, &flag);

		if (flag) {
		  /* Read temperature data */
		  memset(&data_raw_temperature, 0, sizeof(int16_t));
		  stts22h_temperature_raw_get(&dev_ctx, &data_raw_temperature);
		  temperature_degC = stts22h_from_lsb_to_celsius(data_raw_temperature);
		  //sprintf((char *)tx_buffer, "Temperature [degC]:%3.2f\r\n", temperature_degC);
		  //tx_com(tx_buffer, strlen((char const *)tx_buffer));
		}
	  return temperature_degC;
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this example, it's used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  HAL_I2C_Mem_Write((I2C_HandleTypeDef*)handle, STTS22H_I2C_ADD_H, reg,
                    I2C_MEMADD_SIZE_8BIT, (uint8_t*)bufp, len, 1000);
  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this example, it's used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that stores the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  HAL_I2C_Mem_Read((I2C_HandleTypeDef*)handle, STTS22H_I2C_ADD_H, reg,
                   I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}

/*
 * @brief  Send buffer to console (platform dependent)
 *
 * @param  tx_buffer     buffer to transmit
 * @param  len           number of bytes to send
 *
 */
static void tx_com(uint8_t *tx_buffer, uint16_t len)
{
  // Assuming huart3 is used for debug/console communication
  extern UART_HandleTypeDef huart3;
  HAL_UART_Transmit(&huart3, tx_buffer, len, 1000);
}

/*
 * @brief  platform specific delay (platform dependent)
 *
 * @param  ms        delay in ms
 *
 */
static void platform_delay(uint32_t ms)
{
  HAL_Delay(ms);
}

/*
 * @brief  platform specific initialization (platform dependent)
 */
static void platform_init(void)
{
  // Initialize any required peripherals here if needed
}



