cmake_minimum_required(VERSION 3.16)
project(radix VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files (now prefixed with src/)
set(SOURCES
    src/main.cpp
    src/parsing/parsing.cpp
    src/validation/validation.cpp
)

set(HEADERS
    include/constants.h
    include/base.h
    include/parsing/parsing.h
    include/validation/validation.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE

)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)
