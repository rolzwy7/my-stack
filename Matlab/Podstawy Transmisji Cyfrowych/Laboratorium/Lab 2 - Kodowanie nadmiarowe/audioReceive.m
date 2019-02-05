function audio = audioReceive( filename, bin_vec, fs, info )
    vec = bin_vec;
    block = info(1);
    acc = info(2);

    bin_pos_samples = vec(1, :);
    bin_neg_samples = vec(2, :);

    bin_pos_samples = reshape(bin_pos_samples, numel(bin_pos_samples)/block, block);
    bin_neg_samples = reshape(bin_neg_samples , numel(bin_neg_samples )/block, block);

    bin_pos_samples = bi2de(bin_pos_samples);
    bin_neg_samples = bi2de(bin_neg_samples);

    bin_neg_samples = bin_neg_samples .* (-1);
    merged = bin_neg_samples + bin_pos_samples;

    merged = merged ./ acc;

    audiowrite(filename, merged, fs);
    fprintf('[+] File saved: %s\n', filename);
    audio = merged;
end

