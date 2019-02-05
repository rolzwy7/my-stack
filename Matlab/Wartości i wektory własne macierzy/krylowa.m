close all; clear; clc;

%%%% Metoda Kry�owa %%%%
A = [
    1.000 1.000 1.000;
    1.000 2.000 3.000;
    1.000 3.000 6.000
];

x = [1;0;0]; % wektor pocz�tkowy
[mat, vec] = mKrylowa(A, x);
res = (mat\vec)';
[~, c] = size(res);
res_tmp = ones(1, c+1);
res_tmp(2:end) = res;
powers = c:-1:0;

% fKrylowa( powers, res_tmp, 1 );


%%%% Rozwi�zanie r�wnania nielioniowego %%%%
K = 20;
wyniki = ones(K, 2);

ak = 0; % a - pocz�tek przedzia�u
bk = 0.2;  % b - koniec przedzia�u

for k=1:K
    
    f_bk = fKrylowa( powers, res_tmp, bk ); % f(bk);
    f_ak = fKrylowa( powers, res_tmp, ak ); % f(ak);
   
    xk = ( ak * f_bk - bk * f_ak)/(f_bk - f_ak);
    
    f_xk = fKrylowa( powers, res_tmp, xk );
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
wyniki
wyniki(end, 1)




