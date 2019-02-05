% Zwraca wektor z kodem parzystosci
function [ret, srows] = koder_parz( vec, n )    
    vec = (reshape(vec, n-1, numel(vec)/(n-1)))';
    [r, c] = size(vec);
    ret = zeros(r, c+1);   
    ret(1:r, 1:c) = vec;
    ret(1:r, c+1) = mod(sum(vec, 2), 2);
    [srows, ~] = size(ret);
    ret;
    ret = reshape(ret', 1, numel(ret));
end

