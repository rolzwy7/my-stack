close all;
clear all;
clc;

%%% Zmienne globalne %%%
VEC_RAND_FLAG = false;
SCATTER_LIM = [-4 4];
%%%% End Zmienne globalne %%%

load('P1S5_QAM');

%%%%%% Config %%%%%%
% OFDM
prefix = 50;
N = 256;
scatter_N_display = 1:10; % np. 1:10 wyœwietl pierwsze 10 podkana³ów w scatter

% H = [0.2, 0.2, 0.2, 0.2, 0.2]; % odp. imp.
IS_NOISE = true;
SNR_START_IT = 10;
SNR_END_IT = 35;
SNR_STEP = 5;
fofs = 0;
pofs = 0;
M = 16;        % QAM-XX
K = 4;         % Liczba bitów w bloku
%%%%%% End Config %%%%%%

BER_VEC_PLOT  = zeros(1, 6);
SNR_VEC_PLOT  = zeros(1, 6);
SNR_BER_RATIO = zeros(1, 6);

%%% Dane wejœciowe %%% (Binary Stream)
fprintf('[*] £aduje strumieñ danych\n');
% Obraz
data_stream = double(imread('Lena200x200.png'));
[dim_x,dim_y,dim_z] = size(data_stream);
data_stream = de2bi(data_stream);
data_stream = reshape(data_stream,1,[]);
% % (CONFIG) %%% Wektro losowy %%% (Odkomentowaæ ca³e aby nadpisaæ obraz)
% VEC_RAND_FLAG = true;
% vec_rand_len = 10^4; % 10^6 - wolno, 10^5 - œrednio, 10^4 - jest git
% data_stream = randi([0 ,1], 1, vec_rand_len);

%%% Zera %%%
zera = K*N - mod(numel(data_stream), K*N);
data_stream_copy = data_stream';
data_stream = [ data_stream zeros(1, zera)];

%%%  Koder QAM  %%% (Constelation mapper)
fprintf('[*] Kodowanie w trakcie...');
zeros_num=52;
qam_out = koder_QAM(data_stream, konstelacja);
fprintf('done\n');
QAM_test(data_stream, qam_out) % TEST
% scatterplot(qam_out); title('Uk³ad konstelacji po wyjœciu z koder QAM');

%%% Dzielenie na podkana³y %%%
ofdm_matrix = reshape(qam_out', N, numel(qam_out)/N); 

%%% Inv FFT %%%
ofdm_ifft = ifft(ofdm_matrix);
ofdm_ifft_size = size(ofdm_ifft);

%%%% OdpowiedŸ impulsowa kana³u %%%
k=10+randi(9)-5;  
h=rand(1,k)*2-1;
h=h/sqrt(sum(h.^2));
%plot(abs(fft(h,100)));
channel_impulse_response=h;
H = channel_impulse_response;
%%% End OdpowiedŸ impulsowa kana³u %%%

%%% Cyclic Prefix %%%
ofdm_prefix = [ofdm_ifft(ofdm_ifft_size(1)-prefix+1:end,:); ofdm_ifft];
ofdm_prefix_size = size(ofdm_prefix);

%%% OFDM vec %%%
ofdm_vec = reshape(ofdm_prefix, [], 1);

%%%%%%%% INFO %%%%%%%%
if VEC_RAND_FLAG
    fprintf('[*] Przesy³am losowy wektor binarny\n');
else
    fprintf('[*] Przesy³am obraz\n');
end
fprintf('[+] Pêtla - start\n');
%%%%%%%% End INFO %%%%%%%%
c = 1;
% POCZ¥TEK G£ÓWNEJ PÊTLI

for snr_iterator=SNR_START_IT:SNR_STEP:SNR_END_IT
    SNR_var = snr_iterator;
    SNR_VEC_PLOT(c) = SNR_var;

%%% Kana³ szum %%%
z=filter(H,1,ofdm_vec);
if IS_NOISE == true
    ofdm_noise=awgn(z,SNR_var,'measured');
else
    ofdm_noise = z;
end
%%% End Kana³ szum %%%

% [ofdm_noise, H] = channel_gen(ofdm_vec, SNR_var); % odkomentowaæ

fprintf('[*] Transmisja dla SNR=%ddB | H_len=%d...', SNR_var, numel(H));

%%% OFDM matrix %%%
ofdm_matrix_noise = reshape(...
            ofdm_noise,...
            ofdm_prefix_size(1),...
            numel(ofdm_noise)/ofdm_prefix_size(1)...
           );
ofdm_signal = ofdm_matrix_noise(prefix+1:end,:);

%%% FFT %%%
ofdm_signal_fft = fft(ofdm_signal);
ofdm_signal_fft_size = size(ofdm_signal_fft);

%%% konst. (przed korektorem) %%%
figure(11);
subplot(2,3,c)
tmp = reshape(ofdm_signal_fft(scatter_N_display, :), 1, []);
scatter(...
    real(tmp),...
    imag(tmp),...
    6,...
    'filled');
grid on;
xlim(SCATTER_LIM); ylim(SCATTER_LIM);
title(char(['prz.k. SNR=' int2str(SNR_var) 'dB']));
    
%%% Korektor %%%
ch = fft(H, N);
inv_ch = 1./ch;
%%%
ofdm_corr = ofdm_signal_fft .* repmat(inv_ch, ofdm_signal_fft_size(2), 1).';

ofdm_corr_size = size(ofdm_corr);
%%% konstelacja po korektorze
figure(22);
subplot(2,3,c)
tmp = reshape(ofdm_corr(scatter_N_display, :), 1, []);
scatter(...
    real(tmp),...
    imag(tmp),...
    6,...
    'filled');
grid on;
xlim(SCATTER_LIM); ylim(SCATTER_LIM);
title(char(['po.k. SNR=' int2str(SNR_var) 'dB']));
% suptitle('I am a super title');
% scatterplot(tmp);


%%% Decoder %%%
vec_corr = reshape(ofdm_corr,[],1); % dekoder przyjmuje wektor kolumnowy
ofdm_decoded = decoder_noise(vec_corr');
ofdm_decoded_size = size(ofdm_decoded);

vec_decoded = reshape(ofdm_decoded',[],1);

%%% zeros del %%%
signal_nz = vec_decoded(1:numel(vec_decoded)-zera);

%%% save for ber %%%
[BER_VEC_PLOT(c), SNR_BER_RATIO(c)] = biterr(signal_nz, data_stream_copy);

if VEC_RAND_FLAG == false
    %%% Wyœwietl obraz
    lena = reshape(...
        bi2de(...
            reshape(...
                uint8(signal_nz),...
                prod([dim_x,dim_y,dim_z]),...
                8)...
        ),...
        dim_x,...
        dim_y,...
        dim_z...
    );
    figure(33);
    subplot(2,3,c)
    image(lena);
    title(char(['SNR = ' int2str(SNR_var) 'dB']));
    pbaspect([1 1 1])
end

fprintf('done\n');
c = c + 1;
end % KONIEC G£ÓWNEJ PÊTLI

%%% Ploty %%%
    % Charakt. K.
    figure;
    subplot(211);
    plot(abs(ch)); grid on;
    title('Charakt. amplitudowa kana³u');

    subplot(212);
    plot(abs(inv_ch)); grid on;
    title ('Charakt. amplitudowa kana³u (Odwrotnoœæ)');
    % SNR dla BER %
    figure;
    plot(SNR_VEC_PLOT, SNR_BER_RATIO, '-r', 'LineWidth', 2);
%     semilogy(SNR_VEC_PLOT, SNR_BER_RATIO);
    
    grid on;
    xlabel('SNR'); ylabel('BER');
%%% End Ploty %%%




















% %%% Interpolacja - start %%%
% vec_tmp=(n*numel(qam_out));
% qam_inter=zeros(vec_tmp,1);
% qam_inter(1:n:end)=qam_out(1:end);
% %%% Interpolacja - stop %%%

% %%% Filtracja %%% (TRASH)
% fff=filtr_matrix(f_mat_d:f_mat_g,3,3);                               
% qam_filtered=filter(fff,1,qam_inter);



% przej = 1:length(qam_filtered);
% qam_transmi = qam_filtered.*(exp(1i*2*pi*fc/Fp*przej))';
% 
% %%% Main loop %%%
% j = 1;
% main_counter = 1;
% 
% for snr_it = SNR_START_IT:SNR_STEP:SNR_END_IT
%     fprintf('SNR = %d\n', snr_it);
%     
%     if IS_NOISE
%         %Szum%
%         qam_wyjscio_szum = awgn(qam_transmi, snr_it, 'measured'); 
%         
%         %%%%%%%%%%%%%%%%
%         przej = 1:length(qam_wyjscio_szum);
%         qam_transmid = qam_wyjscio_szum.*(exp((-1)*1i*((2*pi*fc/Fp+2*pi*fofs/Fp)*przej + pofs)))';
% 
%         %Filtracja%
%         qam_po_filtracjid = filter(fff,1,qam_transmid);
%         qam_po_filtracjid = qam_po_filtracjid(zeros_num+1:end);
% 
%         %Decymacja%
%         qam_po_decymacji=qam_po_filtracjid(3:n:end); 
%          if(IS_SYNC == false)
%              qam_po_decymacji = qam_po_decymacji * exp(1i * sync_deg * (pi/180));
%          end
%          
%         if(snr_it==10)
%             scatterplot(qam_po_decymacji);
%             title(char(['SNR = ' int2str(snr_it)]));
%         end
%     end
%     
%     %%%%%%%%%%%%%%%%%%%%
%     %Dekoder_QAM gdy jest szum
%     if IS_NOISE
%         wyjscio = decoder_noise(qam_po_decymacji)';
%     else
%         wyjscio = decoder_no_noise(qam_out, konstelacja)';
%     end
% 
%     wyjscio = reshape(wyjscio,[],1);
%     
%     %%% Wyœwietlanie obrazka %%%
%     if VEC_RAND_FLAG == false        
%         y = reshape(wyjscio,1,numel(wyjscio));
%         y = uint8(reshape(y,numel(y)/8,8));
%         y = bi2de(y);
%         zd = reshape(y,dim_x,dim_y,dim_z);
%         
%         figure(77);
%         subplot((SNR_END_IT/SNR_STEP)+1, 1, main_counter);
%         image(zd);
%         pbaspect([1 1 1]);
%         title(char(['SNR = ' int2str(snr_it)]));
%     end
%     
%     %%% Ber / Ser %%%
%     [n_ber(j), ber(j)] = biterr(data_stream, wyjscio');
%     number = koder_QAM(wyjscio,konstelacja);
%     ratio = koder_QAM(data_stream, konstelacja);
%     [n_ser(j), ser(j)] = symerr(ratio, number);
%     j = j+1;
%     
%     %%%%%%%%%%%%%%%%%%%%%%
%     main_counter = main_counter + 1;
% end
%   
% %%%  Wykresy: BER,SER  %%%
% figure;
% subplot(211);
% x_berser = SNR_START_IT:SNR_STEP:SNR_END_IT;
% 
% plot(x_berser, ber, '-b', 'LineWidth', 2);
% title('Bitowa stopa b³êdów (BER)');
% xlabel('SNR'); ylabel('BER');
% grid on;
% 
% subplot(212);
% plot(x_berser, ser, '-r', 'LineWidth', 2);
% title('Symbolowa stopa b³êdów (SER)');
% xlabel('SNR'); ylabel('SER');
% grid on;
% 
% % figure;
% % plot(filtr_matrix(:,5,4)); title('Odp. imp. filtru; wsp. przek. pasma 0.4 | Nadprobkowanie: 5');
% % plot(filtr_matrix(f_mat_d:f_mat_g,5,4));
