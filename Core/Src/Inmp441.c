#include "main.h"
#include "codec2.h"

extern I2S_HandleTypeDef hi2s1;
extern DAC_HandleTypeDef hdac;
extern uint32_t callback_count;

void RlyrrTransmit(void);

struct CODEC2 *codec2;
uint16_t i2s_buffer[160];
uint8_t encoded_bits[8];
short decoded_buffer[160];

void inmp_Start(void)
{
    codec2 = codec2_create(CODEC2_MODE_700C);
    HAL_I2S_Receive_DMA(&hi2s1, i2s_buffer, 160);
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
    if (hi2s->Instance == SPI1)
    {
        callback_count++;
        codec2_encode(codec2, encoded_bits, (short *)i2s_buffer);
        RlyrrTransmit();
    }
}
