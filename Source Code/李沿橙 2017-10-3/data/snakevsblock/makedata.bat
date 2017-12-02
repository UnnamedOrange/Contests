echo off
g++ gen.cpp -o gen.exe
:TAT
gen.exe > snakevsblock12.in
snakevsblock.exe < snakevsblock12.in > snakevsblock12.out