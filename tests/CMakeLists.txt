cmake_minimum_required(VERSION 3.21)

set(TESTS_PROJECT_NAME TESTS)
enable_testing()

add_executable(${TESTS_PROJECT_NAME} 
    src/main.cpp
    src/UsersTests.cpp
    src/MatchTests.cpp
)

target_include_directories(${TESTS_PROJECT_NAME} PRIVATE ../include)
target_include_directories(${TESTS_PROJECT_NAME} PRIVATE ../external/includes)

target_link_libraries(${TESTS_PROJECT_NAME} PUBLIC gtest gtest_main simple-exchange-core)
target_compile_features(${TESTS_PROJECT_NAME} PUBLIC cxx_std_17)

add_test(NAME ${TESTS_PROJECT_NAME} COMMAND ./${TESTS_PROJECT_NAME})
