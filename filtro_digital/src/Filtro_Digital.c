/* ----------------------------------------------------------------------
 * Copyright (C) 2010-2012 ARM Limited. All rights reserved.
 *
* $Date:         17. January 2013
* $Revision:     V1.4.0
*
* Project:       CMSIS DSP Library
 * Title:        arm_fir_example_f32.c
 *
 * Description:  Example code demonstrating how an FIR filter can be used
 *               as a low pass filter.
 *
 * Target Processor: Cortex-M4/Cortex-M3
 *
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
 * -------------------------------------------------------------------- */
/* ----------------------------------------------------------------------
** Include Files
** ------------------------------------------------------------------- */
#include "board.h"
#include "arm_math.h"
#include "math_helper.h"

#include "fir_lpf_data.h"

/* -------------------------------------------------------------------
 * Declare Test output buffer
 * ------------------------------------------------------------------- */
static float32_t testOutput[TEST_LENGTH_SAMPLES];

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

  uint32_t i;
  arm_fir_instance_f32 S;
  arm_status status;
  float32_t  *inputF32, *outputF32;
  /* Initialize input and output buffer pointers */
  inputF32 = &testInput[0];
  outputF32 = &testOutput[0];
  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);
  /* ----------------------------------------------------------------------
  ** Call the FIR process function for every blockSize samples
  ** ------------------------------------------------------------------- */
  for(i=0; i < numBlocks; i++)
  {
    arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
  }
  /* ----------------------------------------------------------------------
  ** Compare the generated output against the reference output computed
  ** in MATLAB.
  ** ------------------------------------------------------------------- */
  snr = arm_snr_f32(&refOutput[0], &testOutput[0], TEST_LENGTH_SAMPLES);
  if (snr < SNR_THRESHOLD_F32)
  {
    status = ARM_MATH_TEST_FAILURE;
  }
  else
  {
    status = ARM_MATH_SUCCESS;
  }
  /* ----------------------------------------------------------------------
  ** Loop here if the signal does not match the reference output.
  ** ------------------------------------------------------------------- */
  if ( status != ARM_MATH_SUCCESS)
  {
    while (1);
  }
  while (1);                             /* main function does not return */
}
