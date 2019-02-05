function [ y, t ] = cClock(bin_data, step, states )
    %
    i = 1;
    a = 0;
    b = 0.5;
    t = 0:step:length(bin_data)-step;
    y = zeros(1, length(t));
    for j=1:length(t)
        if t(j) >= a && t(j) <= b
            % Pierwsza po³owa taktu
            y(j) = states(1);
        elseif t(j)>b && t(j)<=i
            % Druga po³owa taktu
            y(j) = states(2);
            hold_p2 = y(j);
        else
            y(j) = hold_p2;
            i=i+1;
            a=a+1;
            b=b+1;
        end
    end
    
end

