function [ y ] = fKrylowa( pot, alfa, lambda )
    y = 0.0;
    [~,c] = size(pot);
    for it=1:c
        %fprintf('%.2f %.2f %.2f\n', lambda, pot(it), alfa(it));
        res = (lambda^pot(it)) * alfa(it);
        y = y + res;
    end
end

