close all; clear; clc;

A = [2 3;4 -5];
B = [65;10];
M = A; M(:, end+1) = B;

%%%% Cramer, Gauss %%%%
cramer(M);
gauss(M);