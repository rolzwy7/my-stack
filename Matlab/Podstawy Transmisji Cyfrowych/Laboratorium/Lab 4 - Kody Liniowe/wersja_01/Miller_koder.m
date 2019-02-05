% Miller
% ”0” ? zmiana stanu je¿eli nastêpuje po ”0”
% ”0” ? brak zmiany je¿eli nastêpuje po ”1”
% ”1” ? zmiana stanu w po³owie taktu zegarowego
function [ y, t ] = Miller_koder( bin_data, step, states )
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
    p1_insert = bin_data(1);
    for j=1:length(t)
        if t(j) >= a && t(j) <= b
            % Pierwsza po³owa taktu
            y(j) = p1_insert;
        elseif t(j)>b && t(j)<=i
            % Druga po³owa taktu
            if bin_data(i) == states(1)
                p2_insert = p1_insert;
            else
                p2_insert = -p1_insert;
            end
            y(j) = p2_insert;
            p2_hold = p2_insert;
        else
            y(j) = p2_hold;
            
            % w poprzednim takcie (II po³owa)
            prev_ = bin_data(i);
            
            i=i+1;
            a=a+1;
            b=b+1;
            
            % w nastêpnym takcie (I po³owa)
            next_ = bin_data(i);
            
            % 0 na 1
            if prev_ == states(1) && next_ == states(2)
%                 disp('0 na 1');
                p1_insert = p2_insert;
            end
            % 0 na 0
            if prev_ == states(1) && next_ == states(1)
%                 disp('0 na 0');
                p1_insert = -p2_insert;
            end
            % 1 na 1
            if prev_ == states(2) && next_ == states(2)
%                 disp('1 na 1');
                p1_insert = p2_insert;
            end
            % 1 na 0
            if prev_ == states(2) && next_ == states(1)
%                 disp('1 na 0');
                p1_insert = p2_insert;
            end

        end
    end
    
end

