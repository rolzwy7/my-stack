function [bin_vec, image_size] = imageTransmit(filename)
    content = imread(filename);
    
    bin_vec = de2bi(content, 8);
    image_size = size(content);
    bin_vec = reshape(bin_vec, 1, numel(bin_vec));   
end

