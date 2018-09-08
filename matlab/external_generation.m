path = '..\Filtro_Digital\inc';
fid=fopen(fullfile(path,'fir_lpf_data.h'),'wt');

fprintf(fid,'/*===============================================================================\n');
fprintf(fid,'Name        : fir_lpf_data.h\n');
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
fprintf(fid,'#define BLOCK_SIZE %d\n',L/10);
fprintf(fid,'#define NUM_TAPS %d\n\n',orden+1);

fprintf(fid,'/* ----------------------------------------------------------------------\n');
fprintf(fid,'** FIR Coefficients buffer generated using fir1() MATLABfunction.\n');
fprintf(fid,'** fir1(28, 6/24)\n');
fprintf(fid,'** ------------------------------------------------------------------- */\n');

fprintf(fid,'const float32_t firCoeffs32[%d]={\n',size(firCoeffsb,2));

for i=1:size(firCoeffsb,2)-1;
    
    fprintf(fid,'%+5.12ff,\t',firCoeffsb(i));
    if mod(i,8) == 0
        fprintf(fid,'\n');
    end
end
fprintf(fid,'%+5.12ff};\n\n',firCoeffsb(size(firCoeffsb,2)));

fprintf(fid,'const float32_t testInput[%d]={\n',size(testInput,2));

for i=1:size(testInput,2)-1;
    
    fprintf(fid,'%+5.12ff,\t',testInput(i));
    if mod(i,8) == 0
        fprintf(fid,'\n');
    end
end
fprintf(fid,'%+5.12ff};\n\n',testInput(size(testInput,2)));

fprintf(fid,'const float32_t refOutput[%d]={\n',size(testOutput,2));

for i=1:size(testOutput,2)-1;
    
    fprintf(fid,'%+5.12ff,\t',testOutput(i));
    if mod(i,8) == 0
        fprintf(fid,'\n');
    end
    
end
fprintf(fid,'%+5.12ff};\n',testOutput(size(testOutput,2)));
fclose(fid);