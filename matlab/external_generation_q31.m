%path = '..\arm_fir_example\inc';
path = '..\filtro_digital\inc';
fid=fopen(fullfile(path,'fir_lpf_data_q31.h'),'wt');

fprintf(fid,'/*===============================================================================\n');
fprintf(fid,'Name        : fir_lpf_data_q31.h\n');
fprintf(fid,'Author      : Fabian Nardone\n');
fprintf(fid,'Description : Generacion de variables externas para filtros digitales\n');
fprintf(fid,'=================================================================================\n');
fprintf(fid,'*/\n\n');

fprintf(fid,'/* ----------------------------------------------------------------------\n');
fprintf(fid,'** Include Files\n');
fprintf(fid,'** ------------------------------------------------------------------- */\n');

fprintf(fid,'#include "arm_math.h"\n');
fprintf(fid,'#include "math_helper.h"\n\n');

fprintf(fid,'/* ----------------------------------------------------------------------\n');
fprintf(fid,'** Macro Defines\n');
fprintf(fid,'** ------------------------------------------------------------------- */\n');

fprintf(fid,'#define TEST_LENGTH_SAMPLES %d\n',L);
fprintf(fid,'#define SNR_THRESHOLD_F32 %5.1ff\n',140);
fprintf(fid,'#define BLOCK_SIZE %d\n',L);
fprintf(fid,'#define NUM_TAPS %d\n\n',orden+1);

fprintf(fid,'/* ----------------------------------------------------------------------\n');
fprintf(fid,'** FIR Coefficients buffer generated using fir1() MATLABfunction.\n');
fprintf(fid,'** fir1(28, 6/24)\n');
fprintf(fid,'** ------------------------------------------------------------------- */\n');

fprintf(fid,'const float32_t firCoeffs32[NUM_TAPS]={\n');

for i=1:size(firCoeffsb,2)-1;
    
    fprintf(fid,'%+5.12ff,\t',firCoeffsb(i));
    if mod(i,6) == 0
        fprintf(fid,'\n');
    end
    
end

fprintf(fid,'%+5.12ff};\n\n',firCoeffsb(size(firCoeffsb,2)));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf(fid,'const q31_t testInputQ31[TEST_LENGTH_SAMPLES]={\n');

for i=1:size(testInput,2)-1;
    
    fprintf(fid,'%+d,\t',fix(testInput(i)));
    if mod(i,8) == 0
        fprintf(fid,'\n');
    end
    
end

fprintf(fid,'%+d};\n\n',fix(testInput(size(testInput,2))));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

fprintf(fid,'const q31_t refOutputQ31[TEST_LENGTH_SAMPLES]={\n');

for i=1:size(testOutput,2)-1;
    
    fprintf(fid,'%+d,\t',fix(testOutput(i)));
    if mod(i, 8) == 0
        fprintf(fid,'\n');
    end
    
end
fprintf(fid,'%+d};\n',fix(testOutput(size(testOutput,2))));
fclose(fid);