clear
close all;

%%%%%%%%%%%%%%%%%%%%%%%%%%% ZADANIE 1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
kd = 2; % Wspó³czynnik decymacji
ki = 2; % Wspó³czynnik interpolacji
[A,Fs_A] = audioread('female1_m.wav');
[Xd, Fs_Xd] = Decymacja(A,Fs_A,kd); 


A_fft = fft(A);
Freq_A = 0:Fs_A/length(A):Fs_A-(1/Fs_A);
figure('name','Widma sygnalu wejsciowego A','numbertitle','off')
subplot(2,1,1);stem(Freq_A,abs(A_fft),'g');title('Widmo Amplitudowe');xlabel('Czestotliwosc probkowania Fs in');ylabel('Amplituda sygnalu'); 
subplot(2,1,2);plot(Freq_A,angle(A_fft),'r');title('Widmo Fazowe');xlabel('Czestotliwosc probkowania Fs in');ylabel('Faza sygnalu'); 


Xd_fft = fft(Xd);
Freq_Xd = 0:Fs_Xd/length(Xd):Fs_Xd-(1/Fs_Xd);
figure('name','Widma sygnalu zdecymowanego','numbertitle','off')
subplot(2,1,1);stem(Freq_Xd,abs(Xd_fft),'g');title('Widmo Amplitudowe');xlabel('Czestotliwosc probkowania Fs out');ylabel('Amplituda sygnalu'); 
subplot(2,1,2);plot(Freq_Xd,angle(Xd_fft),'r');title('Widmo Fazowe');xlabel('Czestotliwosc probkowania Fs out');ylabel('Faza sygnalu'); 


audiowrite('1_Zdecymowany.wav',Xd,Fs_Xd);


%%%%%%%%%%%%%%%%%%%%%%%% FILTR FIR %%%%%%%%%%%%%%%%%%%%%%%%%
M=183; % liczba wspó³czynników
fc1=15200; %czêstotliwoœæ granicza 
fp=Fs_A;    %czêstotliwoœæ próbkowania
N=fp;
FDP=prototype(M,fc1,fp);

w4=blackman(M).';
FDP=(FDP).*w4;   % filtr górnoprzepustowy
Yf = filter(FDP,1,A);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


Yf_fft = fft(Yf);
Freq_Yf = Freq_A;
figure('name','Widma sygnalu przefiltrowanego','numbertitle','off')
subplot(2,1,1);stem(Freq_Yf,abs(Yf_fft));title('Widmo Amplitudowe');xlabel('Czestotliwosc probkowania Fs out');ylabel('Amplituda sygnalu');
subplot(2,1,2);plot(Freq_Yf,angle(Yf_fft));title('Widmo Fazowe');xlabel('Czestotliwosc probkowania Fs out');ylabel('Faza sygnalu'); 


[Yfd, Fs_Yfd] = Decymacja(Yf, Fs_A, kd);


Yfd_fft = fft(Yfd);
Freq_Yfd = 0:Fs_Yfd/length(Yfd):Fs_Yfd-(1/Fs_Yfd);
figure('name','Widma sygnalu przefiltrowanego i zdecymowanego','numbertitle','off')
subplot(2,1,1);stem(Freq_Yfd,abs(Yfd_fft));title('Widmo Amplitudowe');xlabel('Czestotliwosc probkowania Fs out');ylabel('Amplituda sygnalu');
subplot(2,1,2);plot(Freq_Yfd,angle(Yfd_fft));title('Widmo Fazowe');xlabel('Czestotliwosc probkowania Fs out');ylabel('Faza sygnalu'); 


audiowrite('2_Przefiltrowany.wav',Yf,Fs_A);
audiowrite('3_FiltrIDecym.wav',Yfd,Fs_Yfd);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%% ZADANIE 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[Bi,Fs_Bi] = Interpolacja(Yfd, Fs_Yfd, ki);


Bi_fft = fft(Bi);
Freq_Bi = 0:Fs_Bi/length(Bi):Fs_Bi-(1/Fs_Bi);
figure('name','Widma sygna³u zinterpolowanego','numbertitle','off')
subplot(2,1,1);stem(Freq_Bi,abs(Bi_fft));title('Widmo Amplitudowe');xlabel('Czestotliwosc probkowania Fs Bi');ylabel('Amplituda sygnalu');
subplot(2,1,2);plot(Freq_Bi,angle(Bi_fft));title('Widmo Fazowe');xlabel('Czestotliwosc probkowania Fs Bi');ylabel('Faza sygnalu'); 


%%%%%%%%%%%%%%%%%%%%%%%% FILTR FIR %%%%%%%%%%%%%%%%%%%%%%%%%
M1=87; % liczba wspó³czynników

fc12=5000; %czêstotliwoœæ granicza 
fp1=Fs_Bi;    %czêstotliwoœæ próbkowania
N=fp;
FDP1=prototype(M1,fc12,fp1);

w4=blackman(M1).';
FDP1=(FDP1).*w4;   % filtr górnoprzepustowy
Cf = filter(FDP1,1,Bi);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Cf_fft = fft(Cf);
Freq_Cf = Freq_Bi;
figure('name','Widma sygnalu przefiltrowanego i zinterpolowanego','numbertitle','off')
subplot(2,1,1);stem(Freq_Cf,abs(Cf_fft));title('Widmo Amplitudowe');xlabel('Czestotliwosc probkowania Fs Bi');ylabel('Amplituda sygnalu');
subplot(2,1,2);plot(Freq_Cf,angle(Cf_fft));title('Widmo Fazowe');xlabel('Czestotliwosc probkowania Fs Bi');ylabel('Faza sygnalu'); 




audiowrite('4_IntePoDecy.wav',Bi,Fs_Bi);
audiowrite('5_FiltrowanaInterpolacja.wav',Cf,Fs_Bi);
