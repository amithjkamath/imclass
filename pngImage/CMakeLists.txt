cmake_minimum_required(VERSION 3.3)
project(pngImageIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

add_executable(pngImageIO ${SOURCE_FILES})
target_link_libraries(pngImageIO ${PNG_LIBRARY} ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libimageprocessing.a)
