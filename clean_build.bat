@echo off

IF not exist build (
mkdir build
)

cd build
cmake -A Win32 -S .. -B .
cmake --build .

cd ..

IF not exist .\build\Debug\res (
xcopy .\Renderer\res .\build\Debug\res /E/C/I
)
cd .\build\Debug

start URender.exe