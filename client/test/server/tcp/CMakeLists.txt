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

add_executable(server_tcp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_include_directories(server_tcp PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_sources(server_tcp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/process.cpp
)

conan_target_link_libraries(server_tcp)

# Linking assets client folder
if (WIN32)
    add_custom_command(TARGET server_tcp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
else()
    ADD_CUSTOM_TARGET(assets ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
endif()

# Warning handling
set(MSVC_FLAGS /w)
set(GCC_FLAGS -Wall -Wextra -pedantic -Werror)

if(MSVC)
    target_compile_options(server_tcp PRIVATE ${MSVC_FLAGS})
else()
    target_compile_options(server_tcp PRIVATE ${GCC_FLAGS})
endif()
target_compile_definitions(server_tcp PUBLIC BOOST_BIND_GLOBAL_PLACEHOLDERS=1)

