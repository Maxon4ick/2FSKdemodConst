%Чтение файла
fid = 'FSK2_8000_50Bd_7_5st5.wav';
f = fopen(fid,'rb');
fseek(f,44, 'bof');
s = fread(f,[1,inf],'short');
fclose(f);

%Инициализация констант
fs = 8e3;
ubd = 50;
sampleSize = fs/ubd;
outSize = round(968358/sampleSize);
wLo = 789;
wHi = 1234;

%Генчик
n = 1:1:sampleSize;
op0 = cos(2*pi*wLo/fs*n);
op1 = cos(2*pi*wHi/fs*n);

out = zeros(1,outSize);
strob = zeros(1,sampleSize);
nach = 1;
kon = sampleSize;

for i = 1:1:outSize
    strob = s(nach:kon);
    sinh = fap(strob);
    corOut0 = coran(op0,sinh);
    corOut1 = coran(op1,sinh);
    out(i) = Dumat(corOut0,corOut1);
    nach = i*sampleSize;
    kon = (i+1)*sampleSize-1;
end