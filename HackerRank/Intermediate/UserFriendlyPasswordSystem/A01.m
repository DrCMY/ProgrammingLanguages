% https://www.rapidtables.com/code/text/ascii-table.html
clear,clc
format long
M = 10^9+7;
p = 131;
s = 'cAr1B';
us = double(s);
n = strlength(s);

h = 0;
for i=1:n
    h = h + us(i)*p^(n-i);
end
h
h = mod(h,M)