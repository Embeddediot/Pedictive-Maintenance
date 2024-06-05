/*
 * temp_collect.h
 *
 *  Created on: Jun 5, 2024
 *      Author: bjs
 */

#ifndef SRC_SENSOR_TEMP_COLLECT_H_
#define SRC_SENSOR_TEMP_COLLECT_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "stts22h_reg.h"
#include "main.h"

/* Function Prototypes */
float stts22h_read_data_polling(void);

#ifdef __cplusplus
}
#endif




#endif /* SRC_SENSOR_TEMP_COLLECT_H_ */
