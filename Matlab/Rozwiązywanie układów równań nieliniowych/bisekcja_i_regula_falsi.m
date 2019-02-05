close all; clear; clc;

%%%%%%%%%%%%%%%%%%% Pomocnicze - start %%%%%%%%%%%%%%%%%%%
% x = -1:0.01:5;
% f1 = 2 - x;
% f2 = sin(2*x);
% 
% % Plot
% hold on;
% plot(x, f1); plot(x, f2); grid on;
% hold off;
%%%%%%%%%%%%%%%%%%% Pomocnicze - koniec %%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%% Rozwi¹zania - start %%%%%%%%%%%%%%%%%%%
K = 4;
wyniki = ones(K, 2);

syms f(x);
f(x) = sin(2*x) + x - 2;

ak = 2.3; % a - pocz¹tek przedzia³u
bk = 3;   % b - koniec przedzia³u

for k=1:K
    disp(k);
    
    f_bk = f(bk);
    f_ak = f(ak);
    
    xk = (ak + bk) / 2;                         % xk dla bisekcji
    %xk = ( ak * f_bk - bk * f_ak)/(f_bk - f_ak); % xk dla regula falsi
    
    f_xk = f(xk);
    wyniki(k,:) = [xk, f_xk];
    
    if f_xk == 0
        break;
    end

    if f_ak * f_xk < 0
        bk = xk;
    else
        ak = xk;
    end
end
%%%%%%%%%%%%%%%%%%% Rozwi¹zania - koniec %%%%%%%%%%%%%%%%%%%




