#include "main.h"


static char transmit_string[] = "Hello World\r\n";
static uint8_t transmit_string_itr = 0;


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
