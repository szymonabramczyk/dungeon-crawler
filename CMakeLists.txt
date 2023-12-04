cmake_minimum_required(VERSION 3.0.0)
project(dungeon-crawler-quang-ngo-01 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES src/*.cpp)
add_executable(dungeon-crawler-quang-ngo-01 ${SOURCES})
target_link_libraries(dungeon-crawler-quang-ngo-01 PRIVATE sfml-graphics sfml-audio)
target_compile_features(dungeon-crawler-quang-ngo-01 PRIVATE cxx_std_17)

# Google Test Executable
file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(tests ${TEST_SOURCES} src/Assets.cpp)
target_link_libraries(tests gtest_main sfml-graphics sfml-audio)
add_test(NAME example_test COMMAND tests)

install(TARGETS dungeon-crawler-quang-ngo-01)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Assets copying
file(GLOB SPRITES "content/sprites/*.png")
FILE(COPY ${SPRITES} DESTINATION "${CMAKE_BINARY_DIR}")

file(GLOB FONTS "content/fonts/*.ttf")
FILE(COPY ${FONTS} DESTINATION "${CMAKE_BINARY_DIR}")

file(GLOB SOUNDS "content/sounds/*.wav")
FILE(COPY ${SOUNDS} DESTINATION "${CMAKE_BINARY_DIR}")
