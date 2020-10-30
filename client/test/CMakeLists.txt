set(Boost_USE_STATIC_LIBS OFF)

add_executable(Client_Units_Tests)

target_sources (Client_Units_Tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
        )

target_link_libraries(Client_Units_Tests r-type_client_lib)

target_link_libraries(Client_Units_Tests ${CONAN_LIBS_BOOST})