close all; clear; clc;

% Przyk�ad 1 dla
% nieznana warto�� przeci�tna
% wariancja znana
% wyznaczy� 90% przedzia� ufno�ci

n = 16; % liczebno�� pr�bki
x_sr = 173.24; % warto�� �rednia
odch_std = 4; % praw. wart. odch. standard.

alfa = 0.1; % wsp. ufno�ci

% Kwantyle u(p) rz�du p dla N(0, 1)
% p    0.90 0.95 0.975 0.99 0.995
% u(p) 1.28 1.64 1.96  2.33 2.58 
% z_alfa/2 = u(1 - alfa/2)

z_a2 = 1 - alfa/2; % p=0.95
% czyli 
p = 1.64;

g_up = x_sr + p * odch_std/sqrt(n);
g_down = x_sr - p * odch_std/sqrt(n);

fprintf('%.2f < u < %.2f\n', g_down, g_up);