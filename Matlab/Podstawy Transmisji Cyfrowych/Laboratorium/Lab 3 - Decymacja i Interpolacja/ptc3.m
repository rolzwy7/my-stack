close all; clc; clear;

audio_filename     = 'audio/zdecymowac.wav';
audio_filename_res_dec = 'wyniki/zdecymowac_decymacja.wav';
audio_filename_res_int = 'wyniki/zdecymowac_interpolacja.wav';

% % Zadanie 2.1
% [vec_col, vec_size, fs] = lab3_read(audio_filename);
% % Zadanie 2.2
% D = 3;
% [vec_D_col, fs_D] = decymacja(vec_col, fs, 5000, D);
% audiowrite(audio_filename_res_dec, vec_D_col, fs_D);
% % Zadanie 2.3
% I = 3;
% [ vec_I_col, fs_I ] = interpolacja( vec_col, fs, 500, I);
% audiowrite(audio_filename_res_int, vec_I_col, fs_I);


% % Interpolacja -> Decymacja
% audio_filename_res_int_dec = 'wyniki/zdecymowac_intdec.wav';
% [vec_col, vec_size, fs] = lab3_read(audio_filename);
% I = 6;
% [ vec_I_col, fs_I ] = interpolacja( vec_col, fs, 2500, I);
% D = 6;
% [vec_D_col, fs_D] = decymacja(vec_I_col, fs_I, 5333, D);
% audiowrite(audio_filename_res_int_dec, vec_D_col, fs_D);

disp('Done');