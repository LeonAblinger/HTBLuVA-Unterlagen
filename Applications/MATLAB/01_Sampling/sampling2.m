% Signal mit f0 = 17kHZ abgetastet mit fa = 15kHz
% oder auch mit 19kHz -> Vorzeichen sichtbar!
% Zeige die Aliasingfrequenz

clear;      % lösche alle Variablen im Workspace
close all;  % Schließt alle offenen Fenster
clc;        % Clear command

%%
f0 = 17000;     % Sinus (Referenzsignal) mit 17 kHz
U0 = 1;         % Amplitude mit 1V
fs1 = 200000;   % Abtastfrequenz fs1, Nyquist erfüllt
fs2 = 15000;    % Abtastfrequenz fs2
fs3 = 19000;    % Abtastfrequenz fs3

tmax = 0.0012;

t1 = 0 : 1/fs1 : tmax; % Array von 0 bis tmax mit Schrittweite 1/fs1
t2 = 0 : 1/fs2 : tmax;
t3 = 0 : 1/fs3 : tmax;

u0 = U0 * sin( 2 * pi * f0 * t1 );
u1 = U0 * sin( 2 * pi * f0 * t2 );
u2 = U0 * sin( 2 * pi * f0 * t3 );

% Liniendiagramm ausgeben
figure( 'Name', 'Sampling - f0', 'NumberTitle', 'off' );
subplot( 3, 1, 1 ), plot( t1, u0, 'LineWidth', 1), grid
xlabel( 'Time t [s] \rightarrow' );
ylabel( 'u(t) \rightarrow' );
title( 'u(t) = 17kHz, Abtastung = 200kHz' );

subplot( 3, 1, 2 ), plot( t1, u0, 'LineWidth', 1), grid
hold on;
plot( t2, u1, 'LineWidth', 1 ), grid
xlabel( 'Time t [s] \rightarrow' );
ylabel( 'u(t) \rightarrow' );
title( 'u(t) = 17kHz, Abtastung = 15kHz' );

subplot( 3, 1, 3 ), plot( t1, u0, 'LineWidth', 1), grid
hold on;
plot( t3, u2, 'LineWidth', 1 ), grid
xlabel( 'Time t [s] \rightarrow' );
ylabel( 'u(t) \rightarrow' );
title( 'u(t) = 17kHz, Abtastung = 19kHz' );

