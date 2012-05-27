
set(CMAKE_C_FLAGS "-g -Wall")

cmake_minimum_required (VERSION 2.6)
project(CHR-UM6)

add_subdirectory(wire_format)
add_subdirectory(tests)
add_subdirectory(regs)
add_subdirectory(interface)
add_subdirectory(sys)
