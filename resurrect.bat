@echo OFF
SET /P source=path source:
SET /P destino=path dest:
SET repositorio=https://github.com/fabynardon/Edu-Ciaa-DSP/trunk/

svn copy %repositorio%%source% %destino%