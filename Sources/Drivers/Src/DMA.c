// USART2 mapping:
// Rx - Stream 5 / Channel 4
// Tx - Stream 6 / Channel 4

#include "DMA.h"

uint8_t USART2_Receiver_Buf[USART2_RECEIVER_BUF_SIZE];

void DMA1_Stream5_IRQHandler(void) {

}

void DMA1_Stream6_IRQHandler(void) {

}

void DMA_Init(void) {
	if (LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_5)) {
		LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);

		while (LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_5));
	}

	WRITE_REG(DMA1->HIFCR, (0xF << 8) | (0x1 << 6)); // Clear all stream 5 flags

	LL_DMA_ConfigAddresses(DMA1, LL_DMA_STREAM_5, USART2->DR, (uint32_t)&USART2_Receiver_Buf, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_5, USART2_RECEIVER_BUF_SIZE );

	LL_DMA_SetChannelSelection(DMA1, LL_DMA_STREAM_5, LL_DMA_CHANNEL_4);

	LL_DMA_SetStreamPriorityLevel(DMA1, LL_DMA_STREAM_5, LL_DMA_PRIORITY_VERYHIGH);



//	WRITE_REG(DMA1->HIFCR, (0xF << 18) | (0x1 << 16)); // Clear all stream 6 flags
}
