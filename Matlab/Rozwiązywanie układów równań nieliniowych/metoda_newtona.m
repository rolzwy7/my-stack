close all; clear; clc;

%%%%%%%%%%%%%%%%%%% Rozwi�zania - start %%%%%%%%%%%%%%%%%%%
K = 3;
wyniki = ones(K, 2);

syms f(x);
f(x) = sin(2*x) + x - 2;
fd(x) = diff(f(x));

a = 2.3; % a - pocz�tek przedzia�u
b = 3;   % b - koniec przedzia�u

if f(a) * fd(a) > 0
    xk = a;
end
if f(b) * fd(b) > 0
    xk = b;
end

for k=1:K
    xk = xk - (f(xk)/fd(xk));
    wyniki(k, :) = [xk, f(xk)];
end
%%%%%%%%%%%%%%%%%%% Rozwi�zania - koniec %%%%%%%%%%%%%%%%%%%




