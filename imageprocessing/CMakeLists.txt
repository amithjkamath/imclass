cmake_minimum_required(VERSION 3.5)
project(imageprocessing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

include_directories( ${MY_SOURCE_DIR}../include )

set(SOURCE_FILES image.cpp jpgImage.cpp pngImage.cpp processImage.cpp)
find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
# Create a static library called imageprocessing that holds all these functions.
# Use target_link_libraries() to use it.
add_library(imageprocessing ${SOURCE_FILES})