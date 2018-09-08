path = '..\Filtro_Digital\src';
fid=fopen(fullfile(path,'fir_lpf_data.c'),'wt');

fprintf(fid,'/*===============================================================================\n');
fprintf(fid,'Name        : fir_lpf_data.c\n');
fprintf(fid,'Author      : Fabian Nardone\n');
fprintf(fid,'Description : Generacion de variables externas para filtros digitales\n');
fprintf(fid,'===============================================================================\n');
fprintf(fid,'*/\n\n');

fprintf(fid,'/* ----------------------------------------------------------------------\n');
fprintf(fid,'** Include Files\n');
fprintf(fid,'** ------------------------------------------------------------------- */\n');

fprintf(fid,'#include "arm_math.h"\n');
fprintf(fid,'#include "math_helper.h"\n\n');

fprintf(fid,'extern float32_t testInput_f32_1kHz_15kHz[%d]={\n',size(testInput,2));

for i=1:size(testInput,2)-1;
    
    fprintf(fid,'%+5.12ff,\t',testInput(i));
    if mod(i,16) == 0
        fprintf(fid,'\n');
    end
end
fprintf(fid,'%+5.12ff};\n\n',testInput(size(testInput,2)));

fprintf(fid,'extern float32_t refOutput[%d]={\n',size(testOutput,2));

for i=1:size(testOutput,2)-1;
    
    fprintf(fid,'%+5.12ff,\t',testOutput(i));
    if mod(i,16) == 0
        fprintf(fid,'\n');
    end
    
end
fprintf(fid,'%+5.12ff};\n',testOutput(size(testOutput,2)));
fclose(fid);