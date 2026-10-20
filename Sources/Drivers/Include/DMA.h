#ifndef _DMA_H_
#define _DMA_H_

#include "stm32f4xx.h"
#include "stm32f4xx_ll_dma.h"

#define USART2_RECEIVER_BUF_SIZE 64

extern uint8_t USART2_Receiver_Buf[USART2_RECEIVER_BUF_SIZE];

void DMA_Init(void);

#endif /* _DMA_H_ */
