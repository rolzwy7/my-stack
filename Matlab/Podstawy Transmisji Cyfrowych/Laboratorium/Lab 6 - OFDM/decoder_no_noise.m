function [ y ] = decoder_no_noise(wejscio, konstelacja)
    y = zeros(length(wejscio),4);
    for i = 1:length(wejscio)
        for j=1:length(konstelacja)
            if(wejscio(i) == konstelacja(j,1))
                y(i,1) = konstelacja(j,2);
                y(i,2) = konstelacja(j,3);
                y(i,3) = konstelacja(j,4);
                y(i,4) = konstelacja(j,5);
            break
            end
        end
    end
    
end