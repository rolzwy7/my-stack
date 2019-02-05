function y = koder_hamming(vec, G)
    p = vec';
    x = mod(G*p, 2);
    y = x';
end

