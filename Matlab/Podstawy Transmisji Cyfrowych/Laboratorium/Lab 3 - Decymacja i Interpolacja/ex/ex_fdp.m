close all; clear; clc;

load amdata23.mat

s_inf = signal;

N = 72000;

Ts = 1/f_probkowanie;

t = 0:Ts:(N-1)*Ts;

plot(signal);

n=0:N-1;

% sygna³ noœny
sc = cos(2*pi*f_c/f_probkowanie*n);

% Sygna³ Zmodulowany


% Modulator DSB-WC
mi = g;
k = 2*mi/( max(s_inf) * (1 - mi) - min(s_inf)*(1 + mi) );
s_rf = (1+k*s_inf) .* sc;

subplot(211);
plot(t, s_rf); title('Sygna³ zmodulowany');

% Widma
f = 0 : f_probkowanie/N : f_probkowanie-f_probkowanie/N;

subplot(212);
stem(f, abs(fft(s_rf))); title('Sygna³ zmodulowany (widmo)');
xlim([0 f_probkowanie/2]);

% DETEKTOR (demodulator koherentny)
sc1 = cos(2*pi*(f_c)*t);
sd1 = s_rf .* sc1;

% FDP
fcut = 200 / (f_probkowanie/2);
B = fir1(75, fcut);
sdem = filter(B, 1, sd1);

% ODP
figure;
subplot(211);
plot(t,s_inf); title('Oryginalny sygna³ informacyjny');
subplot(212); 
plot(t, sdem); title('Sygna³ odebrany');