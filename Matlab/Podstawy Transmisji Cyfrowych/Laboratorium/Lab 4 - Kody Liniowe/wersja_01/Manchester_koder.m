% Manchester
% ”0” ? zbocze narastaj¹ce w po³owie taktu zegarowego
% ”1” ? zbocze opadaj¹ce w po³owie taktu zegarowego
function [ y, t ] = Manchester_koder( bin_data, step, states )
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
    t = 0:step:length(bin_data);
    y = zeros(1, length(t));
    co_bylo = 0;
    for j=1:length(t)
        if t(j) >= a && t(j) <= b
            % Pierwsza po³owa taktu
            y(j) = bin_data(i);
            co_bylo = y(j);
        elseif t(j)>b && t(j)<=i
            % Druga po³owa taktu
            y(j) = -bin_data(i);
            co_bylo = y(j);
        else
            y(j) = co_bylo;
            % Zbocze taktu
            i=i+1;
            a=a+1;
            b=b+1;
        end
    end
    
end



