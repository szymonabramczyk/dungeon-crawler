cmake_minimum_required(VERSION 3.0.0)
project(dungeon-crawler-quang-ngo-01 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SOURCES src/*.cpp)
add_executable(dungeon-crawler-quang-ngo-01 ${SOURCES})

target_link_libraries(dungeon-crawler-quang-ngo-01 PRIVATE sfml-graphics)
target_compile_features(dungeon-crawler-quang-ngo-01 PRIVATE cxx_std_17)



install(TARGETS dungeon-crawler-quang-ngo-01)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


FILE(COPY content/sprites/player.png DESTINATION "${CMAKE_BINARY_DIR}")