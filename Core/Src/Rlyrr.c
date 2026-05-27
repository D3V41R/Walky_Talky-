#include "main.h"
#include <string.h>
#include <stdio.h>
#include "codec2.h"

extern UART_HandleTypeDef huart1;
extern uint8_t encoded_bits[8];
extern short decoded_buffer[160];
extern DAC_HandleTypeDef hdac;
extern struct CODEC2 *codec2;

char cmds[256];
uint8_t rxBuffer[128];
uint8_t rx_flag = 0;

void RlyrrInit(void)
{
    HAL_UART_Receive_DMA(&huart1, rxBuffer, sizeof(rxBuffer));

    HAL_Delay(100);
    sprintf(cmds, "AT+ADDRESS=1\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t*)cmds, strlen(cmds), 1000);

    HAL_Delay(100);
    sprintf(cmds, "AT+NETWORKID=5\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t*)cmds, strlen(cmds), 1000);

    HAL_Delay(100);
    sprintf(cmds, "AT+BAND=915000000\r\n");
    HAL_UART_Transmit(&huart1, (uint8_t*)cmds, strlen(cmds), 1000);
}

void RlyrrTransmit(void)
{
    sprintf(cmds, "AT+SEND=2,8,%02X%02X%02X%02X%02X%02X%02X%02X\r\n",
            encoded_bits[0], encoded_bits[1], encoded_bits[2], encoded_bits[3],
            encoded_bits[4], encoded_bits[5], encoded_bits[6], encoded_bits[7]);

    HAL_UART_Transmit(&huart1, (uint8_t*)cmds, strlen(cmds), 1000);
}

void RlyrrReceive(void)
{
    if (strstr((char*)rxBuffer, "+RCV") != NULL)
    {
        char *data_start = strchr((char*)rxBuffer, ',');
        if (data_start) data_start = strchr(data_start + 1, ',');
        if (data_start)
        {
            data_start++;
            for (int i = 0; i < 8; i++)
            {
                char byte_str[3] = {data_start[i*2], data_start[i*2+1], 0};
                encoded_bits[i] = (uint8_t)strtol(byte_str, NULL, 16);
            }
            codec2_decode(codec2, decoded_buffer, encoded_bits);

            HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
            for (int i = 0; i < 160; i++)
            {
                uint16_t dac_val = (decoded_buffer[i] + 32768) >> 4;
                HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_val);
                HAL_Delay(1);
            }
        }
        memset(rxBuffer, 0, sizeof(rxBuffer));
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        rx_flag = 1;
        HAL_UART_Receive_DMA(&huart1, rxBuffer, sizeof(rxBuffer));
    }
}
