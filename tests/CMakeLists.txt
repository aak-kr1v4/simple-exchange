cmake_minimum_required(VERSION 3.21)

set(TESTS_PROJECT_NAME TESTS)
enable_testing()

add_executable(${TESTS_PROJECT_NAME} 
    src/main.cpp
)

target_link_libraries(${TESTS_PROJECT_NAME} gtest gtest_main)
target_compile_features(${TESTS_PROJECT_NAME} PUBLIC cxx_std_17)

add_test(NAME ${TESTS_PROJECT_NAME} COMMAND ./${TESTS_PROJECT_NAME})

