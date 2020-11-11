include_directories(
../engine/include/
../server/include/
)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(r-type_local
                            source/main.cpp
                            source/SfmlModule.cpp
                            source/SfmlAudioModule.cpp
                            ../server/source/LevelState.cpp
                            ../server/source/GameServer.cpp
                            ../server/source/AssetsServer.cpp
                            ../server/source/Storage.cpp
)

target_link_libraries(r-type_local r-type_engine)
