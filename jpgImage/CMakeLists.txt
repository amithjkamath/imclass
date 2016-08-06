cmake_minimum_required(VERSION 3.3)
project(jpgImageIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES main.cpp jpgImage.cpp jpgImage.h image.cpp image.h processImage.h processImage.cpp)

find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
# Create a static library called imageprocessing that holds all these functions.
# Use target_link_libraries() to use it.
# add_library(imageprocessing ${SOURCE_FILES})
add_executable(jpgImageIO ${SOURCE_FILES})
target_link_libraries(jpgImageIO ${JPEG_LIBRARY})
