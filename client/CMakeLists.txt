set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    # SFML static link fix
    add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
    add_compile_options(
            $<$<CONFIG:>:/MD> #---------|
            $<$<CONFIG:Debug>:/MD> #----|-- Statically link the runtime libraries (sfml fix)
            $<$<CONFIG:Release>:/MD> #--|
    )
endif()

link_directories(${CMAKE_BINARY_DIR}/bin)

add_executable(r-type_client ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_library(r-type_client_lib STATIC)

target_include_directories(r-type_client_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(r-type_client_lib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/network.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Iview.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Ifragment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Icolors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sdk/interfaces/Istring.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/colors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/strings/common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/strings/fr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/res/strings/en.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/home.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/app/views/loading.cpp
)

conan_target_link_libraries(r-type_client_lib)
#target_link_libraries(r-type_client_lib
#        ${CONAN_LIBS_BOOST}
#        ${CONAN_LIBS_SFML}
#)

target_link_libraries(r-type_client r-type_client_lib)

# Linking assets client folder
if (WIN32)
    add_custom_command(TARGET r-type_client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
else()
    ADD_CUSTOM_TARGET(assets ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
endif()

# Warning handling
set(MSVC_FLAGS /w)
set(GCC_FLAGS -Wall -Wextra -pedantic -Werror)

if(MSVC)
    target_compile_options(r-type_client PRIVATE ${MSVC_FLAGS})
else()
    target_compile_options(r-type_client PRIVATE ${GCC_FLAGS})
endif()

# Unit Tests
add_subdirectory(test)
