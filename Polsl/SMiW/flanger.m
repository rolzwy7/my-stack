clc;
[x, fs] = audioread('soft_skin_cropped.wav');

x = x(:,1);
% sound(x, fs);

delay = 150;
range = 12;
sweep_freq = 0.3125;
for i = 1:length(x)-delay-range
    y(i) = x(i) + x(i + delay + round(range*sin(2*pi*i*sweep_freq/fs)));
end

sound(y, fs);
