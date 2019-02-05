% Zadanie 2.2
function [ vec_D_col, fs_D ] = decymacja( vec_col, fs, fg_fdp, D)%,  fg_fdp, fg_fdp2, Tp, Tz)
    vec_row = vec_col';
    
    % FDP - start
    fcut = fg_fdp / (fs/2);
    B = fir1(75, fcut);
    vec_filtered_row = filter(B, 1, vec_row);
    % FDP - stop
    
    vec_D_row = downsample(vec_filtered_row, D);
    fs_D = floor(fs/D);
    
    %%%% Test %%%%
    N = numel(vec_D_row); % vec X x 1
    % W dziedzinie czasu
    figure(2);
    subplot(211);
    Ts = 1/fs_D;
    t = 0:Ts:(N-1)*Ts; % skalowanie
    plot(t, vec_D_row); title('W dziedzinie czasu - decymacja');
    
    % freq
    w = 0:(fs_D/N):fs_D-(fs_D/N);
    subplot(212);
    stem(w, abs(fft(vec_D_row))); title('W dziedzinie czêstotliwoœci - decymacja');
    
    vec_D_col = vec_D_row';
end

