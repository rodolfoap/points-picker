cmake_minimum_required(VERSION 3.10)
project(ppicker)

# Force C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Equivalent to (CFLAGS) -g
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "Binary ppicker will go to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "CMakeLists.txt contents:")
execute_process(COMMAND sed "s/^/\t/" CMakeLists.txt
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	RESULT_VARIABLE CMD_ERROR)

# Equivalent to (CFLAGS) -g
set(CMAKE_C_FLAGS "-g")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
set(SFML_STATIC_LIBRARIES TRUE)

add_executable(ppicker window.cpp form.cpp main.cpp)

target_link_libraries(ppicker sfml-graphics sfml-window sfml-system sfml-audio stdc++fs)
