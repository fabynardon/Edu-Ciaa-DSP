/*===============================================================================
Name        : fir_lpf_example_q31.c
Author      : Fabian Nardone
Description : Ejemplo de filtro digital con CMSIS-DSP
=================================================================================
*/

/* ----------------------------------------------------------------------
** Include Files
** ------------------------------------------------------------------- */
#include "board.h"
#include "fir_lpf_data_q31.h"

/* -------------------------------------------------------------------
 * The input signal and reference output (computed with MATLAB)
 * are defined externally in arm_fir_lpf_data.c.
 * ------------------------------------------------------------------- */

float32_t testInputF32[TEST_LENGTH_SAMPLES];
float32_t testOutputF32[TEST_LENGTH_SAMPLES];

/* -------------------------------------------------------------------
 * Declare Test output buffer
 * ------------------------------------------------------------------- */

static q31_t testOutputQ31[TEST_LENGTH_SAMPLES];

/* -------------------------------------------------------------------
 * Declare State buffer of size (numTaps + blockSize - 1)
 * ------------------------------------------------------------------- */

static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

/* ------------------------------------------------------------------
 * Global variables for FIR LPF Example
 * ------------------------------------------------------------------- */

uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = TEST_LENGTH_SAMPLES/BLOCK_SIZE;

float32_t  snr;

/* ----------------------------------------------------------------------
 * FIR LPF Example
 * ------------------------------------------------------------------- */

int32_t main(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	uint32_t clk = SystemCoreClock/1000000;
	uint32_t start_time;
	uint32_t end_time;
//	uint32_t i;

	arm_fir_instance_f32 S;
	float32_t  *inputF32, *outputF32;
	q31_t  *inputQ31, *outputQ31;

	/* Initialize input and output buffer pointers */
	inputQ31 = &testInputQ31[0];
	outputQ31 = &testOutputQ31[0];
	inputF32 = &testInputF32[0];
	outputF32 = &testOutputF32[0];

	/* Call FIR init function to initialize the instance structure. */
	arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);

	/* ----------------------------------------------------------------------
	 ** Call the FIR process function for every blockSize samples
	 ** ------------------------------------------------------------------- */
//	for(i=0; i < numBlocks; i++) {
//		arm_q31_to_float(inputQ31 + (i * blockSize), inputF32 + (i * blockSize), blockSize);
//		arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
//		arm_float_to_q31(outputF32 + (i * blockSize), outputQ31 + (i * blockSize), blockSize);
//	}

	start_time = Chip_RIT_GetCounter(LPC_RITIMER);

	arm_q31_to_float(inputQ31, inputF32, TEST_LENGTH_SAMPLES);
	arm_fir_f32(&S, inputF32, outputF32, TEST_LENGTH_SAMPLES);
	arm_float_to_q31(outputF32, outputQ31, TEST_LENGTH_SAMPLES);

	end_time = Chip_RIT_GetCounter(LPC_RITIMER);

	DEBUGOUT("TIME   TAKEN: %lu (uSec(s))\r\n", (end_time - start_time) / clk);

	/* ----------------------------------------------------------------------
	 ** Compare the generated output against the reference output computed
	 ** in MATLAB.
	 ** ------------------------------------------------------------------- */

	while(1);
}
