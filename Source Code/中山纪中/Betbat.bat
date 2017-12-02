@echo off
:AC
make.exe
echo finish data
echo start 1
1.exe < data.in > 1.out
echo finish 1
echo start 2
2.exe < data.in > 2.out
echo finish 2
fc 1.out 2.out
if errorlevel 1 goto WA
echo Accepted
goto AC
:WA
echo Wrong Answer
pause
