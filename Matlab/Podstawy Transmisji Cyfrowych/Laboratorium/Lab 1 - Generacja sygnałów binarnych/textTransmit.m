% Funkcja wczytuj�ca plik tekstowy i zamieniaj�ca zawarto��
% na binarny wektor wierszowy
% params:
%   filename    - �cie�ka do pliku tekstowego
% ret:
%   bin_vec     - binarny wektor wierszowy
%   char_len    - d�ugo�� bitowa znaku
function [bin_vec, char_len] = textTransmit(filename)
    fid = fopen(filename, 'r', 'n', 'UTF-8');
    bin_row_vector = de2bi(fread(fid)');
    [r, c] = size(bin_row_vector);
    bin_row_vector = reshape(bin_row_vector, 1, r*c);
    fclose(fid);
    bin_vec = bin_row_vector;
    char_len = c;
end

