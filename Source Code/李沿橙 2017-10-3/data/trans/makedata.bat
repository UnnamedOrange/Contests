g++ gen.cpp -o gen.exe
g++ trans.cpp -o trans.exe
gen.exe > trans8.in
trans.exe < trans8.in > trans8.out
gen.exe > trans9.in
trans.exe < trans9.in > trans9.out
gen.exe > trans10.in
trans.exe < trans10.in > trans10.out