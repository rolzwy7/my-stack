% Non-Return-To-Zero Level (NRZ-L)
% ”0” ? – V
% ”1” ? + V
function [ y, t ] = NRZL_koder( bin_data, step, states)
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
    for j=1:length(t)
%         if t(j)<=i
        if t(j)<i
            y(j) = bin_data(i);
        else
            i=i+1;
            y(j) = bin_data(i);
        end
    end
end

