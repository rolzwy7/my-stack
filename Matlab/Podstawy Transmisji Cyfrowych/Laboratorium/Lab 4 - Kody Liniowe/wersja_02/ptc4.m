close all; clc; clear;

load wektory_testowe.mat

% %%%%%%%%%%%%%%%
% %%%% NRZ-L %%%%
% %%%%%%%%%%%%%%%
bin_vec = sygnal_binarny;
% figure(1);
[line_code_data, t] = NRZL_koder(bin_vec, 1/100, [-1 1]);
[clock_data, t_clock] = cClock(bin_vec, 1/100, [-0.5 0.5]);

fprintf('NRZ == line_code_data ---> %d\n', isequal(nrz', line_code_data));

[decoded] = NRZL_dekoder(line_code_data, clock_data);

fprintf('sygnal_binarny == decoded ---> %d\n', isequal(sygnal_binarny, decoded));
fprintf('********\n\n');


%%%%%%%%%%%%%%%
%%%%  RZ   %%%%
%%%%%%%%%%%%%%%
rz = rz';
bin_vec = sygnal_binarny;
% figure(2);
[line_code_data, t] = RZ_koder(bin_vec, 0.01, [-1 1]);
[clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);

fprintf('RZ == line_code_data ---> %d\n', isequal(rz, line_code_data));

[decoded] = RZ_dekoder(line_code_data, clock_data);
fprintf('sygnal_binarny == decoded ---> %d\n', isequal(sygnal_binarny, decoded));

fprintf('********\n\n');

% %%%%%%%%%%%%%%%%%%%%%%%
% %%%%  Manchester   %%%%
% %%%%%%%%%%%%%%%%%%%%%%%
manchester = manchester';
bin_vec = sygnal_binarny;
% figure(2);
[line_code_data, t] = Manchester_koder(bin_vec, 0.01, [-1 1]);
[clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);

fprintf('Manchester == line_code_data ---> %d\n', isequal(manchester, line_code_data));

[decoded] = Manchester_dekoder(line_code_data, clock_data);

fprintf('Manchester: sygnal_binarny == decoded ---> %d\n', isequal(sygnal_binarny, decoded));

fprintf('********\n\n');

% %%%%%%%%%%%%%%%%%%%
% %%%%  Miller   %%%%
% %%%%%%%%%%%%%%%%%%%

miller = miller';
bin_vec = sygnal_binarny;

[line_code_data, t] = Miller_koder(bin_vec, 0.01, [1 -1]);
[clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);

fprintf('miller == line_code_data ---> %d\n', isequal(miller, line_code_data));

[decoded] = Miller_dekoder(line_code_data, clock_data);

fprintf('Miller: sygnal_binarny == decoded ---> %d\n', isequal(sygnal_binarny, decoded));

fprintf('********\n\n');


%%%%%%%%%%%%%%%%%%%
%%%%  AMI      %%%%
%%%%%%%%%%%%%%%%%%%

ami = ami';
bin_vec = sygnal_binarny;

[line_code_data, t] = AMI_koder(bin_vec, 0.01, [0 1]);
[clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);

fprintf('ami == line_code_data ---> %d\n', isequal(ami, line_code_data));

[decoded] = AMI_dekoder(line_code_data, clock_data);

fprintf('sygnal_binarny == decoded ---> %d\n', isequal(sygnal_binarny, decoded));

fprintf('********\n\n');


%%%%%%%%%%%%%%%%%%%
%%%%  Widma    %%%%
%%%%%%%%%%%%%%%%%%%

% vec_D_row = ami;
% 
% fs_D = fp;
% w_step = fs_D/(N*100); 
% w = 0:w_step:fs_D-w_step;
% Sw = abs(fft(vec_D_row));
% 
% plot(w, Sw, 'b'); 
% 
% axis([0 2.5 0 6000]);



% %%%% AMI %%%%

hold on;

vec_D_row = ami;
M = vec_D_row;
for it=2:100
    randkk = randi([0 1], [1 1000]);
    [line_code_data, t] = AMI_koder( randkk, 0.01, [0 1]);
    M(it, :) = line_code_data;
    M(it, :) = abs(fft(M(it, :)));
end
fs_D = fp;
w_step = fs_D/(N*100); 
w = 0:w_step:fs_D-w_step;
Sw = mean(M);
plot(w, Sw); 
axis([0 2.5 0 6000]);


%%%% Miller %%%%
vec_D_row = ami;
M = vec_D_row;
for it=2:100
    randkk = randi([0 1], [1 1000]);
    [line_code_data, t] = Miller_koder( randkk, 0.01, [0 1]);
    M(it, :) = line_code_data;
    M(it, :) = abs(fft(M(it, :)));
end
fs_D = fp;
w_step = fs_D/(N*100); 
w = 0:w_step:fs_D-w_step;
Sw = mean(M);
plot(w, Sw); 
axis([0 2.5 0 6000]);

%%%% NRZ %%%%
vec_D_row = ami;
M = vec_D_row;
for it=2:100
    randkk = randi([0 1], [1 1000]);
    [line_code_data, t] = NRZL_koder( randkk, 0.01, [0 1]);
    M(it, :) = line_code_data;
    M(it, :) = abs(fft(M(it, :)));
end
fs_D = fp;
w_step = fs_D/(N*100); 
w = 0:w_step:fs_D-w_step;
Sw = mean(M);
plot(w, Sw); 
axis([0 2.5 0 6000]);


hold off;



% fs_D = fp;
% w_step = fs_D/(N*100); 
% w = 0:w_step:fs_D-w_step;
% Sw = abs(fft(vec_D_row));
% 
% plot(w, Sw, 'b'); 
% 
% axis([0 2.5 0 6000]);


    
    % % FDP - start
%     fcut = fg_fdp / (fs/2);
%     B = fir1(75, fcut);
%     vec_filtered_row = filter(B, 1, vec_row);
%     % FDP - stop
