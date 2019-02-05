function [y, korekta] = dekoder_hamming(vec, H, R)
    korekta = 0;
    coded = vec';
    z = mod(H*coded, 2);
    syndrom = z'; %fliplr(z');
    if sum(syndrom) ~= 0
        coded = coded';
        coded(1, bi2de(syndrom)) = not(coded(1, bi2de(syndrom)));
        coded = coded';
        korekta = 1;
    end
    y = (R*coded)'; % decoded
end

