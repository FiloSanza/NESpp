project(${CMAKE_PROJECT_NAME}_lib)

set(HEADER_FILES
    cpu/register/register.h
    cpu/register/program_status.h
    cpu/register/program_counter.h
    cpu/register/stack_pointer.h
    cpu/memory/memory.h
    cpu/memory/stack.h
    cpu/cpu.h
    utils/hexdump.h
    cpu/handlers/opcode_handlers.h
    cpu/handlers/transfer_opcodes_handlers.h
    utils/bits.h
)

set(SOURCE_FILES
    cpu/register/register.cpp
    cpu/register/program_status.cpp
    cpu/register/program_counter.cpp
    cpu/register/stack_pointer.cpp
    cpu/memory/memory.cpp
    cpu/memory/stack.cpp
    cpu/cpu.cpp
    cpu/handlers/opcode_handlers.cpp
    cpu/handlers/transfer_opcodes_handlers.cpp
    utils/hexdump.cpp
        cpu/machine.cpp cpu/machine.h)

if (DEFINED SOURCE_FILES)
    add_library(
        ${CMAKE_PROJECT_NAME}_lib
        STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
    )
else()
    add_library(${CMAKE_PROJECT_NAME}_lib INTERFACE)
endif()