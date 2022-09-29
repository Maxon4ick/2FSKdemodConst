function k = sinhr(in)
s = abs(in);
m = max(s);
m = abs(m);
En = length(s);
for k = 1:En
    if s(k)>0.05*m
        break;
    end
end
