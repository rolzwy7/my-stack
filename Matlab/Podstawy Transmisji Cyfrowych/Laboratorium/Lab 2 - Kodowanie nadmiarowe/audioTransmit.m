function [ bin_vec, fs, info ] = audioTransmit( filename )
    [samples, fs] = audioread(filename, 'double');
    acc = 10^8;
    a = samples .* acc;

    neg_samples = abs(((a > 0) * 0 + (a < 0)) .* a);
    pos_samples = ((a < 0) * 0 + (a > 0)) .* a;

    pos_samples = floor(pos_samples);
    neg_samples = floor(neg_samples);

    block = 32;
    bin_neg_samples = de2bi(neg_samples, block);
    bin_pos_samples = de2bi(pos_samples, block);

    bin_neg_samples = reshape(bin_neg_samples,1,numel(bin_neg_samples));
    bin_pos_samples = reshape(bin_pos_samples,1,numel(bin_pos_samples));

    bin_vec = [bin_pos_samples ; bin_neg_samples];
    info = [block, acc];
end

