% Diskrete Faltung
clear;      %clear all variables of the workspace
clc;        %clear
close all;  %close open windows
%%

% Definition of signal arrays
x = [1 -1 -1 1 0 0 0];
k1min = 0;
k1 = length(x);

h = [1 0.75 0.5 0.25];
k2min = 0;
k2 = length(h);

% Calculation of convolution (faltung)
y = conv(x,h);

% Display x
kmin = k2min + k1min;
k = k1 + k2 - 1;
kc = kmin:1:kmin + k - 1;


kx = kmin:1:k1 - 1;
stem(kx,x);
title('input x');
% h
figure
kh = k2min:1:k2-1;
stem(kh,h);
title('Impulse response');




