#include "main.h"
#include "codec2.h"

extern I2S_HandleTypeDef hi2s1;
extern DAC_HandleTypeDef hdac;

struct CODEC2 *codec2;
uint16_t i2s_buffer[160];
uint8_t encoded_bits[8];
short decoded_buffer[160];
extern uint32_t callback_count;


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

    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        // encode
        codec2_encode(codec2, encoded_bits, (short *)i2s_buffer);

        // decode back
        codec2_decode(codec2, decoded_buffer, encoded_bits);

        // send to DAC
        HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
        for (int i = 0; i < 160; i++)
        {
            // convert signed 16-bit to 12-bit unsigned for DAC
            uint16_t dac_val = (decoded_buffer[i] + 32768) >> 4;
            HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_val);
            HAL_Delay(1); // ~8kHz
        }
    }
}
