% x_i - pkt skokowe
% p_i - skoki
% wp - wartosc precietna
function [ y ] = wariancja( x_i, p_i, wp )
    y = 0;
    for it=1:length(x_i)
        y = y + (x_i(it) - wp)^2 * p_i(it);
    end
end

