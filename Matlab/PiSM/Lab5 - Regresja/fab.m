%% rpsim - regresja\

clc;
clear all;


N=10;

a=1-0.95;

U=[1, 3.5, 6, 8.5, 11, 13.5, 16, 18.5, 21, 23.5];

I=[6.0782,4.8160,4.8625,4.9663,3.9332,4.6135,4.4720,3.9858,3.7888,4.1218];


SU=0;


SU2=0;

SI=0;

SUI=0;

for k=1:N 
SU2=SU2+U(k)^2; 
%suma kwadratow napiecia 
SU=SU+U(k); 
% suma napiecia 
SI=SI+I(k); 
% suma pradow 
SUI=SUI+(U(k)*I(k)); 
%suma 

end 
SrI=SI/N; 
% srednia prado 
SrU=SU/N; 
% srednia napiecia 

a0=((SU2 * SI) - (SU * SUI))/ (N*SU2 - (SU)^2) 
% wsp. krzywej regresji 
a1=((N*SUI) - (SU*SI))/ (N*SU2 - (SU)^2) 
% wsp. krzywej regresji 


% Liczymy wsp korelacji i determinacji

mianownikU=0;

mianownikI=0;

licznik=0;

odchylenie_standardowe = 0;
for n=1:N
    odchylenie_standardowe = odchylenie_standardowe + ((I(n) - a0 - (a1*U(n)))^2);
end
odchylenie_standardowe = odchylenie_standardowe * ((1)/(N-2));
odchylenie_standardowe = sqrt(odchylenie_standardowe);
talfa = 2.3060;
mianus = 0;
for i=1:N
    mianus = mianus + ((U(i)-SrU)^2);
end
mianus = sqrt(mianus);
A00 = (talfa * odchylenie_standardowe )/mianus
A11 = (talfa * odchylenie_standardowe)/(sqrt(N))

for k=1:N 
licznik=licznik+((U(k)-SrU)*(I(k)-SrI));

mianownikU=mianownikU +(U(k)-SrU)^2;

mianownikI=mianownikI +(I(k)-SrI)^2;

end 
mianownik=sqrt(mianownikU*mianownikI);

rxy=(licznik/mianownik) 
%Wspolczynnik korelacji (5) 
R2=rxy^2 
%% Wspolczynnik determinacji (17) 

t=(rxy*sqrt(N-2))/(sqrt(1-R2)) 
%% Statystyka , wzor (6) 
ta2=a/2