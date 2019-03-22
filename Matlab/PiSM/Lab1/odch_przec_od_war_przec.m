% x_i - pkt skokowe
% p_i - skoki
% wp - wartosc precietna
function [ y ] = odch_przec_od_war_przec( x_i, p_i, wp )
    y = 0;
    for it=1:length(x_i)
        y = y + abs(x_i(it) - wp) * p_i(it);
    end
end


