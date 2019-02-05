function [ Y, Fout ] = Interpolacja( X, Fin, k)
%   Y - sygna� zinterpolowany
%   Fout - Wyj�ciowa cz�stotliwo�� pr�bkowania 
%   X - Sygna� zdecymowany
%   Fin - Wej�ciowa cz�stotliwo�� pr�bkowania
%   k - wsp�czynnik interpolacji   
Y = zeros(k*length(X),1);
j = 1;
Fout = Fin*k;
for i = 1:length(X)
    Y(j) = X(i);
    j = j+k;
end

end

