#ifndef _USART_H_
#define _USART_H_

#include <stdint.h>

#include "DriversHelper.h"
#include "stm32f4xx.h"


#define USART2_OVER8_DIVISOR 16

void USART2_Init(uint32_t baud_rate);

#endif /* _USART_H_ */
