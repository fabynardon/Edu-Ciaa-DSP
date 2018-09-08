clf, clc, clear all

Fs=48000; Ts = 1/Fs; L =320; t = (0:L-1)*Ts; f = Fs*(0:(L/2))/L;
Fc = 4000;  orden = 88;

S = sin(2*pi*1000*t)+1;
%S = square(2*pi*3000*t);
testInput = S + 0*rand(size(S));

% for i=0:319;
%     if mod(i,40) == 0
%         testInput(i+1)=1;
%     end
% end

testInput(1)=1;
figure(1)
subplot(221)
plot(1000*t,testInput)
title('Signal Corrupted with Zero-Mean Random Noise')
xlabel('t (milliseconds)')
ylabel('X(t)')
grid on

Y = fft(testInput);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

figure(1)
subplot(223)
plot(f*0.001,P1)
title('Single-Sided Amplitude Spectrum of testInput(t)')
xlabel('f (Khz)')
ylabel('|P1(f)|')
grid on

[firCoeffsb, firCoeffsa] = fir1(orden, 2*Fc/Fs);
%[firCoeffs, firTime] = impz(firCoeffsb, firCoeffsa);
[h,w] = freqz(firCoeffsb,firCoeffsa,length(f));

% figure(2)
% subplot(121)
% plot(1000*Ts*firTime, firCoeffs), %xlim(1000*Ts*[firTime(1) firTime(end)])
% title('Respuesta Impulsiva del filtro (t)')
% xlabel('t (milliseconds)')
% grid on
% subplot(122)
% plot(0.001*Fs*w/(2*pi),abs(h),'r'), xlim([0 0.001*Fs/2]), grid on
% title('Single-Sided Amplitude Spectrum of Respuesta Impulsiva(t)')
% xlabel('f (Khz)')
% ylabel('|P1(f)|')

testOutput = filter(firCoeffsb,firCoeffsa,testInput);

figure(1)
subplot(222)
plot(1000*t,testOutput)
title('Filtered Signal')
xlabel('t (milliseconds)')
ylabel('X(t)')
grid on

Y = fft(testOutput); 
P2 = abs(Y/L); 
P1 = P2(1:L/2+1); 
P1(2:end-1) = 2*P1(2:end-1);

figure(1),subplot(224)
[ax,h1,h2] = plotyy(f*0.001,P1,f*0.001,abs(h));
title('Single-Sided Amplitude Spectrum of testOutput(t)')
xlabel('f (Khz)')
ylabel('|P1(f)|')
grid on
set(ax(2),'Ylim',[0 1])

external_generation