## 'tests' is the subproject name
#project(googletest)
#
## 'lib' is the folder with Google Test sources
#add_subdirectory(googletest)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#
## 'googletest_run' is the target name
## 'test1.cpp tests2.cpp' are source files with tests
##add_executable(googletest_run test1.cpp tests2.cpp)
#
#add_executable(googletest_run
#        cpu/handlers/transfer_opcode_handlers_tests.cpp
#)
#
#target_link_libraries(googletest_run gtest gtest_main)

project(${CMAKE_PROJECT_NAME}_tests)

set(GOOGLETEST_DIR ${CMAKE_SOURCE_DIR}/tests/googletest)
if(NOT EXISTS ${GOOGLETEST_DIR})
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone https://github.com/google/googletest ${GOOGLETEST_DIR}
    )
endif()

add_subdirectory(googletest)
add_subdirectory(unit_tests)