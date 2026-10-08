#include "USART.h"

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
