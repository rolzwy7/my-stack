close all; clear; clc;

% Przyk³ad 2 dla
% nieznana wartoœæ przeciêtna próbki
% maj¹cej cechy rozk³adu normalnego.
% wariancja nieznana

% tutej wchodzi rozk³ad studenta

% pliki; wyznaczyæ 95% dla 
% wartoœci œredniej
n = 23;
x_sr = 4822; % kB
od_std = 127;

alfa = 0.05;
v = n - 1; % stopnie swobody

T = 1 - alfa/2; % 0.975
% t_0.975,22 = 2.074
t = 2.074;
% kawntyle t(p,v), dla v stopni swobody

g_up = x_sr + t * od_std/sqrt(n);
g_down = x_sr - t * od_std/sqrt(n);

fprintf('%.2f < u < %.2f\n', g_down, g_up);