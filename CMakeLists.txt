cmake_minimum_required(VERSION 3.5)
project(algae)

# Set C++ standard to at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Add the include directory to the search path for header files
include_directories(include)

# Define the sources for the main application
set(MAIN_SOURCES
    src/graph.cpp
)

# Define the sources for the test executable
set(TEST_SOURCES
    tests/main.cpp
)

# Add a library target for the main sources
add_library(algae_lib ${MAIN_SOURCES})


# Add an executable target for the tests and link with the library
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests algae_lib)