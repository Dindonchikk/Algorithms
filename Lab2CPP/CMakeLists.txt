add_executable(Lab2CPP main.cpp)
target_link_libraries(Lab2CPP PRIVATE LibraryCPP)

#1
add_test(
    NAME BefungeTest1_Run
    COMMAND $<TARGET_FILE:Lab2CPP>
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/input1.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/actual1.txt"
)

add_test(
    NAME BefungeTest1_Compare
    COMMAND ${CMAKE_COMMAND} -E compare_files
        "${CMAKE_CURRENT_BINARY_DIR}/actual1.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/output1.txt"
)

set_tests_properties(
    BefungeTest1_Compare
    PROPERTIES DEPENDS BefungeTest1_Run
)

#2
add_test(
    NAME BefungeTest2_Run
    COMMAND $<TARGET_FILE:Lab2CPP>
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/input2.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/actual2.txt"
)

add_test(
    NAME BefungeTest2_Compare
    COMMAND ${CMAKE_COMMAND} -E compare_files
        "${CMAKE_CURRENT_BINARY_DIR}/actual2.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/output2.txt"
)

set_tests_properties(
    BefungeTest2_Compare
    PROPERTIES DEPENDS BefungeTest2_Run
)

#3
add_test(
    NAME BefungeTest3_Run
    COMMAND $<TARGET_FILE:Lab2CPP>
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/input3.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/actual3.txt"
)

add_test(
    NAME BefungeTest3_Compare
    COMMAND ${CMAKE_COMMAND} -E compare_files
        "${CMAKE_CURRENT_BINARY_DIR}/actual3.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/output3.txt"
)

set_tests_properties(
    BefungeTest3_Compare
    PROPERTIES DEPENDS BefungeTest3_Run
)

#4
add_test(
    NAME BefungeTest4_Run
    COMMAND $<TARGET_FILE:Lab2CPP>
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/input4.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/actual4.txt"
)

add_test(
    NAME BefungeTest4_Compare
    COMMAND ${CMAKE_COMMAND} -E compare_files
        "${CMAKE_CURRENT_BINARY_DIR}/actual4.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/Tests/output4.txt"
)

set_tests_properties(
    BefungeTest4_Compare
    PROPERTIES DEPENDS BefungeTest4_Run
)