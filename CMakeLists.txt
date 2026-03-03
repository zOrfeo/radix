cmake_minimum_required(VERSION 3.16)
project(radix VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files (now prefixed with src/)
set(SOURCES
    src/main.cpp
    src/parsing/parsing.cpp
    src/validation/validation.cpp
    src/conversion/conversion.cpp
    src/core/core.cpp
    src/logging/logging.cpp
)

set(HEADERS
    include/constants.h
    include/base.h
    include/parsing/parsing.h
    include/validation/validation.h
    include/conversion/conversion.h
    include/core/core.h
    include/logging/logging.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE

)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2   # or latest stable
)

FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests
    ${HEADERS}
    tests/test_conversion.cpp
    tests/test_core.cpp
    tests/test_parsing.cpp
    tests/test_validation.cpp
    src/conversion/conversion.cpp
    src/parsing/parsing.cpp
    src/validation/validation.cpp
    src/core/core.cpp
)

target_include_directories(unit_tests
    PRIVATE include
)

target_link_libraries(unit_tests
    PRIVATE Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(unit_tests)
