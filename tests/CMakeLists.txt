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