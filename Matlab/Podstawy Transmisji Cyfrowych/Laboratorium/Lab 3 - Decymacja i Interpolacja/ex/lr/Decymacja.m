function [B, Fsout] = Decymacja( A, Fsin, k )
%   A - sygna� spr�bkowany
%   Fsin - cz�stotliwo�� pr�bkowania sygna�u
%   k - wsp�czynnik decymacji
%   B - sygna� zdecymowany
%   Fsout - nowa cz�stotliwo�� pr�bkowania sygna�u

B = zeros(ceil(length(A)/k), 1);
Fsout = ceil(Fsin/k);
j = 1;
for i =1:k:length(A)
    B(j,1) = A(i,1);
    j=j+1;
end

end

