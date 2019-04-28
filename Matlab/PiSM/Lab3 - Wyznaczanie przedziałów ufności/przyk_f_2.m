close all; clear; clc;

x = [11.0552, 10.6477, 9.63204, 9.88118, 9.37967, 8.24137, 10.73796, 9.22886, 8.82199, 9.192863];
n = length(x);
x_sr = mean(x);
x_var = var(x);
x_ostd = sqrt(x_var);

% Block 0.95 - start
p1 = 0.95;

alfa1 = 1 - p1;
fprintf('Odcz. z tabeli %.4f, %.4f\n', 1 - alfa1/2, n-1);
odcz = 2.2622;

k1 = x_sr - odcz * x_ostd/sqrt(n);
k2 = x_sr + odcz * x_ostd/sqrt(n);

fprintf('p = %.2f dolna: %.4f górna: %.4f\n', p1, k1, k2);
% Block - stop
fprintf('------------------------------\n');
% Block 0.99 - start
p2 = 0.99;

alfa2 = 1 - p2;
fprintf('Odcz. z tabeli %.4f, %.4f\n', 1 - alfa2/2, n-1);
odcz = 3.2498;

k1 = x_sr - odcz * x_ostd/sqrt(n);
k2 = x_sr + odcz * x_ostd/sqrt(n);

fprintf('p = %.2f dolna: %.4f górna: %.4f\n', p2, k1, k2);
% Block - stop

