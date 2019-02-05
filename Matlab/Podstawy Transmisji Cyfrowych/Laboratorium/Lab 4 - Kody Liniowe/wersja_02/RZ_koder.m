% Return-To-Zero
% ”0” ? –V (pierwsza po³owa taktu zegarowego)
% ”1” ? +V (pierwsza po³owa taktu zegarowego)
function [ y, t ] = RZ_koder( bin_data, step, states )
    %
    for m = 1:length(bin_data)
            if bin_data(m) == 1;
                bin_data(m) = states(2);
            else
                bin_data(m) = states(1);
            end
    end
    %
    i = 1;
    a = 0;
    b = 0.5;
    t = 0:step:length(bin_data)-step;
    y = zeros(1, length(t));
    for j=1:length(t)
%         if t(j) >= a && t(j) <= b
        if t(j) >= a && t(j) <= b
            % Pierwsza po³owa taktu
            y(j) = bin_data(i);
%         elseif t(j)>b && t(j)<= i
        elseif t(j)>b && t(j)< i
            % Druga po³owa taktu
            y(j) = 0;
        else
            i=i+1;
            a=a+1;
            b=b+1;
        end
    end
    % shift
    sss = 1;
    y = y(1+sss:numel(y));
    y(numel(y)+sss) = 0;
end

