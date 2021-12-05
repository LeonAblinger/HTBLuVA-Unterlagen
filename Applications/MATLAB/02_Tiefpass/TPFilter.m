%% Simple low pass with Average filter with 2 coefficients
clear;      %clear all variables of the workspace
clc;        %clear
close all;  %close open windows
%%

samples = 100;
start = 30;
tpLength = 5;
finish = samples - start; 
x = linspace(1,1,samples);
for i = 1:start-1
    x(i) = 0;
end
for i = finish:samples
    x(i) = 0;
end
GF = 0.8;
y = linspace(0,0,samples);
y(i) = x(i);
for i = 2:samples
    y(i) =  0.5 * (x(i) + x(i-1));
end
kc = 0:1:samples -1; 
stem(kc,y);