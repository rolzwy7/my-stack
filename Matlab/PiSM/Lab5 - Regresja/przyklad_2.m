close all; clear; clc;

U = [10 20 30 40 50 60 70]; % V
I = [.04 .05 .05 .07 .065 .065 .08]; % A

X = U;
Y = I;
N = length(X);
p = 0.95;
a = 1 - p; % poziom istotno�ci

% Zak�adaj�c linow� zale�no�� mi�dzy nimi:
% - wyznaczy� posta� funkcji regresji
% - okre�lic w jakim stopniu otrzymany model
%        dopasowany jest do danych pomiarowych.
% - Podac zakres warto�ci parametr�w linii regresji 
% w jakim z poziomem ufno�ci 1 ? a = 0.95
% znajdzie si� funkcja regresji wynikaj�ca z populacji generalnej.

X_sum = sum(X);
Y_sum = sum(Y);
X_sum_sq = sum(X .* X);
Y_sum_sq = sum(Y .* Y);
XY_sum = sum(X .* Y);

a01_mianownik = N*(X_sum_sq)-(X_sum)^2;

a_0 = (X_sum_sq*Y_sum - X_sum*XY_sum) / a01_mianownik;
a_1 = (N*XY_sum-X_sum*Y_sum) / a01_mianownik;

% tStudenta

t_odczyt = abs(tinv(a/2, N-2)); % 2.4469

od_std_y = sqrt(1/(N-2) * sum((Y-a_0-a_1.*X).^2));

a_0pm = t_odczyt * od_std_y/sqrt(sum((X-mean(X)).^2));
a_1pm = t_odczyt * od_std_y/sqrt(N);

fprintf('a0 = %.6f +/- %.6f\n', a_0, a_0pm);
fprintf('a1 = %.6f +/- %.6f\n', a_1, a_1pm);
R2 = wsp_korelacji(X, Y)^2;
fprintf('R^2 = %.2f%%\n', R2*100);
