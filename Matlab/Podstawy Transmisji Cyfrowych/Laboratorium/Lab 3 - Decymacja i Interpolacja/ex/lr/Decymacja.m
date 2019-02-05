function [B, Fsout] = Decymacja( A, Fsin, k )
%   A - sygna³ spróbkowany
%   Fsin - czêstotliwoœæ próbkowania sygna³u
%   k - wspó³czynnik decymacji
%   B - sygna³ zdecymowany
%   Fsout - nowa czêstotliwoœæ próbkowania sygna³u

B = zeros(ceil(length(A)/k), 1);
Fsout = ceil(Fsin/k);
j = 1;
for i =1:k:length(A)
    B(j,1) = A(i,1);
    j=j+1;
end

end

