function [y] = prototype( M, fc, fp )

i=0:(M-1);
y = sin(2*pi*fc/fp*(i-(M-1)/2))./(pi*(i-(M-1)/2));
  if mod(M,2)
      y((M-1)/2+1)=2*fc/fp;
  end
end



