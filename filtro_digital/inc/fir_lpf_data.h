/*===============================================================================
Name        : fir_lpf_data.h
Author      : Fabian Nardone
Description : Generacion de variables externas para filtros digitales
=================================================================================
*/

/* ----------------------------------------------------------------------
** Include Files
** ------------------------------------------------------------------- */
#include "arm_math.h"
#include "math_helper.h"

/* ----------------------------------------------------------------------
** Macro Defines
** ------------------------------------------------------------------- */
#define TEST_LENGTH_SAMPLES 320
#define SNR_THRESHOLD_F32 140.0f
#define BLOCK_SIZE 32
#define NUM_TAPS 89

/* ----------------------------------------------------------------------
** FIR Coefficients buffer generated using fir1() MATLABfunction.
** fir1(28, 6/24)
** ------------------------------------------------------------------- */
const float32_t firCoeffs32[89]={
-0.000500950326f,	-0.000300285708f,	+0.000000000000f,	+0.000351173026f,	+0.000679392309f,	+0.000889203307f,	
+0.000881449851f,	+0.000585851863f,	-0.000000000000f,	-0.000780599070f,	-0.001558771144f,	-0.002070176082f,	
-0.002055778568f,	-0.001356392010f,	+0.000000000000f,	+0.001752796057f,	+0.003433298871f,	+0.004468734086f,	
+0.004349051565f,	+0.002813811916f,	-0.000000000000f,	-0.003507796684f,	-0.006762829398f,	-0.008678058733f,	
-0.008340964545f,	-0.005339665397f,	+0.000000000000f,	+0.006557119428f,	+0.012589507822f,	+0.016129047306f,	
+0.015521664126f,	+0.009980829856f,	-0.000000000000f,	-0.012512821372f,	-0.024456627463f,	-0.032106216223f,	
-0.031925385412f,	-0.021446060218f,	+0.000000000000f,	+0.030891895192f,	+0.067597200289f,	+0.104933897595f,	
+0.137116322169f,	+0.158886654996f,	+0.166580953452f,	+0.158886654996f,	+0.137116322169f,	+0.104933897595f,	
+0.067597200289f,	+0.030891895192f,	+0.000000000000f,	-0.021446060218f,	-0.031925385412f,	-0.032106216223f,	
-0.024456627463f,	-0.012512821372f,	-0.000000000000f,	+0.009980829856f,	+0.015521664126f,	+0.016129047306f,	
+0.012589507822f,	+0.006557119428f,	+0.000000000000f,	-0.005339665397f,	-0.008340964545f,	-0.008678058733f,	
-0.006762829398f,	-0.003507796684f,	-0.000000000000f,	+0.002813811916f,	+0.004349051565f,	+0.004468734086f,	
+0.003433298871f,	+0.001752796057f,	+0.000000000000f,	-0.001356392010f,	-0.002055778568f,	-0.002070176082f,	
-0.001558771144f,	-0.000780599070f,	-0.000000000000f,	+0.000585851863f,	+0.000881449851f,	+0.000889203307f,	
+0.000679392309f,	+0.000351173026f,	+0.000000000000f,	-0.000300285708f,	-0.000500950326f};

const float32_t testInput[320]={
+1.000000000000f,	+1.130526192220f,	+1.258819045103f,	+1.382683432365f,	+1.500000000000f,	+1.608761429009f,	
+1.707106781187f,	+1.793353340291f,	+1.866025403784f,	+1.923879532511f,	+1.965925826289f,	+1.991444861374f,	
+2.000000000000f,	+1.991444861374f,	+1.965925826289f,	+1.923879532511f,	+1.866025403784f,	+1.793353340291f,	
+1.707106781187f,	+1.608761429009f,	+1.500000000000f,	+1.382683432365f,	+1.258819045103f,	+1.130526192220f,	
+1.000000000000f,	+0.869473807780f,	+0.741180954897f,	+0.617316567635f,	+0.500000000000f,	+0.391238570991f,	
+0.292893218813f,	+0.206646659709f,	+0.133974596216f,	+0.076120467489f,	+0.034074173711f,	+0.008555138626f,	
+0.000000000000f,	+0.008555138626f,	+0.034074173711f,	+0.076120467489f,	+0.133974596216f,	+0.206646659709f,	
+0.292893218813f,	+0.391238570991f,	+0.500000000000f,	+0.617316567635f,	+0.741180954897f,	+0.869473807780f,	
+1.000000000000f,	+1.130526192220f,	+1.258819045103f,	+1.382683432365f,	+1.500000000000f,	+1.608761429009f,	
+1.707106781187f,	+1.793353340291f,	+1.866025403784f,	+1.923879532511f,	+1.965925826289f,	+1.991444861374f,	
+2.000000000000f,	+1.991444861374f,	+1.965925826289f,	+1.923879532511f,	+1.866025403784f,	+1.793353340291f,	
+1.707106781187f,	+1.608761429009f,	+1.500000000000f,	+1.382683432365f,	+1.258819045103f,	+1.130526192220f,	
+1.000000000000f,	+0.869473807780f,	+0.741180954897f,	+0.617316567635f,	+0.500000000000f,	+0.391238570991f,	
+0.292893218813f,	+0.206646659709f,	+0.133974596216f,	+0.076120467489f,	+0.034074173711f,	+0.008555138626f,	
+0.000000000000f,	+0.008555138626f,	+0.034074173711f,	+0.076120467489f,	+0.133974596216f,	+0.206646659709f,	
+0.292893218813f,	+0.391238570991f,	+0.500000000000f,	+0.617316567635f,	+0.741180954897f,	+0.869473807780f,	
+1.000000000000f,	+1.130526192220f,	+1.258819045103f,	+1.382683432365f,	+1.500000000000f,	+1.608761429009f,	
+1.707106781187f,	+1.793353340291f,	+1.866025403784f,	+1.923879532511f,	+1.965925826289f,	+1.991444861374f,	
+2.000000000000f,	+1.991444861374f,	+1.965925826289f,	+1.923879532511f,	+1.866025403784f,	+1.793353340291f,	
+1.707106781187f,	+1.608761429009f,	+1.500000000000f,	+1.382683432365f,	+1.258819045103f,	+1.130526192220f,	
+1.000000000000f,	+0.869473807780f,	+0.741180954897f,	+0.617316567635f,	+0.500000000000f,	+0.391238570991f,	
+0.292893218813f,	+0.206646659709f,	+0.133974596216f,	+0.076120467489f,	+0.034074173711f,	+0.008555138626f,	
+0.000000000000f,	+0.008555138626f,	+0.034074173711f,	+0.076120467489f,	+0.133974596216f,	+0.206646659709f,	
+0.292893218813f,	+0.391238570991f,	+0.500000000000f,	+0.617316567635f,	+0.741180954897f,	+0.869473807780f,	
+1.000000000000f,	+1.130526192220f,	+1.258819045103f,	+1.382683432365f,	+1.500000000000f,	+1.608761429009f,	
+1.707106781187f,	+1.793353340291f,	+1.866025403784f,	+1.923879532511f,	+1.965925826289f,	+1.991444861374f,	
+2.000000000000f,	+1.991444861374f,	+1.965925826289f,	+1.923879532511f,	+1.866025403784f,	+1.793353340291f,	
+1.707106781187f,	+1.608761429009f,	+1.500000000000f,	+1.382683432365f,	+1.258819045103f,	+1.130526192220f,	
+1.000000000000f,	+0.869473807780f,	+0.741180954897f,	+0.617316567635f,	+0.500000000000f,	+0.391238570991f,	
+0.292893218813f,	+0.206646659709f,	+0.133974596216f,	+0.076120467489f,	+0.034074173711f,	+0.008555138626f,	
+0.000000000000f,	+0.008555138626f,	+0.034074173711f,	+0.076120467489f,	+0.133974596216f,	+0.206646659709f,	
+0.292893218813f,	+0.391238570991f,	+0.500000000000f,	+0.617316567635f,	+0.741180954897f,	+0.869473807780f,	
+1.000000000000f,	+1.130526192220f,	+1.258819045103f,	+1.382683432365f,	+1.500000000000f,	+1.608761429009f,	
+1.707106781187f,	+1.793353340291f,	+1.866025403784f,	+1.923879532511f,	+1.965925826289f,	+1.991444861374f,	
+2.000000000000f,	+1.991444861374f,	+1.965925826289f,	+1.923879532511f,	+1.866025403784f,	+1.793353340291f,	
+1.707106781187f,	+1.608761429009f,	+1.500000000000f,	+1.382683432365f,	+1.258819045103f,	+1.130526192220f,	
+1.000000000000f,	+0.869473807780f,	+0.741180954897f,	+0.617316567635f,	+0.500000000000f,	+0.391238570991f,	
+0.292893218813f,	+0.206646659709f,	+0.133974596216f,	+0.076120467489f,	+0.034074173711f,	+0.008555138626f,	
+0.000000000000f,	+0.008555138626f,	+0.034074173711f,	+0.076120467489f,	+0.133974596216f,	+0.206646659709f,	
+0.292893218813f,	+0.391238570991f,	+0.500000000000f,	+0.617316567635f,	+0.741180954897f,	+0.869473807780f,	
+1.000000000000f,	+1.130526192220f,	+1.258819045103f,	+1.382683432365f,	+1.500000000000f,	+1.608761429009f,	
+1.707106781187f,	+1.793353340291f,	+1.866025403784f,	+1.923879532511f,	+1.965925826289f,	+1.991444861374f,	
+2.000000000000f,	+1.991444861374f,	+1.965925826289f,	+1.923879532511f,	+1.866025403784f,	+1.793353340291f,	
+1.707106781187f,	+1.608761429009f,	+1.500000000000f,	+1.382683432365f,	+1.258819045103f,	+1.130526192220f,	
+1.000000000000f,	+0.869473807780f,	+0.741180954897f,	+0.617316567635f,	+0.500000000000f,	+0.391238570991f,	
+0.292893218813f,	+0.206646659709f,	+0.133974596216f,	+0.076120467489f,	+0.034074173711f,	+0.008555138626f,	
+0.000000000000f,	+0.008555138626f,	+0.034074173711f,	+0.076120467489f,	+0.133974596216f,	+0.206646659709f,	
+0.292893218813f,	+0.391238570991f,	+0.500000000000f,	+0.617316567635f,	+0.741180954897f,	+0.869473807780f,	
+1.000000000000f,	+1.130526192220f,	+1.258819045103f,	+1.382683432365f,	+1.500000000000f,	+1.608761429009f,	
+1.707106781187f,	+1.793353340291f,	+1.866025403784f,	+1.923879532511f,	+1.965925826289f,	+1.991444861374f,	
+2.000000000000f,	+1.991444861374f,	+1.965925826289f,	+1.923879532511f,	+1.866025403784f,	+1.793353340291f,	
+1.707106781187f,	+1.608761429009f,	+1.500000000000f,	+1.382683432365f,	+1.258819045103f,	+1.130526192220f,	
+1.000000000000f,	+0.869473807780f,	+0.741180954897f,	+0.617316567635f,	+0.500000000000f,	+0.391238570991f,	
+0.292893218813f,	+0.206646659709f};

const float32_t refOutput[320]={
-0.000500950326f,	-0.000866623172f,	-0.000970086669f,	-0.000719488059f,	-0.000090222949f,	+0.000842999276f,	
+0.001889246819f,	+0.002756843383f,	+0.003112131086f,	+0.002677814635f,	+0.001348507410f,	-0.000714521480f,	
-0.003052343615f,	-0.004973264853f,	-0.005719332228f,	-0.004704331588f,	-0.001759146496f,	+0.002698856843f,	
+0.007649895716f,	+0.011652491121f,	+0.013207341390f,	+0.011226581681f,	+0.005478988594f,	-0.003137872492f,	
-0.012622712756f,	-0.020247755585f,	-0.023243783141f,	-0.019645112338f,	-0.009069978503f,	+0.006810620639f,	
+0.024316016051f,	+0.038399535039f,	+0.043827759867f,	+0.036673060873f,	+0.015779523449f,	-0.016178580061f,	
-0.052371836028f,	-0.082405122465f,	-0.093796948110f,	-0.074107288116f,	-0.013298857780f,	+0.094166896554f,	
+0.247965798312f,	+0.441600961522f,	+0.663243393848f,	+0.897566688691f,	+1.128199762375f,	+1.340288826961f,	
+1.522645505764f,	+1.669064207571f,	+1.778590642885f,	+1.854764417556f,	+1.904082691589f,	+1.934086031415f,	
+1.951518541724f,	+1.960956176777f,	+1.964151352992f,	+1.960150659428f,	+1.946056087957f,	+1.918164153491f,	
+1.873160423983f,	+1.809075484171f,	+1.725805923552f,	+1.625138085595f,	+1.510344461820f,	+1.385518943551f,	
+1.254857169925f,	+1.122068877201f,	+0.990043721505f,	+0.860804564431f,	+0.735699572778f,	+0.615728572976f,	
+0.501881267340f,	+0.395384140514f,	+0.297797735815f,	+0.210959401936f,	+0.136811719370f,	+0.077181901361f,	
+0.033578732541f,	+0.007055123087f,	-0.001844458124f,	+0.006939404628f,	+0.033052656241f,	+0.075814312341f,	
+0.134291371225f,	+0.207349104678f,	+0.293677688337f,	+0.391805066241f,	+0.500107539716f,	+0.617398874970f,	
+0.741236621551f,	+0.869501881279f,	+1.000000000000f,	+1.130498118721f,	+1.258763378449f,	+1.382601125030f,	
+1.499892460284f,	+1.608630496946f,	+1.706954697062f,	+1.793182706305f,	+1.865839139533f,	+1.923680825026f,	
+1.965718075511f,	+1.991231621976f,	+1.999784920568f,	+1.991231621976f,	+1.965718075511f,	+1.923680825026f,	
+1.865839139533f,	+1.793182706305f,	+1.706954697062f,	+1.608630496946f,	+1.499892460284f,	+1.382601125030f,	
+1.258763378449f,	+1.130498118721f,	+1.000000000000f,	+0.869501881279f,	+0.741236621551f,	+0.617398874970f,	
+0.500107539716f,	+0.391369503054f,	+0.293045302938f,	+0.206817293695f,	+0.134160860467f,	+0.076319174974f,	
+0.034281924489f,	+0.008768378024f,	+0.000215079432f,	+0.008768378024f,	+0.034281924489f,	+0.076319174974f,	
+0.134160860467f,	+0.206817293695f,	+0.293045302938f,	+0.391369503054f,	+0.500107539716f,	+0.617398874970f,	
+0.741236621551f,	+0.869501881279f,	+1.000000000000f,	+1.130498118721f,	+1.258763378449f,	+1.382601125030f,	
+1.499892460284f,	+1.608630496946f,	+1.706954697062f,	+1.793182706305f,	+1.865839139533f,	+1.923680825026f,	
+1.965718075511f,	+1.991231621976f,	+1.999784920568f,	+1.991231621976f,	+1.965718075511f,	+1.923680825026f,	
+1.865839139533f,	+1.793182706305f,	+1.706954697062f,	+1.608630496946f,	+1.499892460284f,	+1.382601125030f,	
+1.258763378449f,	+1.130498118721f,	+1.000000000000f,	+0.869501881279f,	+0.741236621551f,	+0.617398874970f,	
+0.500107539716f,	+0.391369503054f,	+0.293045302938f,	+0.206817293695f,	+0.134160860467f,	+0.076319174974f,	
+0.034281924489f,	+0.008768378024f,	+0.000215079432f,	+0.008768378024f,	+0.034281924489f,	+0.076319174974f,	
+0.134160860467f,	+0.206817293695f,	+0.293045302938f,	+0.391369503054f,	+0.500107539716f,	+0.617398874970f,	
+0.741236621551f,	+0.869501881279f,	+1.000000000000f,	+1.130498118721f,	+1.258763378449f,	+1.382601125030f,	
+1.499892460284f,	+1.608630496946f,	+1.706954697062f,	+1.793182706305f,	+1.865839139533f,	+1.923680825026f,	
+1.965718075511f,	+1.991231621976f,	+1.999784920568f,	+1.991231621976f,	+1.965718075511f,	+1.923680825026f,	
+1.865839139533f,	+1.793182706305f,	+1.706954697062f,	+1.608630496946f,	+1.499892460284f,	+1.382601125030f,	
+1.258763378449f,	+1.130498118721f,	+1.000000000000f,	+0.869501881279f,	+0.741236621551f,	+0.617398874970f,	
+0.500107539716f,	+0.391369503054f,	+0.293045302938f,	+0.206817293695f,	+0.134160860467f,	+0.076319174974f,	
+0.034281924489f,	+0.008768378024f,	+0.000215079432f,	+0.008768378024f,	+0.034281924489f,	+0.076319174974f,	
+0.134160860467f,	+0.206817293695f,	+0.293045302938f,	+0.391369503054f,	+0.500107539716f,	+0.617398874970f,	
+0.741236621551f,	+0.869501881279f,	+1.000000000000f,	+1.130498118721f,	+1.258763378449f,	+1.382601125030f,	
+1.499892460284f,	+1.608630496946f,	+1.706954697062f,	+1.793182706305f,	+1.865839139533f,	+1.923680825026f,	
+1.965718075511f,	+1.991231621976f,	+1.999784920568f,	+1.991231621976f,	+1.965718075511f,	+1.923680825026f,	
+1.865839139533f,	+1.793182706305f,	+1.706954697062f,	+1.608630496946f,	+1.499892460284f,	+1.382601125030f,	
+1.258763378449f,	+1.130498118721f,	+1.000000000000f,	+0.869501881279f,	+0.741236621551f,	+0.617398874970f,	
+0.500107539716f,	+0.391369503054f,	+0.293045302938f,	+0.206817293695f,	+0.134160860467f,	+0.076319174974f,	
+0.034281924489f,	+0.008768378024f,	+0.000215079432f,	+0.008768378024f,	+0.034281924489f,	+0.076319174974f,	
+0.134160860467f,	+0.206817293695f,	+0.293045302938f,	+0.391369503054f,	+0.500107539716f,	+0.617398874970f,	
+0.741236621551f,	+0.869501881279f,	+1.000000000000f,	+1.130498118721f,	+1.258763378449f,	+1.382601125030f,	
+1.499892460284f,	+1.608630496946f,	+1.706954697062f,	+1.793182706305f,	+1.865839139533f,	+1.923680825026f,	
+1.965718075511f,	+1.991231621976f,	+1.999784920568f,	+1.991231621976f,	+1.965718075511f,	+1.923680825026f,	
+1.865839139533f,	+1.793182706305f,	+1.706954697062f,	+1.608630496946f,	+1.499892460284f,	+1.382601125030f,	
+1.258763378449f,	+1.130498118721f,	+1.000000000000f,	+0.869501881279f,	+0.741236621551f,	+0.617398874970f,	
+0.500107539716f,	+0.391369503054f,	+0.293045302938f,	+0.206817293695f,	+0.134160860467f,	+0.076319174974f,	
+0.034281924489f,	+0.008768378024f};
