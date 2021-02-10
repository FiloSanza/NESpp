include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests_run
        cpu/handlers/transfer_opcode_handlers.cpp
        cpu/handlers/store_opcodes_handlers.cpp cpu/handlers/flag_opcodes_handlers.cpp cpu/handlers/bitwise_opcodes_handlers.cpp cpu/handlers/branch_opcodes_handlers.cpp cpu/handlers/stack_opcodes_handlers.cpp cpu/handlers/compare_opcodes_handlers.cpp cpu/handlers/math_opcodes_handlers.cpp cpu/handlers/system_opcodes_handlers.cpp)

target_link_libraries(tests_run gtest gtest_main)
target_link_libraries(tests_run ${CMAKE_PROJECT_NAME}_lib)