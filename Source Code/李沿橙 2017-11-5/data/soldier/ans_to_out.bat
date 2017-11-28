@echo off
set /p name=请输入文件名:
set /p cnt=请输入文件数量:
for /L %%i in (1,1,%cnt%) do rename %name%%%i.ans %name%%%i.out
