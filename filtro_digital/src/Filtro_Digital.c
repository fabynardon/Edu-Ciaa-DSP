#include "arm_math.h"
#include "math_helper.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "board.h"
#include <stdbool.h>

#define pi 3.14159265

#define MUESTRAS		256
#define FRECUENCIA		2000			    // Frecuencia de la senal a generar [HZ]
#define GPDMA_CLOCK		204e6				// Frecuencia de operacion del DMA
#define NUM_TAPS              30

#define FRAC16(x) 1*x

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

static DMA_TransferDescriptor_t DMADescriptor[4];

//static ADC_CLOCK_SETUP_T ADCSetup;
q15_t Buffer[4][MUESTRAS];

char flag0, flag1;

int	PULSOS = GPDMA_CLOCK/(MUESTRAS*FRECUENCIA);

//static float32_t firStateF32[MUESTRAS + NUM_TAPS - 1];
static q15_t firStateF32[MUESTRAS + NUM_TAPS - 1];
//static arm_fir_instance_f32 S;
static arm_fir_instance_q15 S;
static arm_status status;

const q15_t firCoeffs32[30]={
FRAC16(-0.001626713373),	FRAC16(-0.001982091342),	FRAC16(-0.001196998776),	FRAC16(+0.001845687947),	FRAC16(+0.006801082329),	FRAC16(+0.010072171918),
FRAC16(+0.005990524395),	FRAC16(-0.008387651291),	FRAC16(-0.027870248460),	FRAC16(-0.038075524205),	FRAC16(-0.021661235385),	FRAC16(+0.030495506289),
FRAC16(+0.110171093788),	FRAC16(+0.191828095691),	FRAC16(+0.243596300476),	FRAC16(+0.243596300476),	FRAC16(+0.191828095691),	FRAC16(+0.110171093788),
FRAC16(+0.030495506289),	FRAC16(-0.021661235385),	FRAC16(-0.038075524205),	FRAC16(-0.027870248460),	FRAC16(-0.008387651291),	FRAC16(+0.005990524395),
FRAC16(+0.010072171918),	FRAC16(+0.006801082329),	FRAC16(+0.001845687947),	FRAC16(-0.001196998776),	FRAC16(-0.001982091342),	FRAC16(-0.001626713373)};


//const float32_t firCoeffs32[29] = {
//		-0.0018225230, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
//		-0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
//		+0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
//		+0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
//};

void DMA__DAC_Config(){

	DMADescriptor[0].src 	=	(uint32_t) &Buffer[0][0];
	DMADescriptor[0].dst 	=	(uint32_t) &LPC_DAC->CR;
	DMADescriptor[0].lli 	=	(uint32_t) &DMADescriptor[1];
	DMADescriptor[0].ctrl	=	MUESTRAS	// transfer size (0 - 11) = 64
                        	|	(0 << 12)  	// source burst size (12 - 14) = 1
							|	(0 << 15)  	// destination burst size (15 - 17) = 1
							| 	(1 << 18)  	// source width (18 - 20) = 32 bit
							| 	(1 << 21)  	// destination width (21 - 23) = 32 bit
							| 	(1 << 24)  	// source AHB select (24) = AHB 0
							| 	(1 << 25)  	// destination AHB select (25) = AHB 1
							| 	(1 << 26)  	// source increment (26) = increment
							| 	(0 << 27)  	// destination increment (27) = no increment
							| 	(0 << 28)  	// mode select (28) = access in user mode
							| 	(0 << 29)  	// (29) = access not bufferable
							| 	(0 << 30)  	// (30) = access not cacheable
							| 	(0 << 31); 	// terminal count interrupt disabled (deshabilita (0) / habilita (1));

	DMADescriptor[1].src	=	(uint32_t) &Buffer[1][0];
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
	DMADescriptor[2].dst 	=	(uint32_t) &Buffer[2][0];
	DMADescriptor[2].lli 	=	(uint32_t) &DMADescriptor[3];
	DMADescriptor[2].ctrl	=	MUESTRAS	// transfer size (0 - 11) = 64
                        	|	(0 << 12)  	// source burst size (12 - 14) = 1
							|	(0 << 15)  	// destination burst size (15 - 17) = 1
							| 	(1 << 18)  	// source width (18 - 20) = 32 bit
							| 	(1 << 21)  	// destination width (21 - 23) = 32 bit
							| 	(1 << 24)  	// source AHB select (24) = AHB 0
							| 	(1 << 25)  	// destination AHB select (25) = AHB 1
							| 	(0 << 26)  	// source increment (26) = no increment
							| 	(1 << 27)  	// destination increment (27) = increment
							| 	(0 << 28)  	// mode select (28) = access in user mode
							| 	(0 << 29)  	// (29) = access not bufferable
							| 	(0 << 30)  	// (30) = access not cacheable
							| 	(1 << 31); 	// terminal count interrupt disabled (deshabilita (0) / habilita (1));

	DMADescriptor[3].src	=	(uint32_t) &LPC_ADC0->DR[3];
	DMADescriptor[3].dst	=	(uint32_t) &Buffer[3][0];
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
//bool b0n = false;
//bool b1n = false;

void DMA_IRQHandler(void) {
//	if( ((LPC_GPDMA->INTTCSTAT) & (1 << 0)) != 0){
//		b0n = ! b0n;
//		LPC_GPDMA->INTTCCLEAR |= 1 << 0;
//		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 0, b0n);
//	}
//
//	if( ((LPC_GPDMA->INTTCSTAT) & (1 << 1)) != 0){
//		b1n = ! b1n;
//		LPC_GPDMA->INTTCCLEAR |= 1 << 1;
//		Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 3, b1n);
//	}
	LPC_GPDMA->INTTCCLEAR |= 1 << 1;
	if(LPC_GPDMA->CH[1].LLI == DMADescriptor[2].lli){
		flag0=1;
	}
	if(LPC_GPDMA->CH[1].LLI == DMADescriptor[3].lli){
		flag1=1;
	}
}

void DMA_Config();
void DAC_Config();

int main(void) {

	SystemCoreClockUpdate();
	Board_Init();

	DAC_Config();
	ADC_Config();

	DMA__DAC_Config();
	DMA__ADC_Config();

//	Chip_SCU_PinMuxSet(6, 1, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0);
//	Chip_SCU_PinMuxSet(6, 4, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | SCU_MODE_FUNC0);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 3, 0);
//	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 3, 3);

	//arm_fir_init_f32(&S, 29, (float32_t *)&firCoeffs32[0], &firStateF32[0], MUESTRAS);
	arm_fir_init_q15(&S, NUM_TAPS, (q15_t *)&firCoeffs32[0], &firStateF32[0], MUESTRAS);

	LPC_GPDMA->CONFIG |= 1;
	NVIC->ISER[0] |= (1 << 2);

	while(1){
		if(flag0==1){
			memcpy(&Buffer[1][0], &Buffer[2][0], 2*MUESTRAS);
			//arm_fir_f32(&S, &Buffer[2][0], &Buffer[1][0], MUESTRAS);
			//arm_fir_fast_q15(&S, &Buffer[2][0], &Buffer[1][0], MUESTRAS);
			flag0=0;
		}
		if(flag1==1){
			memcpy(&Buffer[0][0], &Buffer[3][0], 2*MUESTRAS);
			//arm_fir_f32(&S, &Buffer[3][0], &Buffer[0][0], MUESTRAS);
			//arm_fir_fast_q15(&S, &Buffer[3][0], &Buffer[0][0], MUESTRAS);
			flag1=0;
		}
	}
}
