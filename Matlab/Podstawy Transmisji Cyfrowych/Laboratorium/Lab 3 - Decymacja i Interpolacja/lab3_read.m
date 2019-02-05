% Zadanie 2.1
function [ vec, vec_size, fs ] = lab3_read( filename)%, fft_size )

    [vec, fs] = audioread(filename);
    N = numel(vec); % vec X x 1
    vec_size = size(vec);
    vec_row = vec'; % vec_row 1 x X
    
    % W dziedzinie czasu
    figure(1);
    subplot(211);
    Ts = 1/fs;
    t = 0:Ts:(N-1)*Ts; % skalowanie
    plot(t, vec_row); title('Przebieg czasowy - orygina³');
    
    % freq
    w = 0:(fs/N):fs-(fs/N);
    subplot(212);
    stem(w, abs(fft(vec_row))); title('Widmo - orygina³');
end

