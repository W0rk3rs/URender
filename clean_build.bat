@echo off

IF exist build (
echo DO you want to renew your build?
rmdir /s build
echo Deleting existing build
)

mkdir build
cd build
cmake -A Win32 -S .. -B .
cmake --build .

cd ..
xcopy .\Renderer\res .\build\Debug\res /E/C/I

cd .\build\Debug

start URender.exe