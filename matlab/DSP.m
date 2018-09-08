%% Generacion y grafica de una señal muestreada a 8KHz.
% Se genera una señal sinusoidal de 400Hz y amplitud 2.
F0=400;
A=2;
phi=pi/4;
Fs=8000;
Ts=1/Fs;
t=-0.002:Ts:0.002;
%t=linspace(-0.002,0.002,0.004/Ts);
xt=A*sin(2*pi*F0*t+phi);
stem(t,xt)
%% Señales no sinusoidales periodicas. 
% Generacion de una señal diente de sierra.
F0=400;
A=2;
Fs=8000;
Ts=1/Fs;
t=-0.002:Ts:0.002;
xt=A*sawtooth(2*pi*F0*t);
stem(t,xt)
hold on
plot(t,xt)
xlabel('time (s)');
ylabel('x(t)');
%% Señal aperiodica.
% Muestreo de la señal Sinc.
F0=400;
A=2;
Fs=8000;
Ts=1/Fs;
t=-0.003:Ts:0.003;
xt=A*sinc(2*F0*t);
stem(t,xt)
%% Generacion e Ruido.
% Se utilizan los comandos:
% Y=rand(rows,cols): Genera ruido con distribucion uniforme.
% Y=randn(rows,cols): Genera ruido Gaussiano.
% Donde: rows, cols: indica la dimension del a matriz de ruido aleatorio a
% gneerar
% Para observar el histograma se utiliza el comando:
% hist(y,m): Representa el ruido "y" mediante m "contenedores".
%% Generacion y Representacion de Ruido Gaussiano.
Gnoise=randn(1,1e6);
hist(Gnoise,100);
%% Submuestreo y Sobremuestreo
% Submuestreo
%   xtDown=downsample(xt,N)
% La señal xDown tendra una frecuencia de muestreo Fs/N.
% Submuestrear la señal significa conservar cada N-esima muestra y eliminar
% las muestras restantes.
% Sobremuestreo
%   xtUp=upsample(xt,N)
% La seña xUp tendra una frecuencia de muestreo N*Fs.
% Sobremuestrear la señal significa introducir N-1 ceros entre muestras
% consecutivas.
%% Submuestreo. 
% Se submuestrea la señal sinusoidal generada anteriormente (Fs=8KHz) para obtener una señal xtDown muestreada a 2KHz.
F0=400;
A=2;
phi=pi/4;
Fs=8000;
Ts=1/Fs;
t=-0.002:Ts:0.002;
xt=A*sin(2*pi*F0*t+phi);
stem(t,xt)
xtDown=downsample(xt,4);
tDown=downsample(t,4);
hold on
stem(tDown,xtDown,'r');
%%  Procesamiento de Audio.
% Para escuchar un tono de señal en Matlab se utiliza el comando:
%   soundsc(xt,Fs)
% Donde:    xt: Tono a escuchar.
%           Fs: Frecuencai de muestreo.
% Para escuchar la señal sinusoidal generada anteriormente:
soundsc(xt,Fs)
%% Grabacion de Audio
% Para grabar una señal audible mediante la tarjeta de sonido y un
% microfono se utilizan los siguientes comandos:
% r=audiorecorder: Crea un objeto de grabacion.
% record(r): inicio de grabacion.
% pause(r), stop(r): Pausa y finalizacion.
% play(r): Escuchar la grabacion
% y=getaudiodata(r): Para obtener la matriz que contiene las muestras de la
% señal audible. Esta es la señal que se puede procesar.
% Fs=r.SampleRate: Para obtener la frecuencia de muestreo.
r=audiorecorder;
record(r)
pause(r)
record(r)
stop(r)
play(r)
y=getaudiodata(r);
Fs=r.SampleRate
%% Guardar como Archivo de Audio
% Para guardar la señal de audio que se acaba de grabar se utiliza el
% comando:
%   audiowrite('grabacion.wav',y,Fs)
% Se guarda en formato wav en la carpeta de trabajo de Matlab
audiowrite('grabacion.wav',y,Fs)
which grabacion.wav
%% Leer un Archivo de Audio
% Para leer un archivo de audio en formato wav que se encuentra en la
% carpeta de trabajo de Matlab se utiliza la funcion:
%   [xt,Fs]=audioread('nombre_de_archivo.wav')
% Se guardan las muestras y la frecuencia de muestreo xt y Fs
% respectivamente
[xt,Fs]=audioread('grabacion.wav');
%% Analisis en Frecuencia
% Transformada Rapida de Fourier
%   xF=fft(xt,nFFT)
% Donde:    nFFT=numero de puntos a representar.
% Comandos adicionales:
%   magxF=abs(xF): Magnitud de la fft de xt.
%   phasexF=angle(xF): Fase de ka fft de xt.
%   phasexF=unwrap(phasexF): para obtener la apropiada informacion de fase.
%% Obtencion de la FFT de la funcion Compuerta.
Fs=2000;
Ts=1/Fs;
t=-0.005:Ts:0.005;
xt=rectpuls(t,0.004);
nFFT=64;
xF=fft(xt,nFFT);
magxF=abs(xF);
phasexF=angle(xF);
phasexF=unwrap(phasexF);
figure,stem(magxF);
title('Magnitud de xF')
figure,stem(phasexF)
title('Fase de xF')
%% Obtencion de la FFt de la funcion Compuerta.
% El comando fft obtiene la transformada de Fourier en la region
% entre 0 y la frecuencia de muestreo Fs. se requiere desplazar una parte
% de la grafica para obtener la region negativa de la transformada de
% Fourier.
magxF=fftshift(magxF);
phasexF=fftshift(phasexF);
stem(magxF);
title('Magnitud de xF')
figure,stem(phasexF)
title('Fase de xF')
%% Obtencion de la FFt de la funcion Compuerta.
% Los graficos anteriores no presentan el eje de frecuencia correcto. Se
% debe crear el vector de eje de frecuencias para graficar correctamente.
f_eje=linspace(-Fs/2,Fs/2,nFFT);
stem(f_eje,magxF)
figure,stem(f_eje,phasexF)
%% Representacion de Filtros en Matlab
% Para representar la funcion de transferencia del filtro:
% H(z)=(1+1.1*z^-1)/(1-0.1*z^-2)
% en Matlab:
num=[1 1.1];
den=[1 0 -0.1];
%% Respuesta al Impulso y Convolucion
% Para obtener la respuesta al impulso se utilizan los comandos:
%   impz(num,den): Grafica la repsuesta al impulso del filtro. Por defecto
%   se considera Fs=1 Hz y grafica las 10 primeras muestras.
%   imps(num,den,n,Fs): Grafica la respuesta al impulso. Se especifica el
%   numero de muestras a graficar y la frecuencia de muestreo utilizada.
%   [h,t]=impz(num,den,n,Fs): Guarda los vectores de magnitud y eje de
%   tiempo en h y t respectivamente.
%% Graficando la respuesta al impulso del filtro creado anteriormente.
num=[1 1.1];
den=[1 0 -0.1];
impz(num,den);
Fs=8000;
[h,t]=impz(num,den,32,Fs);
figure,stem(t,h,'filled')
%% Señal de Salida del Filtro Para una Señal de Entrada
% Se realiza mediante los comandos:
%   y=conv(h,x)
% Donde:    h es la respuesta al impulso del filtro
%           x es la señal de entrada.
%   y=filter(num,den,x)
% Donde:    x es la señal de entrada.
% Se obtendra la señal de salida del filtro para una señal de entrada
% audible:
[xt,Fs]=audioread('grabacion.wav');
[h,t]=impz(num,den,10,Fs);
y1=convn(h,xt);
soundsc(xt,Fs);
soundsc(y1,Fs);
y2=filter(num,den,xt);
soundsc(xt,Fs);
soundsc(y2,Fs);
%% Respuesta de Magnitud y Fase de filtros
% Se utilizan los comandos:
%   [H,F]=freqz(num,den): Por defecto asume 512 puntos equidistantemente
%   espaciados y el eje de frecuencias es normalizada.
%   [H,F]=freqz(num,den,n,Fs): Donde se especifica numero de puntos n y la frecuencia de muestreo Fs.
%   [H,F]=freqz(num,den,f,Fs): Donde f es un vector en el que se especifica
%   las frecuencias particulares en las que se obtendra la respuesta de
%   magnitud y fase.
%% Respuesta en frecuencia del filtro creado anteriormente.
num=[1 1.1];
den=[1 0 -0.1];
Fs=8000;
freqz(num,den)
figure,freqz(num,den,1024,Fs);
f=[0,200,400];
[H,F]=freqz(num,den,f,Fs);
%% Grafico de Retardo de Grupo
% Se utilizan los comandos:
%   [G,F]=grpdelay(num,den)
%   [G,F]=grpdelay(num,den,n,Fs)
%   [G,F]=grpdelay(num,den,f,Fs)
% Los argumentos son iguales a los del caso anterior.
[G,F]=grpdelay(num,den);
grpdelay(num,den);
figure,grpdelay(num,den,1024,Fs);