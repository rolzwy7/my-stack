function y = koder_QAM(stream, konst)
    stream = reshape(stream,4,length(stream)/4)';

    [r, ~] = size(stream);
    y = zeros(1, r);
   
    for i = 1:r
        b = stream(i,:); 
        for j = 1:length(konst)
            if(b(1)==konst(j,2) && b(2)==konst(j,3) && b(3)==konst(j,4) && b(4)==konst(j,5))
                y(i) = konst(j,1);
                break
            end
        end
    end
    
end