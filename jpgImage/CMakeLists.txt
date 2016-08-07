cmake_minimum_required(VERSION 3.3)
project(jpgImageIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )

find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})

add_executable(jpgImageIO ${SOURCE_FILES})
target_link_libraries(jpgImageIO ${JPEG_LIBRARY} ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libimageprocessing.a)
