@ECHO OFF
if not exist ".\cmake-build-debug\" mkdir cmake-build-debug
cd cmake-build-debug
conan install .. -b missing
cmake .. -G "Visual Studio 16 2019"
cmake --build .