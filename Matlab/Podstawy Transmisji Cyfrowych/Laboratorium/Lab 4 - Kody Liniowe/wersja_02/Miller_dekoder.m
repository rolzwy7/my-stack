function [ y ] = Miller_dekoder( line_code_signal, clock_signal )
    prev = clock_signal(1);
    i = 1;
    for it=2:length(clock_signal)
        current = clock_signal(it);
        if current > prev % zbocze narastaj¹ce
            
            if line_code_signal(it-5) == line_code_signal(it+5)
                y(i) = 0;
            else
                y(i) = 1;
            end
            i = i + 1;
        elseif(current < prev) % zbocze opadaj¹ce
        end
        prev = clock_signal(it);
    end
end

