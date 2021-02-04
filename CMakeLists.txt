cmake_minimum_required(VERSION 3.17)
project(NESpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(NESpp
        main.cpp
        src/cpu/register/register.cpp
        src/cpu/register/register.h
        src/cpu/register/program_status.cpp
        src/cpu/register/program_status.h
        src/cpu/register/program_counter.cpp
        src/cpu/register/program_counter.h
        src/cpu/register/stack_pointer.cpp
        src/cpu/register/stack_pointer.h
        src/cpu/memory/memory.cpp
        src/cpu/memory/memory.h
        src/cpu/memory/stack.cpp
        src/cpu/memory/stack.h
        src/cpu/cpu.cpp
        src/cpu/cpu.h
        src/utils/hexdump.cpp
        src/utils/hexdump.h
        src/cpu/handlers/opcode_handlers.cpp
        src/cpu/handlers/opcode_handlers.h
        src/cpu/handlers/transfer_opcodes_handlers.cpp
        src/cpu/handlers/transfer_opcodes_handlers.h
        src/utils/bits.h
)

add_subdirectory(googletest)