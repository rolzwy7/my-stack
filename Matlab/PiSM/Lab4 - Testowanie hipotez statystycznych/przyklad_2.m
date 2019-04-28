close all; clear; clc;

% Hipoteza o wariancji

% Dla próbki o licznosci N = 15 pochodzacej z populacji o 
% rozk³adzie normalnym weryfikujemy na poziomie istotnosci
% alfa = 0,01 hipoteze 
% H: H_0 : odstd = 4 wobec hipotezy alternatywnej
% H_1 : odstd != 4. W próbce otrzymano wynik.

alfa_0 = 4; % H: H_0 : odstd = 4

otrz_wynik = 300; % (podane) suma kwadratów ró¿nic próbek i avg.
% podzielic przez N i bedzie wariancja
N = 15;
alfa = 0.01;
x_var = otrz_wynik / N;

fprintf('X2k_p z tabeli (%.4f, %.4f)\n', alfa/2, N-1);
fprintf('X2k   z tabeli (%.4f, %.4f)\n', 1 - alfa/2, N-1);

X2k_p = 4.0747; % to rêcznie
X2k = 31.3193; % to rêcznie

gXp = alfa_0^2 * X2k_p;
gX = alfa_0^2 * X2k;

fprintf('obszar kryt. %.4f < %.4f LUB %.4f > %.4f\n', gX, otrz_wynik, gXp, otrz_wynik);

fprintf('Wniosek:\n\t');
if gXp > otrz_wynik || gX < otrz_wynik
    fprintf('H_0 - odrzucamy\n');
else
    fprintf('H_0 - brak podstaw do odrzucenia\n');
end
