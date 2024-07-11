cmake_minimum_required(VERSION 3.21)

set(SERVER_PROJECT_NAME simple-exchange-server)

add_executable(${SERVER_PROJECT_NAME} 
    src/main.cpp
    src/Session/Session.hpp
    src/Session/Session.cpp
    src/Server/Server.hpp
    src/Server/Server.cpp
)

find_package(Boost 1.40 COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)


target_include_directories(${SERVER_PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${SERVER_PROJECT_NAME} PRIVATE ../include)
target_include_directories(${SERVER_PROJECT_NAME} PRIVATE ../external/includes)


target_link_libraries(${SERVER_PROJECT_NAME} PRIVATE Threads::Threads ${Boost_LIBRARIES})
target_link_libraries(${SERVER_PROJECT_NAME} PRIVATE simple-exchange-core)


target_compile_features(${SERVER_PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${SERVER_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
