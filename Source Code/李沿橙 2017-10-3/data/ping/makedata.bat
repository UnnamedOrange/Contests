g++ gen.cpp -o gen.exe
g++ ping.cpp -o ping.exe
gen.exe > ping19.in
ping.exe < ping19.in > ping19.out