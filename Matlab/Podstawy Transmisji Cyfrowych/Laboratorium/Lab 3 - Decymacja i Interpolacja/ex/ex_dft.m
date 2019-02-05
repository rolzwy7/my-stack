close all; clear; clc;

% Amplitudy
A1 = 5;
A2 = 2;

% Czestotliwosci
f1 = 6;
f2 = 41;

N = 128;
n = 0:N-1;

fs = 128;
Ts = 1/fs;

s = A1 * cos(2*pi*f1*Ts*n) + A2 * cos(2*pi*f2*Ts*n);

subplot(211);
plot(s);

w = 0:fs/(length(s)):fs-fs/length(s);

Sw = fft(s) /(N/2);

subplot(212);
stem(w, abs(Sw));