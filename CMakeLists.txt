cmake_minimum_required(VERSION 3.11.2)
project(r-type)

# Conan configuration
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
# https://stackoverflow.com/questions/63290538/how-to-use-conan-to-handle-imgui-sfml-dependency-in-a-cmake-gcc-project-in-linux

# link_libraries(${CONAN_LIBS})
# The target_link_libraries() command should be preferred whenever possible
# https://cmake.org/cmake/help/v3.1/command/link_libraries.html

# contains include of the conan libs:
include_directories(${CMAKE_INCLUDE_PATH})

# Build the server and the client
add_subdirectory(server)
add_subdirectory(client)

