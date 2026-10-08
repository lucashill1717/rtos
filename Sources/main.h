#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx.h"
#include "system_stm32f4xx.c"

#define BIT_IS_SET(Reg, Bit) ((Reg) & (Bit))

#define SCB_CPACR  (*(volatile uint32_t *)0xE000ED88)

#define USART2_OVER8_DIVISOR 16

void inline enable_FPU(void) {
	SCB_CPACR |= (0xF << 20);
	__asm volatile ("dsb");
	__asm volatile ("isb");
}
