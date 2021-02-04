# 'googletest' is the subproject name
project(googletest)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest-release-1.10.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'googletest_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
#add_executable(googletest_run test1.cpp tests2.cpp)

add_executable(googletest_run
        cpu/handlers/transfer_opcode_handlers_tests.cpp
)

target_link_libraries(googletest_run gtest gtest_main)
