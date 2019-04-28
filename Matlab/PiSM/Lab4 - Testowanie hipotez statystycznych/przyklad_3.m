close all; clear; clc;

% Porównanie wariancji (test F-Snedecora)

% Korzystajac z testy F-Snedecora dla nastepujacych zbiorów danych
% X = {x_i} oraz Y = {y_i} zweryfikujemy hipoteze
% H_0 : var_1 = var_2 na poziomie istotnosci alfa = 0.05
% przyjmujac, ze dane te pochodza z populacji o rozk³adzie normalnym.

x = [1.55508 -0.342242 1.0849 -0.362719 1.42819 -1.11659 -0.258791 1.05238 0.180204 1.80046 -1.09857 -0.216113];
y = [-1.11114 -0.909139 -0.572291 -0.223399 0.100347 1.35598 -1.68698 -0.446482 -0.52801 -0.724528 -1.0165 1.42809];
yN = length(y);
xN = length(x);
N = xN; % te same
x_mean = mean(x);
y_mean = mean(y);
alfa = 0.05;

S2x = var(x, 1);
S2y = var(y, 1);
if S2x > S2y
    F = S2x/S2y;
else
    F = S2y/S2x;
end

fprintf('Odcz. z tabeli p:=%.4f, v:=%.4f', 1-alfa/2, N-1);
t_alfa = 2.2010; % odczyt z tabelki (rêcznie)
t = (x_mean - y_mean) / sqrt( (N*S2x + N*S2y) / (N*(N-1)) );
t_alfa
t

% WTF ???