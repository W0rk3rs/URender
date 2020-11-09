@echo off

IF not exist build (
echo Project isn't built!
pause
exit
)

cd .\build\Debug

start URender.exe