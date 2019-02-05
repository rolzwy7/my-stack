function content = imageReceive(filename, bin_vec, dim)
    [~, c] = size(bin_vec);
    bin_vec = reshape(bin_vec, c/8, 8);
    d2b = bi2de(bin_vec);
    d2b = reshape(d2b, dim);
    imwrite(d2b, filename);
    fprintf('[+] File saved: %s\n', filename);
    content = d2b;
end

