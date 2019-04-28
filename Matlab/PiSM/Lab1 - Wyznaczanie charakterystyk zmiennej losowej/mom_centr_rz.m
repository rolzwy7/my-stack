% moment centralny dowolnego rzêdu
% wp - wartoœæ przeciêtna (mom. zwyk. r=1)
function [ y ] = mom_centr_rz( r, x_i, p_i, wp )
    y = 0;
    for it=1:length(x_i)
        y = y + (x_i(it) - wp)^r * p_i(it);
    end
end

