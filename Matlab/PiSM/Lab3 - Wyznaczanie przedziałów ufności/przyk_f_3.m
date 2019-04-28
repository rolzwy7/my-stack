close all; clear; clc;

% Przedzia³y ufnoœci dla nieznanej wariancji
% próbki pochodz¹cej z populacji o rozk³adzie
% normalnym.

x = [8.591,8.35633,8.95066,9.2165,9.26367,8.85530,9.94805,9.69714,9.06728,9.46711];
n = length(x);
x_sr = mean(x);
x_var = var(x);

% Block 0.95 - start
p1 = 0.95;

alfa1 = 1 - p1;
fprintf('Odcz.1 z tabeli (%.4f, %.4f)\n', 1 - alfa1/2, n-1);
fprintf('Odcz.2 z tabeli (%.4f, %.4f)\n', alfa1/2, n-1);

odcz_1 = 19.0228; % to rêcznie
odcz_2 = 2.7004; % to rêcznie

k1 = ((n - 1) * x_var) / odcz_1;
k2 = ((n - 1) * x_var) / odcz_2;
fprintf('p = %.2f dolna: %.4f górna: %.4f\n', p1, k1, k2);
% Block - stop
fprintf('------------------------------\n');
% Block 0.99 - start
p2 = 0.99;

alfa2 = 1 - p1;
fprintf('Odcz.1 z tabeli (%.4f, %.4f)\n', 1 - alfa2/2, n-1);
fprintf('Odcz.2 z tabeli (%.4f, %.4f)\n', alfa2/2, n-1);

odcz_1 = 23.5894; % to rêcznie
odcz_2 = 1.7349; % to rêcznie

k1 = ((n - 1) * x_var) / odcz_1;
k2 = ((n - 1) * x_var) / odcz_2;
fprintf('p = %.2f dolna: %.4f górna: %.4f\n', p2, k1, k2);
% Block - stop
