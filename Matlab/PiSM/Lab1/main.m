clear; clc; close all;

x_i = [-2, 2, 4];
p_i = [.5, .3, .2];

% zad 1
[x, y] = plot_dyst(x_i, p_i);
kw = .3;

hold on;
plot(x, y, 'o');
plot(x, kw * ones(1, length(x)), '-r', 'LineWidth', 2);
hold off;
grid on;

% zad 2
wp = wart_przec(x_i, p_i);
war = wariancja(x_i, p_i, wp);
odstd = sqrt(war);
opowp = odch_przec_od_war_przec(x_i, p_i, wp);

mc_4 = mom_centr_rz(4, x_i, p_i, wp);
kurtoza = mc_4 / odstd^4;