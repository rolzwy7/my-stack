% Funkcja generuj¹ca binarny sygna³ zak³ócaj¹cy
% params:
%   p     - prawdopodobieñstwo wyst¹pienia b³êdu
%   dim   - liczba wierszy i kolumn
% ret:
%   y     - macierz zawieraj¹ca sygna³ zak³ócaj¹cy
%   n_err - liczba przek³amanych bitów
%   N     - ca³kowita liczba bitów
function [ inter, n_err, N ] = interference(p, dim)
    accuraccy = 10^1;
    mat = randi([0, 100*accuraccy], dim(1), dim(2)) ./ (accuraccy*10^2);
    
    if(p == 1.0)
       mat = ones(dim(1), dim(2));
    elseif(p == 0.0)
       mat = zeros(dim(1), dim(2));
    elseif(p > 0.0 && p < 1.0)
        mat = (mat >= p) * 0 + (mat < p) * 1;
    else
        mat = zeros(dim(1), dim(2)); % b³êdny parametr p
    end
       
    inter = mat;
    N = numel(mat);
    n_err = length(find(mat));
end
