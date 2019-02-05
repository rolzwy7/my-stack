close all; clear; clc;

%%%%%%%%%%%%%%%%%%% Rozwi¹zania - start %%%%%%%%%%%%%%%%%%%
K = 3;
wyniki = ones(K, 2);

syms f(x);
f(x) = sin(2*x) + x - 2;
fd(x) = diff(f(x));

a = 2.3; % a - pocz¹tek przedzia³u
b = 3;   % b - koniec przedzia³u

x0 = a;
x1 = b;

for k=1:K
    xk = x1 - ((f(x1)*(x1-x0))/(f(x1)-f(x0)));
    x0 = x1;
    x1 = xk;
    wyniki(k, :) = [xk, f(xk)];
end
%%%%%%%%%%%%%%%%%%% Rozwi¹zania - koniec %%%%%%%%%%%%%%%%%%%




