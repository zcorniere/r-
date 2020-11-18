include_directories(./include/ )
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(r-type_engine STATIC
                            source/StateMachine.cpp
                            source/ComponentStorage.cpp
                            source/Snitch.cpp
                            source/Game.cpp
                            source/states/DebugState.cpp
                            source/components/Transform.cpp
                            source/System.cpp
                            source/SystemStorage.cpp
)
target_link_libraries(r-type_engine CONAN_PKG::boost)


add_executable(tests_StateMachine
                            tests/StateMachineTests.cpp
)

conan_target_link_libraries(tests_StateMachine)
target_link_libraries(tests_StateMachine r-type_engine)


add_executable(tests_ComponentStorage
                        tests/ComponentStorageTests.cpp
)

conan_target_link_libraries(tests_ComponentStorage)
target_link_libraries(tests_ComponentStorage r-type_engine)


add_executable(tests_System
                        tests/SystemTest.cpp
)

conan_target_link_libraries(tests_System)
target_link_libraries(tests_System r-type_engine)
