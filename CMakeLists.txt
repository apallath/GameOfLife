cmake_minimum_required(VERSION 3.10)

project(GameOfLife)

# Require C++ 14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# All .cpp files from src/
file(GLOB SOURCES "src/*.cpp")

# Find boost (required)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})
message("boost lib: ${Boost_LIBRARIES}, inc:${Boost_INCLUDE_DIR}")

add_executable(GameOfLife ${SOURCES})

# Link
target_link_libraries(GameOfLife ${Boost_LIBRARIES})

#####################
# Testing           #
#####################

enable_testing()

add_subdirectory(tests)