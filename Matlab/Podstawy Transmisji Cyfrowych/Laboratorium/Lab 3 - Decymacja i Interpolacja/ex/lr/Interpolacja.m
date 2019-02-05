function [ Y, Fout ] = Interpolacja( X, Fin, k)
%   Y - sygna³ zinterpolowany
%   Fout - Wyjœciowa czêstotliwoœæ próbkowania 
%   X - Sygna³ zdecymowany
%   Fin - Wejœciowa czêstotliwoœæ próbkowania
%   k - wspó³czynnik interpolacji   
Y = zeros(k*length(X),1);
j = 1;
Fout = Fin*k;
for i = 1:length(X)
    Y(j) = X(i);
    j = j+k;
end

end

