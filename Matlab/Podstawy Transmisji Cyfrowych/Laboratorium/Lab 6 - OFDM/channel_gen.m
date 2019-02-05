function [y,channel_impulse_response]=channel_gen(x,SNR)    

    k=10+randi(9)-5;  
    
    h=rand(1,k)*2-1;
    
    h=h/sqrt(sum(h.^2));
    
    %plot(abs(fft(h,100)));
    
    channel_impulse_response=h;

    z=filter(h,1,x);
    
    y=awgn(z,SNR,'measured');
    
end