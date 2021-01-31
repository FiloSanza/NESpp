cmake_minimum_required(VERSION 3.17)
project(NESpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(NESpp main.cpp src/cpu/register/register.cpp src/cpu/register/register.h src/cpu/register/program_status.cpp src/cpu/register/program_status.h src/cpu/register/program_counter.cpp src/cpu/register/program_counter.h src/cpu/register/stack_pointer.cpp src/cpu/register/stack_pointer.h)

#add_subdirectory(googletest)