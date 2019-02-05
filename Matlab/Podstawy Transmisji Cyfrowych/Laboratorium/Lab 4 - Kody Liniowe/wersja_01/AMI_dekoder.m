function [ y ] = AMI_dekoder( line_code_signal, clock_signal )
    prev = clock_signal(1);
    i = 1;
    for it=2:length(clock_signal)
        current = clock_signal(it);
        if current > prev % zbocze narastaj¹ce
            y(i) = line_code_signal(it);
            i = i + 1;
        elseif(current < prev) % zbocze opadaj¹ce
        end
        prev = clock_signal(it);
    end
    y = (y ~= 0) * 1 + (y == 0) * 0;
end


