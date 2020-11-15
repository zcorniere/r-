set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    # boost static link fix
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    add_compile_options(
            $<$<CONFIG:>:/MD> #---------|
            $<$<CONFIG:Debug>:/MD> #----|-- Statically link the runtime libraries (boost fix)
            $<$<CONFIG:Release>:/MD> #--|
    )
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

link_directories(${CMAKE_BINARY_DIR}/bin)

add_executable(server_udp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(server_udp PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_sources(server_udp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/process.cpp
)

conan_target_link_libraries(server_udp)

# Warning handling
set(MSVC_FLAGS /w)
set(GCC_FLAGS -Wall -Wextra -pedantic -Werror)

if(MSVC)
    target_compile_options(server_udp PRIVATE ${MSVC_FLAGS})
else()
    target_compile_options(server_udp PRIVATE ${GCC_FLAGS})
endif()
target_compile_definitions(server_udp PUBLIC BOOST_BIND_GLOBAL_PLACEHOLDERS=1)

