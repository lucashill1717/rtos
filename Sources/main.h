#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx.h"
#include "system_stm32f4xx.c"

#include "USART.h"

#define SCB_CPACR  (*(volatile uint32_t *)0xE000ED88)

void inline enable_FPU(void) {
	SCB_CPACR |= (0xF << 20);
	__asm volatile ("dsb");
	__asm volatile ("isb");
}
