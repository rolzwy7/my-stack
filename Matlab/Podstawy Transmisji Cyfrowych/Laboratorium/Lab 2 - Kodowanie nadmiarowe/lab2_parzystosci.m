close all; clear; clc;

%%%%%%%%%%%%%%%%%%%%%%%% LAB 2 %%%%%%%%%%%%%%%%%%%%%%%% 

prawdo_bledu = 0.0;

n = 3;
%n = 5;
%n = 17;
%n = 33;
%n = 65;
%n = 129;

retrans = 0;
retrans = 1+retrans;

% %%% DEBUG
% %%%%%%%%%%%%
% A = [0 0 0 1 1 1 1 0 0 0];
% [A, srows] = koder_parz(A, n);
% success = zeros(srows, 1);
% Result = zeros(srows, n);
% for retr_it=1:retrans
%     [inter, n_err, N] = interference(prawdo_bledu, size(A));
%     fprintf('Retransmisja %02d, BER: %.2f%%\n', retr_it-1, 100*(n_err/N));
%     A_loop = xor(A, inter);
%     success_prev = success;
%     [res, success] = dekoder_parz(A_loop, n, success);
%     success_new = xor(success, success_prev);
%     success_new = repmat(success_new, 1, n);
%     Result = Result + (res .* success_new);
%     if( numel(find(success_new)) == 0 )
%         disp('Dekoder uzna³, ¿e nie ma ju¿ b³êdów');
%         disp('Pomijam pozosta³e retransmisje.');
%         break;
%     end
% end
% % start - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = double(logical(Result + (res .* not(success_new))));
% % stop - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = Result(1:srows, 1:n-1);
% Result = reshape(Result', numel(Result), 1)';






% %%% Text - Lab 2
% %%%%%%%%%%%%
% [A, char_len] = textTransmit('text/text01.txt');
% [A, srows] = koder_parz(A, n);
% success = zeros(srows, 1);
% Result = zeros(srows, n);
% for retr_it=1:retrans
%     [inter, n_err, N] = interference(prawdo_bledu, size(A));
%     fprintf('Retransmisja %02d, BER: %.2f%%\n', retr_it-1, 100*(n_err/N));
%     A_loop = xor(A, inter);
%     success_prev = success;
%     [res, success] = dekoder_parz(A_loop, n, success);
%     success_new = xor(success, success_prev);
%     success_new = repmat(success_new, 1, n);
%     Result = Result + (res .* success_new);
%     if( numel(find(success_new)) == 0 )
%         disp('Dekoder uzna³, ¿e nie ma ju¿ b³êdów');
%         disp('Pomijam pozosta³e retransmisje.');
%         break;
%     end
% end
% % start - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = double(logical(Result + (res .* not(success_new))));
% % stop - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = Result(1:srows, 1:n-1);
% Result = reshape(Result', numel(Result), 1)';
% content_text = textReceive('wyniki/text_result.txt', Result, char_len);






% %%% Image - Lab 2
% %%%%%%%%%%%%
% [A, image_size] = imageTransmit('image/lena.png');
% [A, srows] = koder_parz(A, n);
% success = zeros(srows, 1);
% Result = zeros(srows, n);
% for retr_it=1:retrans
%     [inter, n_err, N] = interference(prawdo_bledu, size(A));
%     fprintf('Retransmisja %02d, BER: %.2f%%\n', retr_it-1, 100*(n_err/N));
%     A_loop = xor(A, inter);
%     success_prev = success;
%     [res, success] = dekoder_parz(A_loop, n, success);
%     success_new = xor(success, success_prev);
%     success_new = repmat(success_new, 1, n);
%     Result = Result + (res .* success_new);
%     if( numel(find(success_new)) == 0 )
%         disp('Dekoder uzna³, ¿e nie ma ju¿ b³êdów');
%         disp('Pomijam pozosta³e retransmisje.');
%         break;
%     end
% end
% % start - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = double(logical(Result + (res .* not(success_new))));
% % stop - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = Result(1:srows, 1:n-1);
% Result = reshape(Result', numel(Result), 1)';
% Result = uint8(Result);
% img = imageReceive('wyniki/image_result.png', Result, image_size);
% imshow(uint8(img));






% %%% Audio - Lab 2
% %%%%%%%%%%%%
% [ B, fs, info ] = audioTransmit('audio/audio01.wav');
% A_1 = B(1, :);
% [A, srows] = koder_parz(A_1, n);
% success = zeros(srows, 1);
% Result = zeros(srows, n);
% disp('Transmisja dodatnich próbek')
% for retr_it=1:retrans
%     [inter, n_err, N] = interference(prawdo_bledu, size(A));
%     fprintf('Retransmisja %02d, BER: %.2f%%\n', retr_it-1, 100*(n_err/N));
%     A_1 = xor(A, inter);
%     success_prev = success;
%     [res, success] = dekoder_parz(A_1, n, success);
%     success_new = xor(success, success_prev);
%     success_new = repmat(success_new, 1, n);
%     Result = Result + (res .* success_new);
%     if( numel(find(success_new)) == 0 )
%         disp('Dekoder uzna³, ¿e nie ma ju¿ b³êdów');
%         disp('Pomijam pozosta³e retransmisje.');
%         break;
%     end
% end
% % start - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = double(logical(Result + (res .* not(success_new))));
% % stop - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = Result(1:srows, 1:n-1);
% Result = reshape(Result', numel(Result), 1)';
% Result_1 = uint16(Result);
% 
% A_2 = B(2, :);
% [A, srows] = koder_parz(A_2, n);
% success = zeros(srows, 1);
% Result = zeros(srows, n);
% disp('Transmisja ujemnych próbek')
% for retr_it=1:retrans
%     [inter, n_err, N] = interference(prawdo_bledu, size(A));
%     fprintf('Retransmisja %02d, BER: %.2f%%\n', retr_it-1, 100*(n_err/N));
%     A_2 = xor(A, inter);
%     success_prev = success;
%     [res, success] = dekoder_parz(A_2, n, success);
%     success_new = xor(success, success_prev);
%     success_new = repmat(success_new, 1, n);
%     Result = Result + (res .* success_new);
%     if( numel(find(success_new)) == 0 )
%         disp('Dekoder uzna³, ¿e nie ma ju¿ b³êdów');
%         disp('Pomijam pozosta³e retransmisje.');
%         break;
%     end
% end
% % start - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = double(logical(Result + (res .* not(success_new))));
% % stop - Przepuœæ nieporawne bity przy ostaniej retransmisij
% Result = Result(1:srows, 1:n-1);
% Result = reshape(Result', numel(Result), 1)';
% Result_2 = uint16(Result);
% bin_vec = [];
% bin_vec(1, :) = Result_1;
% bin_vec(2, :) = Result_2;
% audio = audioReceive( 'wyniki/audio_result.wav', bin_vec, fs, info );
