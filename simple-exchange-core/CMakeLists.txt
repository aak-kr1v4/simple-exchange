cmake_minimum_required(VERSION 3.21)

set(CORE_PROJECT_NAME simple-exchange-core)

add_library(${CORE_PROJECT_NAME} STATIC
    src/simple-exchange-core/Core/Core.cpp
    includes/simple-exchange-core/Core/Core.hpp

    src/simple-exchange-core/User/User.cpp
    includes/simple-exchange-core/User/User.hpp

    src/simple-exchange-core/Utils/CurrencyUtil.cpp
    includes/simple-exchange-core/Utils/CurrencyUtil.hpp

    src/simple-exchange-core/Order/Order.cpp
    includes/simple-exchange-core/Order/Order.hpp
)

target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE ../include)
target_include_directories(${CORE_PROJECT_NAME} PRIVATE ../external/includes)

target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)