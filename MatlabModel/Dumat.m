function Out = Dumat(corOut0,corOut1)
len = length(corOut0);
max0 = 0;
max1 = 0;
corOut0 = abs(corOut0);
corOut1 = abs(corOut1);
for i = 1:1:len
    if (corOut0(i) > max0)
        max0 = corOut0(i);
    end
    if (corOut1(i) > max1)
        max1 = corOut1(i);
    end
end
 if (max0>max1)
     Out = 0;
 else
     Out = 1;
 end
end