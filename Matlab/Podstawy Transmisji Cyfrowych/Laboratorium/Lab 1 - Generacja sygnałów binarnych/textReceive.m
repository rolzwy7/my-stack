% Zadaniem funkcji jest wczytanie wektora binarnego i przekszta³cenie go
% w tekst, który bêdzie zapisany w pliku o podanej nazwie.
% params:
%   filename    - œcie¿ka do pliku tekstowego
%   vec         - binarny wektor wierszowy
%   char_len    - d³ugoœæ bitowa znaku
% ret:
%   bin_vec     - binarny wektor wierszowy
%   char_length - d³ugoœæ bitowa znaku
function content_text = textReceive(filename, vec, char_len)
    fid = fopen(filename', 'w', 'n', 'UTF-8');
    [~,c] = size(vec);
    vec = reshape(vec, c/char_len, char_len);
    content = bi2de(vec);
    fwrite(fid, content);
    fprintf('[+] File saved: %s\n', filename);
    content_text = content;
    fclose(fid);
end

