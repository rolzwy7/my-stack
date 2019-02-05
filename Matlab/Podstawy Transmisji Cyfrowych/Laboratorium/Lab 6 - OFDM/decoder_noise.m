function y = decoder_noise(in_)
    y = zeros(length(in_),4);
    for i = 1:length(in_)
        im = imag(in_(i));
        re = real(in_(i));
        if(re>2 && im >2) % 3+3i
            y(i,:) = [0,0,0,1];
        elseif(re<-2 && im<-2) %-3-3i
            y(i,:) = [1,1,1,1];
        elseif(re>2 && im<-2) %3-3i
            y(i,:) = [0,0,1,1];
        elseif(re<-2 && im>2) %-3+3i
            y(i,:) = [1,1,0,1];
        elseif(re>=0 && re<=2 && im>2) %1+3i
            y(i,:) = [1,0,0,1];
        elseif(re>=2 && im>=0 && im<2) %3+1i
            y(i,:) = [0,0,1,0];
        elseif(re>=0 && re<2 && im<2 && im>0) %1+1i
            y(i,:) = [1,0,1,0];
        elseif(re<0 && re>-2 && im<2 && im>=0) %-1+1i
            y(i,:) = [0,1,1,0];
        elseif(re<0 && re>-2 && im<0 && im>=-2) % -1-1i
            y(i,:) = [0,1,0,0];
        elseif(re<2 && re>0 && im<0 && im>=-2) % %1-1i
            y(i,:) = [1,0,0,0];
        elseif(re<=0 && re>=-2 && im>=2) % -1 +3i
            y(i,:) = [0,1,0,1];
        elseif(re<=-2 && im>=0 && im<=2) % -3+1i
            y(i,:) = [1,1,1,0]; 
        elseif(re<=-2 && im<=0 && im>=-2) %-3 -1i
            y(i,:) = [1,1,0,0];
        elseif(re<=0 && re>=-2 && im<-2) % -1-3i
            y(i,:) = [0,1,1,1];
        elseif(re>=0 && re<=2 && im<-2) % 1-3i
            y(i,:) = [1,0,1,1];
        elseif(re>=2 && im<=0 && im>=-2) % 3-1i
            y(i,:) = [0,0,0,0];
        end
    end
    
end
