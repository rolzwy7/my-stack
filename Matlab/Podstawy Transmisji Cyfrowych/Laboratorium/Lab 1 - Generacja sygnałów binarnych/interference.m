% Funkcja generuj�ca binarny sygna� zak��caj�cy
% params:
%   p     - prawdopodobie�stwo wyst�pienia b��du
%   dim   - liczba wierszy i kolumn
% ret:
%   y     - macierz zawieraj�ca sygna� zak��caj�cy
%   n_err - liczba przek�amanych bit�w
%   N     - ca�kowita liczba bit�w
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
        mat = zeros(dim(1), dim(2)); % b��dny parametr p
    end
       
    inter = mat;
    N = numel(mat);
    n_err = length(find(mat));
end
