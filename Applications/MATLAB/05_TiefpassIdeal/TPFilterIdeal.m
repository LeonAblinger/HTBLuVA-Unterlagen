% Lowpass filter
clear;      %clear all variables of the workspace
clc;        %clear
close all;  %close open windows
%%

% Read coefficients from Excel-File
filename = 'TPFilterIdeal.xlsx';
b = xlsread( filename, 'B12:B62' );

[h,w] = freqz( b, 1, 1024 );
mag = 20 * log10( abs(h) );
plot( w/pi, mag ); grid
