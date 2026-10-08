#include "USART.h"


void USART2_IRQHandler(void) {
	if (BIT_IS_SET(USART2->SR, 1 << 5)) {  // RXNEIE
		// clear through read from DR
	}

	if (BIT_IS_SET(USART2->SR, 1 << 7)) {  // TXEIE
		// clear through write to DR
		USART2->DR = transmit_string[transmit_string_itr++];
		if (transmit_string_itr > 12)
		{
			transmit_string_itr = 0;
		}
	}

	if (BIT_IS_SET(USART2->SR, 1 << 6)) {  // TCIE
		// not sure yet, can be cleared by software
		CLEAR_BIT(USART2->SR, 1 << 6);
	}
}


void USART2_Set_Baud_Rate(uint32_t baud_rate) {
	SystemCoreClockUpdate();

	uint32_t pclk1 = SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1)>> RCC_CFGR_PPRE1_Pos];

	uint32_t tmp = (100 * pclk1) / (USART2_OVER8_DIVISOR * baud_rate);    // (pclk1 / (USART2_OVER8_DIVISOR * baud)) x 100
	uint32_t mantissa = tmp / 100;
	uint32_t frac_x100 = tmp - (mantissa * 100);
	uint32_t fraction = ((frac_x100 * USART2_OVER8_DIVISOR) + 50) / 100;  // round to nearest whole number

	if (fraction >= USART2_OVER8_DIVISOR) {
		++mantissa;
		fraction = 0;
	}

	USART2->BRR = (mantissa << 4) | (fraction & 0xF);
}


void USART2_Init(uint32_t baud_rate) {
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_USART2EN);  // Enable USART2 clock
	SET_BIT(USART2->CR1, 1 << 13);                // UE, USART enable

	CLEAR_BIT(USART2->CR1, 1 << 15);              // OVER8, oversample by 16
	CLEAR_BIT(USART2->CR1, 1 << 12);              // M, data length 8
	CLEAR_BIT(USART2->CR2, 3 << 12);              // 1 stop bit

	USART2_Set_Baud_Rate(baud_rate);

	SET_BIT(USART2->CR1, 1 << 3);                 // TE, transmitter enable
	SET_BIT(USART2->CR1, 1 << 2);                 // RE, reciever enable

	SET_BIT(USART2->CR1, 1 << 7);                 // TXEIE, transmit data register empty interupt enable
	SET_BIT(USART2->CR1, 1 << 6);                 // TCIE, tranmission complete interupt enable
	SET_BIT(USART2->CR1, 1 << 5);                 // RXNEIE, read data register not empty interupt enable
	NVIC_EnableIRQ(USART2_IRQn);
}
