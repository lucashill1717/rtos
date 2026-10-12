#include "main.h"


int main(void) {
	GPIOA_Init();
	USART2_Init(115200);

	while (1) {}
}
