set(CMAKE_CXX_STANDARD 20)

add_executable(r-type_client)

target_include_directories(r-type_client PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(r-type_client PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(r-type_client
${CONAN_LIBS_BOOST}
${CONAN_LIBS_SFML}
)

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