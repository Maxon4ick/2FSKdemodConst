function y = fap(s)
N = length(s);
Ks = 1000;
Kd = 1;
Ko = 1;
wp = 2*pi*300;
zeta = 0.5;

fs = 8e3;
T = 1/fs;
f0 = 1.5e3;
df = 600;
fg = f0 - df;
g1 = 2 * (1 - exp(-wp * zeta * T) * cos(wp * sqrt(1 - zeta^2)*T));
g2 = g1 + exp(-2 * wp * zeta * T) - 1;

Ki = g2 / (Ko*Kd);
Kp = g1 / (Ko*Kd);

p = zeros(1,N); % фаза NCO
v = zeros(1,N); % выход фазового детектора
e = zeros(1,N); % выход петлевого фильтра
y = zeros(1,N); % сигнал на выходе NCO
r = zeros(1,N); % ошибка слежения

for i=2:N
    
    % выход фазового детектора
    v(i) = Kd * s(i) * cos(2 * pi * fg/fs * i + p(i-1));
    
    % разностное уравнение петлевого фильтра
    e(i) = Kp * v(i) + (Ki-Kp) * v(i-1) + e(i-1);
    
    % разностное уравнение NCO
    p(i) = 1/Ks * Ko * e(i-1) + p(i-1);
    
    % сигнал, синхронизованный со входным
    y(i) = Ks * sin(2 * pi * fg/fs * i + p(i-1));
    
end

