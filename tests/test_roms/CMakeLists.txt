add_executable(nestest_run
    cpu/nestest.h
    cpu/main.cpp
)

target_link_libraries(nestest_run ${CMAKE_PROJECT_NAME}_lib)

#copy the res folder where "nestest_run" is built
add_custom_command(TARGET nestest_run POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:nestest_run>/res
)
