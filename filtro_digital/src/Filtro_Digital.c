#include "arm_math.h"
#include "math_helper.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "board.h"
#include <stdbool.h>
#include "fir_lpf_data_q31.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

static DMA_TransferDescriptor_t DMADescriptor[4];

q31_t BufferQ31[4][TEST_LENGTH_SAMPLES];
float32_t BufferF32[4][TEST_LENGTH_SAMPLES];

static float32_t firStateF32[TEST_LENGTH_SAMPLES + NUM_TAPS - 1];
static arm_fir_instance_f32 S;

//static arm_status status;

void DMA__DAC_Config(){

	DMADescriptor[0].src 	=	(uint32_t) &BufferQ31[0][0];
	DMADescriptor[0].dst 	=	(uint32_t) &LPC_DAC->CR;
	DMADescriptor[0].lli 	=	(uint32_t) &DMADescriptor[1];
	DMADescriptor[0].ctrl	=	TEST_LENGTH_SAMPLES	// transfer size (0 - 11) = 64
			|	(0 << 12)  	// source burst size (12 - 14) = 1
			|	(0 << 15)  	// destination burst size (15 - 17) = 1
			| 	(2 << 18)  	// source width (18 - 20) = 32 bit
			| 	(2 << 21)  	// destination width (21 - 23) = 32 bit
			| 	(1 << 24)  	// source AHB select (24) = AHB 0
			| 	(1 << 25)  	// destination AHB select (25) = AHB 1
			| 	(1 << 26)  	// source increment (26) = increment
			| 	(0 << 27)  	// destination increment (27) = no increment
			| 	(0 << 28)  	// mode select (28) = access in user mode
			| 	(0 << 29)  	// (29) = access not bufferable
			| 	(0 << 30)  	// (30) = access not cacheable
			| 	(0 << 31); 	// terminal count interrupt disabled (deshabilita (0) / habilita (1));

	DMADescriptor[1].src	=	(uint32_t) &BufferQ31[1][0];
	DMADescriptor[1].dst	=	(uint32_t) &LPC_DAC->CR;
	DMADescriptor[1].lli	=	(uint32_t) &DMADescriptor[0];
	DMADescriptor[1].ctrl	=	DMADescriptor[0].ctrl;

	LPC_GPDMA->CH[0].SRCADDR	= DMADescriptor[0].src;
	LPC_GPDMA->CH[0].DESTADDR 	= DMADescriptor[0].dst;
	LPC_GPDMA->CH[0].LLI 		= DMADescriptor[0].lli;
	LPC_GPDMA->CH[0].CONTROL	= DMADescriptor[0].ctrl;
	LPC_GPDMA->CH[0].CONFIG		=	1   		// channel enabled (0)
			|	(0 << 1)  	// source peripheral (1 - 5) = none
			|	(0x0F << 6) // destination peripheral (6 - 10) = DAC
			| 	(1 << 11)  	// flow control (11 - 13) = mem to per
			| 	(0 << 14)  	// (14) = mask out error interrupt (0 = enmsacara)
			| 	(1 << 15)  	// (15) = mask out terminal count interrupt  (0 = enmsacara)
			| 	(0 << 16)  	// (16) = no locked transfers
			| 	(0 << 18); 	// (27) = no HALT (SE USA HASTA EL 18)
}

void DMA__ADC_Config(){

	DMADescriptor[2].src 	=	(uint32_t) &LPC_ADC0->DR[3];
	DMADescriptor[2].dst 	=	(uint32_t) &BufferQ31[2][0];
	DMADescriptor[2].lli 	=	(uint32_t) &DMADescriptor[3];
	DMADescriptor[2].ctrl	=	TEST_LENGTH_SAMPLES	// transfer size (0 - 11) = 64
			|	(0 << 12)  	// source burst size (12 - 14) = 1
			|	(0 << 15)  	// destination burst size (15 - 17) = 1
			| 	(2 << 18)  	// source width (18 - 20) = 32 bit
			| 	(2 << 21)  	// destination width (21 - 23) = 32 bit
			| 	(1 << 24)  	// source AHB select (24) = AHB 0
			| 	(1 << 25)  	// destination AHB select (25) = AHB 1
			| 	(0 << 26)  	// source increment (26) = no increment
			| 	(1 << 27)  	// destination increment (27) = increment
			| 	(0 << 28)  	// mode select (28) = access in user mode
			| 	(0 << 29)  	// (29) = access not bufferable
			| 	(0 << 30)  	// (30) = access not cacheable
			| 	(1 << 31); 	// terminal count interrupt disabled (deshabilita (0) / habilita (1));

	DMADescriptor[3].src	=	(uint32_t) &LPC_ADC0->DR[3];
	DMADescriptor[3].dst	=	(uint32_t) &BufferQ31[3][0];
	DMADescriptor[3].lli	=	(uint32_t) &DMADescriptor[2];
	DMADescriptor[3].ctrl	=	DMADescriptor[2].ctrl;

	LPC_GPDMA->CH[1].SRCADDR	= DMADescriptor[2].src;
	LPC_GPDMA->CH[1].DESTADDR 	= DMADescriptor[2].dst;
	LPC_GPDMA->CH[1].LLI 		= DMADescriptor[2].lli;
	LPC_GPDMA->CH[1].CONTROL	= DMADescriptor[2].ctrl;
	LPC_GPDMA->CH[1].CONFIG		=	1   		// channel enabled (1)
			|	(0xD << 1)	// source peripheral (1 - 5) = ADC
			|	(0 << 6) 	// destination peripheral (6 - 10) = none
			| 	(2 << 11)	// flow control (11 - 13) = per to mem
			| 	(0 << 14)  	// (14) = mask out error interrupt (0 = enmsacara)
			| 	(1 << 15)  	// (15) = mask out terminal count interrupt  (0 = enmsacara)
			| 	(0 << 16)  	// (16) = no locked transfers
			| 	(0 << 18); 	// (27) = no HALT (SE USA HASTA EL 18)
}

void DAC_Config(){

	LPC_SCU->ENAIO[2] |= 1;

	LPC_SCU->SFSP[4][4] |= SCU_MODE_INACT;

	LPC_DAC->CR	|= 	(1	<<	16);

	LPC_DAC->CTRL |= (1	<<	1)	|
			(1	<<	2)	|
			(1	<<	3);

	LPC_DAC->CNTVAL |= (2551 & 0xFFFF);		//Configura el contador del DAC
}

void ADC_Config(){

	LPC_SCU->ENAIO[0] |= (1 << 3);

	LPC_SCU->SFSP[7][5] = SCU_MODE_INACT;

	LPC_ADC0->CR |= (1	 <<	3)	|
			(231 <<	8)	|
			(1	 <<	16)	|
			(0	 <<	17)	|
			(1	 <<	21)	|
			(0	 <<	24)	|
			(0	 <<	27)	;

	LPC_ADC0->INTEN = (1 <<	3)	|
			(0 << 8)	;

	NVIC->ICER[0] |= (1	<<	17);
}

bool b0n = false;
bool b1n = false;
bool flag0 = false;
bool flag1 = false;

void DMA_IRQHandler(void) {

//	if( ((LPC_GPDMA->INTTCSTAT) & (1 << 0)) != 0){
//		LPC_GPDMA->INTTCCLEAR |= 1 << 0;
//		b0n = ! b0n;
//		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 0, b0n);
//	}
//
//	if( ((LPC_GPDMA->INTTCSTAT) & (1 << 1)) != 0){
//		LPC_GPDMA->INTTCCLEAR |= 1 << 1;
//		b1n = ! b1n;
//		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 3, b1n);
//	}

	LPC_GPDMA->INTTCCLEAR |= 1 << 1;
	if(LPC_GPDMA->CH[1].LLI == DMADescriptor[2].lli){
		flag0=true;
	}
	if(LPC_GPDMA->CH[1].LLI == DMADescriptor[3].lli){
		flag1=true;
	}

}

int main(void) {

	SystemCoreClockUpdate();
	Board_Init();

	DAC_Config();
	ADC_Config();

	DMA__DAC_Config();
	DMA__ADC_Config();

	Chip_SCU_PinMuxSet(6, 1, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0);
	Chip_SCU_PinMuxSet(6, 4, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 3, 0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 3, 3);

	arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], TEST_LENGTH_SAMPLES);

	LPC_GPDMA->CONFIG |= 1;
	NVIC->ISER[0] |= (1 << 2);

	while(1){
		if(flag0){
			//memcpy(&Buffer[1][0], &Buffer[2][0], 4*MUESTRAS);
//			Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 3, true);
			arm_q31_to_float(&BufferQ31[2][0],&BufferF32[0][0],TEST_LENGTH_SAMPLES);
			arm_fir_f32(&S, &BufferF32[0][0], &BufferF32[1][0], TEST_LENGTH_SAMPLES);
			arm_float_to_q31(&BufferF32[1][0],&BufferQ31[1][0],TEST_LENGTH_SAMPLES);
//			Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 3, false);
			flag0=false;
		}
		if(flag1){
			//memcpy(&Buffer[0][0], &Buffer[3][0], 4*MUESTRAS);
			arm_q31_to_float(&BufferQ31[3][0],&BufferF32[2][0],TEST_LENGTH_SAMPLES);
			arm_fir_f32(&S, &BufferF32[2][0], &BufferF32[3][0], TEST_LENGTH_SAMPLES);
			arm_float_to_q31(&BufferF32[3][0],&BufferQ31[0][0], TEST_LENGTH_SAMPLES);
			flag1=false;
		}
	}
}
