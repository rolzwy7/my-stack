% Zadaniem funkcji jest wczytanie wektora binarnego i przekszta�cenie go
% w tekst, kt�ry b�dzie zapisany w pliku o podanej nazwie.
% params:
%   filename    - �cie�ka do pliku tekstowego
%   vec         - binarny wektor wierszowy
%   char_len    - d�ugo�� bitowa znaku
% ret:
%   bin_vec     - binarny wektor wierszowy
%   char_length - d�ugo�� bitowa znaku
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

