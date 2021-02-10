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
    cpu/machine.h
    cpu/handlers/flag_opcodes_handlers.h
    cpu/handlers/store_opcodes_handlers.h
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
    cpu/machine.cpp
    cpu/handlers/store_opcodes_handlers.cpp
    cpu/handlers/flag_opcodes_handlers.cpp
        cpu/handlers/bitwise_opcodes_handlers.cpp cpu/handlers/bitwise_opcodes_handlers.h cpu/handlers/branch_opcodes_handlers.cpp cpu/handlers/branch_opcodes_handlers.h cpu/handlers/stack_opcodes_handlers.cpp cpu/handlers/stack_opcodes_handlers.h cpu/handlers/compare_opcodes_handlers.cpp cpu/handlers/compare_opcodes_handlers.h cpu/handlers/math_opcodes_handlers.cpp cpu/handlers/math_opcodes_handlers.h cpu/handlers/system_opcode_handlers.cpp cpu/handlers/system_opcode_handlers.h cpu/handlers/opcodes.h utils/debug.h cpu/handlers/jump_opcodes_handlers.cpp cpu/handlers/jump_opcodes_handlers.h)

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