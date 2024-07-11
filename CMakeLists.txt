cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME simple-exchange)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

add_subdirectory(simple-exchange-core)
add_subdirectory(simple-exchange-server)
add_subdirectory(simple-exchange-client)
add_subdirectory(external/googletest)
add_subdirectory(tests)

