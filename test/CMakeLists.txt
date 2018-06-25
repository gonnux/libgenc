file(GLOB test_srcs RELATIVE ${CMAKE_SOURCE_DIR}/test *.c)
foreach(test_src ${test_srcs})
    string(REGEX REPLACE "(.*)\\.c$" "\\1" test_exe ${test_src})
    add_executable(${test_exe} ${test_src})
    set_target_properties(${text_exe} PROPERTIES
                                      C_STANDARD_REQUIRED on 
                                      C_STANDARD 11)
    target_link_libraries(${test_exe} cmocka)
    add_test(NAME ${test_exe} COMMAND ${test_exe})
endforeach()
