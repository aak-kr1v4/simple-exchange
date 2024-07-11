cmake_minimum_required(VERSION 3.21)

set(CORE_PROJECT_NAME simple-exchange-core)

add_library(${CORE_PROJECT_NAME} STATIC
    src/simple-exchange-core/Core/Core.cpp
    includes/simple-exchange-core/Core/Core.hpp
)

target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE ../include)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE ../external/includes)

target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)