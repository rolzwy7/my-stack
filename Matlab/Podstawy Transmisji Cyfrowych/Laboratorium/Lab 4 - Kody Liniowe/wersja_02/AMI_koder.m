% Non-Return-To-Zero Level (NRZ-L)
% ”0” ? 0
% ”1” ? naprzemiennie +V , –V
function [ y, t ] = AMI_koder( bin_data, step, states)
    %
    for m = 1:length(bin_data)
            if bin_data(m) == 1;
                bin_data(m) = states(2);
            else
                bin_data(m) = states(1);
            end
    end
    %
    i=1;
    t=0:step:length(bin_data)-step;
    y = zeros(1, length(t));
    remember_switch = -1;
    for j=1:length(t)
        if t(j)<i
            if bin_data(i) == states(1)
                p_insert = bin_data(i);
            else
                p_insert = remember_switch * bin_data(i);
            end
            y(j) = p_insert;
            
        else
            prev_ = bin_data(i);
            i=i+1;
            y(j) = p_insert;
            if prev_ == states(2)
                remember_switch = -remember_switch;
            end
        end
    end
        % shift
    sss = 1;
    y = y(1+sss:numel(y));
    y(numel(y)+sss) = 0;
    
    y(numel(y)) = states(2);
end