clear; clc; close all;

x_i = [-2, 2, 4];
p_i = [.5, .3, .2];

[x, y] = plot_dyst(x_i, p_i);

z = [x;y];


plot(x, y, '-o');
grid on;