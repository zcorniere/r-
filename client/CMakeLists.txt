set(CMAKE_CXX_STANDARD 20)

add_executable(r-type_client ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_library(r-type_client_lib STATIC)

target_include_directories(r-type_client_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(r-type_client_lib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/components/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/home.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/loading.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/components/interfaces/Iview.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/components/event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/components/network.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/components/interfaces/Ifragment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/fragments/blue.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/fragments/red.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/fragments/inner/magenta.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/views/fragments/inner/green.cpp
)

#target_link_libraries(r-type_client_lib
#        ${CONAN_LIBS_BOOST}
#        ${CONAN_LIBS_SFML}
#)
# prefer conan_target_link_libraries() insteal of target_link_libraries()
# because : https://stackoverflow.com/questions/63290538/how-to-use-conan-to-handle-imgui-sfml-dependency-in-a-cmake-gcc-project-in-linux

conan_target_link_libraries(r-type_client_lib)

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
