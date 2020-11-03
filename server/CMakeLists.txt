include_directories(./include/ )
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(r-type_server
                            source/main.cpp
                            source/StateMachine.cpp
                            source/ComponentStorage.cpp
                            source/Snitch.cpp
                            source/Game.cpp
                            source/components/Transform.cpp
)

add_executable(tests_StateMachine
                            source/StateMachine.cpp
                            tests/StateMachineTests.cpp
)

add_executable(tests_ComponentStorage
                            source/ComponentStorage.cpp
                            source/Snitch.cpp
                            tests/ComponentStorageTests.cpp
)
