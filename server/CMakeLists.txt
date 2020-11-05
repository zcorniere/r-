include_directories(
./include/
../engine/include/
)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(r-type_server
                            source/main.cpp
)

target_link_libraries(r-type_server r-type_engine)
