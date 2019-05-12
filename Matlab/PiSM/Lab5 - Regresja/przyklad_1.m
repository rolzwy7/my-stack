close all; clc; clear;

U = [0 1 2 3 7]; % V
I = [0 3 5.1 7.9 18.4]; % mA
% Sprawdziæ czy istnieje liniowa zale¿noœæ pomiêdzy
% tymi pomiarami.

N = length(U);
p = 0.95;
a = 1 - p; % poziom istotnoœci

r_xy = wsp_korelacji(U, I);

% Hipoteza H_0 r = 0 (brak korelacji)
t = (r_xy * sqrt(N-2)) / sqrt(1-r_xy^2);
P = a/2;
V = N-2;
odczyt = abs(tinv(P, V)); % tinv(P, V);
fprintf('t(%.4f, %.1f) = %.4f\n', P, V, odczyt);
fprintf('|t| = %.4f\n', abs(t));

if abs(t) >= odczyt
    fprintf('Odrzucamy hipoteze H0\n')
else
    fprintf('Brak podstaw do odrzucenia H0\n')
end