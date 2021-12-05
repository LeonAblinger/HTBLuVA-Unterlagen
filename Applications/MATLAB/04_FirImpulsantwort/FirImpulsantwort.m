% Lowpass filter with 8 coefficients
clear;      %clear all variables of the workspace
clc;        %clear
close all;  %close open windows
%%

f = 0.3; % Testfrequenz
fa = 10;
t = linspace( -f * fa * pi, f * fa * pi, 100 );
rng default; % Initialize random number geneartor
x = sin(t) + 0.25 * rand(size(t));

% Read coefficients from excel file
filename = 'FirImpulsantwort.xlsx';
d = xlsread( filename, 'B8:B15');
%%
freqz(d);
%%
figure;
y = filter( d, 1, x );
plot( t, x );
hold on
plot( t, y );
legend('Input data', 'Filter data');