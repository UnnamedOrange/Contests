@echo off
set /p name=�������ļ���:
set /p cnt=�������ļ�����:
for /L %%i in (1,1,%cnt%) do rename %name%%%i.ans %name%%%i.out
