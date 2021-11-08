# R-Type

## Prerequisites

Conan, cmake, make, gcc 10

### Conan

``` sh
pip install conan
conan remote add bincrafters  https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
```

## Building

``` sh
mkdir build
cd build
conan install .. --build=missing
cmake ..
cmake --build .
```
