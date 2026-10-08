#include "main.h"


void GPIOA_Init(void) {
	SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);  // Enable GPIOA clock

	SET_BIT(GPIOA->MODER, 2 << (2 * 2));         // AF mode for port 2 (Tx)
	SET_BIT(GPIOA->MODER, 2 << (3 * 2));         // AF mode for port 3 (Rx)

	SET_BIT(GPIOA->AFR[0], 7 << (2 * 4));        // AF7 is USART2, port 2
	SET_BIT(GPIOA->AFR[0], 7 << (3 * 4));        // AF7 is USART2, port 3

	SET_BIT(GPIOA->OSPEEDR, 3 << (2 * 2));       // High speed for port 2
	SET_BIT(GPIOA->OSPEEDR, 3 << (3 * 2));       // High speed for port 3
}


int main(void) {
	GPIOA_Init();
	USART2_Init(115200);

	while (1) {}
}
