cmake_minimum_required(VERSION 3.1.0)
project(r-type)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# Conan configuration

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# link_libraries(${CONAN_LIBS})
# The target_link_libraries() command should be preferred whenever possible
# https://cmake.org/cmake/help/v3.1/command/link_libraries.html

# contains include of the conan libs:
include_directories(${CMAKE_INCLUDE_PATH})

# Build the server and the client
add_subdirectory(server)
add_subdirectory(client)

