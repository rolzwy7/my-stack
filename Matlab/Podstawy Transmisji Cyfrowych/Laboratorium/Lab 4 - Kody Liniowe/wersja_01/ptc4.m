close all; clc; clear;

% %%%%%%%%%%%%%%%
% %%%% NRZ-L %%%%
% %%%%%%%%%%%%%%%
% bin_vec = [1 0 0 1 1 0 1 0 1 1 1 0 1 0 0 1 1 0 0 0];
% figure(1);
% [line_code_data, t] = NRZL_koder(bin_vec, 0.01, [-1 1]);
% [clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);
% 
% hold on;
% plot_line_code(line_code_data, t, 'NRZ-L', 'b');
% plot_line_code(clock_data, t_clock, 'cClock', 'r');
% hold off;
% 
% [decoded] = NRZL_dekoder(line_code_data, clock_data);

%%%%%%%%%%%%%%%
%%%%  RZ   %%%%
%%%%%%%%%%%%%%%
% bin_vec = [0 0 1 0 1 1 0 1 0 0 1 1 1 0 1 1 0 0 0 0];
% figure(2);
% [line_code_data, t] = RZ_koder(bin_vec, 0.01, [-1 1]);
% [clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);
% 
% hold on;
% plot_line_code(line_code_data, t, 'RZ', 'b');
% plot_line_code(clock_data, t_clock, 'cClock', 'r');
% hold off;
% 
% [decoded] = RZ_dekoder(line_code_data, clock_data);

% %%%%%%%%%%%%%%%%%%%%%%%
% %%%%  Manchester   %%%%
% %%%%%%%%%%%%%%%%%%%%%%%
% bin_vec = [1 0 0 0 0 1 1 1 1 0 1 0 0 1 0 1 1 1 1 0];
% figure(3);
% [line_code_data, t] = Manchester_koder(bin_vec, 0.01, [-1 1]);
% [clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);
% 
% hold on;
% plot_line_code(line_code_data, t, 'Manchester', 'b');
% plot_line_code(clock_data, t_clock, 'cClock', 'r');
% hold off;
% 
% [decoded] = Manchester_dekoder(line_code_data, clock_data);

% %%%%%%%%%%%%%%%%%%%
% %%%%  Miller   %%%%
% %%%%%%%%%%%%%%%%%%%
% bin_vec = [0 1 1 1 0 1 0 0 0 0 0 0 1 0 1 0 1 0 0 1];
% figure(4);
% [line_code_data, t] = Miller_koder(bin_vec, 0.01, [1 -1]);
% [clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);
% 
% hold on;
% plot_line_code(line_code_data, t, 'Miller', 'b');
% plot_line_code(clock_data, t_clock, 'cClock', 'r');
% hold off;
% 
% [decoded] = Miller_dekoder(line_code_data, clock_data);

%%%%%%%%%%%%%%%%%%%
%%%%  Miller   %%%%
%%%%%%%%%%%%%%%%%%
bin_vec = [0 1 1 1 0 0 0 1 1 0 0 1 1 1 0 0 1 0 0 1];
figure(5);
[line_code_data, t] = AMI_koder(bin_vec, 0.01, [0 1]);
[clock_data, t_clock] = cClock(bin_vec, 0.01, [-0.5 0.5]);

hold on;
plot_line_code(line_code_data, t, 'AMI', 'b');
plot_line_code(clock_data, t_clock, 'cClock', 'r');
hold off;

[decoded] = AMI_dekoder(line_code_data, clock_data);


%%%%%%%%%%%%%%%
%%%% DEBUG %%%%
%%%%%%%%%%%%%%%
% bin_vec = [1 0 0 1 1 0 1 0 1 1 1 0 1 0 0 1 1 0 0 0];
% figure(6);
% [clock_data, t_clock] = cClock(bin_vec, 0.01, [-1 1]);
% plot_line_code(clock_data, t_clock, 'cClock', 'r');

% bin_vec = [1 0 0 1 1 0 1 0 1 1 1 0 1 0 0 1 1 0 0 0];
% figure(1);
% [line_code_data, t] = NRZL_koder(bin_vec, 0.01, [-1 1]);
% plot_line_code(line_code_data, t, 'NRZ-L', 'r');
 
% bin_vec = [0 0 1 0 1 1 0 1 0 0 1 1 1 0 1 1 0 0 0 0];
% figure(2);
% [line_code_data, t] = RZ_koder(bin_vec, 0.01, [-1 1]);
% plot_line_code(line_code_data, t, 'RZ', 'r');
% 
% bin_vec = [1 0 0 0 0 1 1 1 1 0 1 0 0 1 0 1 1 1 1 0];
% figure(3);
% [line_code_data, t] = Manchester_koder(bin_vec, 0.01, [-1 1]);
% plot_line_code(line_code_data, t, 'Manchester', 'r');
% 
% bin_vec = [0 1 1 1 0 1 0 0 0 0 0 0 1 0 1 0 1 0 0 1];
% figure(4);
% [line_code_data, t] = Miller_koder(bin_vec, 0.01, [1 -1]);
% plot_line_code(line_code_data, t, 'Miller', 'r');
% 
% bin_vec = [0 1 1 1 0 0 0 1 1 0 0 1 1 1 0 0 1 0 0 1];
% figure(5);
% [line_code_data, t] = AMI_koder(bin_vec, 0.01, [0 1]);
% plot_line_code(line_code_data, t, 'AMI', 'r');
%%%%%%%%%%%%%%%
%%%% DEBUG %%%%
%%%%%%%%%%%%%%%
