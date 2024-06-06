#include "iis3dwb_read_data_polling.h"
#include "iis3dwb_reg.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;  // Make sure this matches your SPI handle

/* Private variables ---------------------------------------------------------*/
stmdev_ctx_t dev_ctx;
#define    BOOT_TIME        10 //ms
/* Function prototypes -------------------------------------------------------*/
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static void platform_delay(uint32_t ms);
static void platform_init(void);
static uint8_t whoamI;
/**
 * @brief  Initialize the IIS3DWB sensor.
 * @retval None
 */
void iis3dwb_init(void)
{
    /* Initialize mems driver interface */
    dev_ctx.write_reg = platform_write;
    dev_ctx.read_reg = platform_read;
    dev_ctx.mdelay = platform_delay;
    dev_ctx.handle = &hspi1;

    platform_delay(BOOT_TIME);

    iis3dwb_device_id_get(&dev_ctx, &whoamI);

    if (whoamI != IIS3DWB_ID)
    {
        while (1)
        {
            // Device not found, handle error
        }
    }

    /* Enable Block Data Update */
    iis3dwb_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
    /* Set Output Data Rate */
    iis3dwb_xl_data_rate_set(&dev_ctx, IIS3DWB_XL_ODR_26k7Hz);
    /* Set full scale */
    iis3dwb_xl_full_scale_set(&dev_ctx, IIS3DWB_8g);
}

/**
 * @brief  Read accelerometer data.
 * @retval Accelerometer data in mg
 */
float iis3dwb_read_data_polling(void)
{
    int16_t data_raw_acceleration[3];
    float acceleration_mg[3];

    /* Read accelerometer data */
    iis3dwb_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
    acceleration_mg[0] = iis3dwb_from_fs8g_to_mg(data_raw_acceleration[0]);
    acceleration_mg[1] = iis3dwb_from_fs8g_to_mg(data_raw_acceleration[1]);
    acceleration_mg[2] = iis3dwb_from_fs8g_to_mg(data_raw_acceleration[2]);

    /* For simplicity, returning only the X-axis data */
    return acceleration_mg[0];
}

/**
 * @brief  Write generic device register (platform dependent).
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len)
{
    reg |= 0x40; // Multi-byte write bit for SPI

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // Adjust CS pin as per your configuration
    HAL_SPI_Transmit((SPI_HandleTypeDef*)handle, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Transmit((SPI_HandleTypeDef*)handle, (uint8_t*)bufp, len, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // Adjust CS pin as per your configuration

    return 0;
}

/**
 * @brief  Read generic device register (platform dependent).
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
    reg |= 0xC0; // Multi-byte read bit for SPI

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // Adjust CS pin as per your configuration
    HAL_SPI_Transmit((SPI_HandleTypeDef*)handle, &reg, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive((SPI_HandleTypeDef*)handle, bufp, len, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); // Adjust CS pin as per your configuration

    return 0;
}

/**
 * @brief  Platform specific delay (platform dependent).
 */
static void platform_delay(uint32_t ms)
{
    HAL_Delay(ms);
}

/**
 * @brief  Platform specific initialization (platform dependent).
 */
static void platform_init(void)
{
    // Platform specific initialization code if needed
}
