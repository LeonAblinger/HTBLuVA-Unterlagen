% Sampling a signal f0 with different sample periods
clear;		% clear all variables of the workspace
clc;		% clear
close all; 	% close open windows

%%
f0 = 5;
tmin = 0;
tmax = 2;
t0 = linspace( tmin, tmax, 2000 );

% Plot the continious signal
x_c = sin( 2 * pi * f0 * t0 );
plot( t0, x_c );
xlabel('t (seconds)');
grid;

%%
f1 = 64; % 1st sample frequency 64Hz
f2 =  6; % 2nd sample frequency  6Hz
T1 = 1 / f1;
T2 = 1 / f2;
n1 = floor( tmax / T1 );
n  = 0 : n1; % = 0 : 1 : n1;
x1 = sin( 2 * pi * f0 * n * T1 );
hold on;
plot( n * T1, x1, '.' );
hold off;

%%
% Second sample frequency
figure;
plot( t0, x_c );
xlabel('t (seconds)');
grid;
n2 = floor( tmax / T2 );
n  = 0 : n2;
x1 = sin( 2 * pi * f0 * n * T2 );
hold on;
plot( n * T2, x1, '.' );
hold off;

%%
figure;
falias = 1;
x_c = -sin( 2 * pi * falias * t0 );
plot( t0, x_c );
xlabel('t (seconds)');
hold on;
plot( n * T2, x1, '.' );
hold off;