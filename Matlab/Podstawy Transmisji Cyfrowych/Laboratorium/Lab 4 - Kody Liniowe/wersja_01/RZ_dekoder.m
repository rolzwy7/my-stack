function [ y ] = RZ_dekoder( line_code_signal, clock_signal )
    prev = clock_signal(1);
    i = 1;
    for it=2:length(clock_signal)
        current = clock_signal(it);
        if current > prev % zbocze narastaj�ce
            y(i) = line_code_signal(it-3);
            i = i + 1;
        elseif(current < prev) % zbocze opadaj�ce
        end
        prev = clock_signal(it);
    end
    y = (y > 0) * 1 + (y < 0) * 0;
end
