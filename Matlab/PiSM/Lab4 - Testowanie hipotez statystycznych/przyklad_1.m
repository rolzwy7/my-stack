close all; clear; clc;

% Hipoteza o sredniej, odstd nieznane

% Dla zbioru danych X = {x_i} zweryfikowac hipoteze
% H_0 : m = 0, wobec hipotezy alternatywnej H_1 : m != 0
% (wart. sredniej)

m_0 = 0; % H_0 : m = 0

x = [1.55508 -0.342242 1.0849 -0.362719 1.42819 -1.11659 -0.258791 1.05238 0.180204 1.80046 -1.09857 -0.216113];
% No. samples
N = length(x);
% Variance
x_var = var(x, 1); % var(x)
% Std. Dev.
x_ostd = sqrt(x_var);
% Average
x_mean = mean(x);
% Statystyka
t = (x_mean - m_0)/x_ostd * sqrt(N - 1);

% t-Studenta tabelka
stp_swobody = N - 1; % 11
alfa = 0.05;
fprintf('Odcz. z tabeli p:=%.4f, v:=%.4f', 1-alfa/2, stp_swobody);
t_alfa = 2.2010; % odczyt z tabelki (rêcznie)
fprintf(' -> t_alfa = %.4f\n', t_alfa);

fprintf('t      := %.4f\n', t);
fprintf('t_alfa := %.4f\n', t_alfa);

if abs(t) > t_alfa
    fprintf('- Wniosek: Odrzucamy H_0, przyjmujemy H_1\n');
else
    fprintf('- Wniosek: H_0 - brak podstaw do odrzucenia\n');
end

