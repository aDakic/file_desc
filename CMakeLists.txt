cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(fd
        VERSION 1.0.0
        LANGUAGES CXX)

include(cmake/standard_settings.cmake)
include(cmake/tools.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

set(headers include/${PROJECT_NAME}/fd.hpp)
set(sources src/fd.cpp)

add_library(${PROJECT_NAME} ${headers} ${sources})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()