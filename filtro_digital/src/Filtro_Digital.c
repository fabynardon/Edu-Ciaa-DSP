///* ----------------------------------------------------------------------
//** Include Files
//** ------------------------------------------------------------------- */
//#include "board.h"
//#include "arm_math.h"
//#include "math_helper.h"
//
//#include "fir_lpf_data.h"
//
///* -------------------------------------------------------------------
// * Declare Test output buffer
// * ------------------------------------------------------------------- */
//static float32_t testOutput[TEST_LENGTH_SAMPLES];
//
///* -------------------------------------------------------------------
// * Declare State buffer of size (numTaps + blockSize - 1)
// * ------------------------------------------------------------------- */
//static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];
//
///* ------------------------------------------------------------------
// * Global variables for FIR LPF Example
// * ------------------------------------------------------------------- */
//uint32_t blockSize = BLOCK_SIZE;
//uint32_t numBlocks = TEST_LENGTH_SAMPLES/BLOCK_SIZE;
//float32_t  snr;
//
///* ----------------------------------------------------------------------
// * FIR LPF Example
// * ------------------------------------------------------------------- */
//int32_t main(void)
//{
//	SystemCoreClockUpdate();
//	Board_Init();
//
//  uint32_t i;
//  arm_fir_instance_f32 S;
//  arm_status status;
//  float32_t  *inputF32, *outputF32;
//  /* Initialize input and output buffer pointers */
//  inputF32 = &testInput[0];
//  outputF32 = &testOutput[0];
//  /* Call FIR init function to initialize the instance structure. */
//  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);
//  /* ----------------------------------------------------------------------
//  ** Call the FIR process function for every blockSize samples
//  ** ------------------------------------------------------------------- */
//  for(i=0; i < numBlocks; i++)
//  {
//    arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);
//  }
//  /* ----------------------------------------------------------------------
//  ** Compare the generated output against the reference output computed
//  ** in MATLAB.
//  ** ------------------------------------------------------------------- */
//  snr = arm_snr_f32(&refOutput[0], &testOutput[0], TEST_LENGTH_SAMPLES);
//  if (snr < SNR_THRESHOLD_F32)
//  {
//    status = ARM_MATH_TEST_FAILURE;
//  }
//  else
//  {
//    status = ARM_MATH_SUCCESS;
//  }
//  /* ----------------------------------------------------------------------
//  ** Loop here if the signal does not match the reference output.
//  ** ------------------------------------------------------------------- */
//  if ( status != ARM_MATH_SUCCESS)
//  {
//    while (1);
//  }
//  while (1);                             /* main function does not return */
//}
