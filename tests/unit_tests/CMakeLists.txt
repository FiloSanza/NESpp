include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests_run
    cpu/handlers/transfer_opcode_handlers_tests.cpp
        )

target_link_libraries(tests_run gtest gtest_main)
target_link_libraries(tests_run ${CMAKE_PROJECT_NAME}_lib)