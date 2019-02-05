% Zadanie 2.3
function [ vec_I_col, fs_I ] = interpolacja( vec_col, fs, fg_fdp, I)
    vec_row = vec_col';
    
    vec_D_row = upsample(vec_row, I);
    fs_I = floor(fs*I);
    
    % FDP - start
    fcut = fg_fdp / (fs/2);
    B = fir1(75, fcut);
    vec_filtered_row = filter(B, 1, vec_D_row);
    % FDP - stop
    
    %%%% Test %%%%
    N = numel(vec_filtered_row); % vec X x 1
    % W dziedzinie czasu
    figure(3);
    subplot(211);
    Ts = 1/fs_I;
    t = 0:Ts:(N-1)*Ts; % skalowanie
    plot(t, vec_filtered_row); title('W dziedzinie czasu - interpolacja');
    
    % freq
    w = 0:(fs_I/N):fs_I-(fs_I/N);
    subplot(212);
    stem(w, abs(fft(vec_filtered_row))); title('W dziedzinie czêstotliwoœci- interpolacja');
    
    vec_I_col = vec_filtered_row';
end

