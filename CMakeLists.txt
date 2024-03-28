cmake_minimum_required(VERSION 3.0)
project(aathalg)

# Set C++ standard to at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_library(aathalg_lib ${MAIN_SOURCES})

# Add an executable target for the main application and link with the library
# add_executable(main main.cpp)
# target_link_libraries(main aathalg_lib)

# Add an executable target for the tests and link with the library
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests aathalg_lib)

# Optionally, link the main application against additional libraries
# target_link_libraries(main <library1> <library2> ...)

# Optionally, link the tests against additional libraries
# target_link_libraries(tests <library1> <library2> ...)
