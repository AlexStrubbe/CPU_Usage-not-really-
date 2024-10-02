cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -s")

include_directories(include)

# Set the project name
project(cpu_usage)

# Add the executable
add_executable(cpu_usage 
	src/threader.c
	src/functions.c)

target_link_libraries(cpu_usage  ${CURSES_LIBRARIES})
target_link_libraries(cpu_usage  m)