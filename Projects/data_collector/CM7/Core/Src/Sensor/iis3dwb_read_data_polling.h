#ifndef IIS3DWB_READ_DATA_POLLING_H
#define IIS3DWB_READ_DATA_POLLING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void iis3dwb_init(void);
float iis3dwb_read_data_polling(void);

#ifdef __cplusplus
}
#endif

#endif /* IIS3DWB_READ_DATA_POLLING_H */
