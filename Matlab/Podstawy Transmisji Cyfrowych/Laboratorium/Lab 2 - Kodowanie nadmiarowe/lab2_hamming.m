close all; clear; clc;

prawdo_bledu = 0.05;

[G, H, R, k] = cHamming(3);

% %%% Text
% %%%%%%%%%%%%%
% Error_sr = 0;
% [bin_vec, char_len] = textTransmit('text/text01.txt');
% [r,c] = size(bin_vec);
% bin_vec = reshape(bin_vec, c/k, k);
% for it=1:c/k
%     packet = bin_vec(it, :);
%     coded = koder_hamming(packet, G);
%     % Zak³ócenia - start
%     [inter, n_err, N] = interference(prawdo_bledu, size(coded));
%     coded = xor( coded, inter );
%     % Zak³ócenia - stop
%     [decoded, korekta] = dekoder_hamming(coded, H, R);
%     if korekta
%         n_err = 0;
%     end
%     Error_sr = Error_sr + (n_err/N);
%     bin_vec(it, :) = decoded;
% end
% bin_vec = reshape(bin_vec, 1, numel(bin_vec));
% content_text = textReceive('wyniki/text_result.txt', bin_vec, char_len);
% fprintf('Text - BER: %.6f%%\n', Error_sr/(c/k)*1000);





% %%% Image
% %%%%%%%%%%%%%
% Error_sr = 0;
% [bin_vec, image_size] = imageTransmit('image/lena_slaby_net.png');
% [r,c] = size(bin_vec);
% bin_vec = reshape(bin_vec, c/k, k);
% for it=1:c/k
%     if mod(it, 10^4) == 0
%         fprintf('\r%.2f%%', 100*(it/(c/k)));
%     end
%     packet = bin_vec(it, :);
%     packet = double(packet);
%     coded = koder_hamming(packet, G);
%     coded = uint8(coded);
%     % Zak³ócenia - start
%     [inter, n_err, N] = interference(prawdo_bledu, size(coded));
%     coded = xor( coded, inter );
%     % Zak³ócenia - stop
%     [decoded, korekta] = dekoder_hamming(coded, H, R);
%     if korekta
%         n_err = 0;
%     end
%     Error_sr = Error_sr + (n_err/N);
%     bin_vec(it, :) = decoded;
%  
% end
% bin_vec = reshape(bin_vec, 1, numel(bin_vec));
% img = imageReceive('wyniki/image_result.png', bin_vec, image_size);
% imshow(uint8(img));
% fprintf('Image - BER: %.6f%%\n', Error_sr/(c/k)*1000);





% %%% Audio - NIE DZIA£A
% %%%%%%%%%%%%%
% Error_sr = 0;
% [ bin_vec, fs, info ] = audioTransmit('audio/audio01.wav');
% %%% Dodatnie
% disp('Dodatnie probki:')
% bin_vec_pos = bin_vec(1, :);
% [r,c] = size(bin_vec_pos);
% bin_vec = reshape(bin_vec_pos, c/k, k);
% for it=1:c/k
%     if mod(it, 10^4) == 0
%         fprintf('\r%.2f%%', 100*(it/(c/k)));
%     end
%     packet = bin_vec(it, :);
%     packet = double(packet);
%     coded = koder_hamming(packet, G);
%     coded = uint8(coded);
%     % Zak³ócenia - start
%     [inter, n_err, N] = interference(prawdo_bledu, size(coded));
%     coded = xor( coded, inter );
%     % Zak³ócenia - stop
%     [decoded, korekta] = dekoder_hamming(coded, H, R);
%     if korekta
%         n_err = 0;
%     end
%     Error_sr = Error_sr + (n_err/N);
%     bin_vec(it, :) = decoded;
%  
% end
% bin_vec_pos = reshape(bin_vec, 1, numel(bin_vec));
% %%% Ujemne
% disp('Ujemne probki:')
% bin_vec_neg = bin_vec(2, :);
% [r,c] = size(bin_vec_neg);
% bin_vec = reshape(bin_vec_neg, c/k, k);
% for it=1:c/k
%     if mod(it, 10^4) == 0
%         fprintf('\r%.2f%%', 100*(it/(c/k)));
%     end
%     packet = bin_vec(it, :);
%     packet = double(packet);
%     coded = koder_hamming(packet, G);
%     coded = uint8(coded);
%     % Zak³ócenia - start
%     [inter, n_err, N] = interference(prawdo_bledu, size(coded));
%     coded = xor( coded, inter );
%     % Zak³ócenia - stop
%     [decoded, korekta] = dekoder_hamming(coded, H, R);
%     if korekta
%         n_err = 0;
%     end
%     Error_sr = Error_sr + (n_err/N);
%     bin_vec(it, :) = decoded;
%  
% end
% bin_vec_neg = reshape(bin_vec, 1, numel(bin_vec));
% 
% bin_vec(1, :) = bin_vec_pos;
% bin_vec(2, :) = bin_vec_neg;
% 
% audio = audioReceive( 'wyniki/audio_result.wav', bin_vec, fs, info );
% fprintf('Audio - BER: %.6f%%\n', Error_sr/(c/k)*1000);