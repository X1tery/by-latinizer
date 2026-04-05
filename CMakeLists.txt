cmake_minimum_required(VERSION 3.23)

project(by-latin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/headers")


add_executable(bycyrlat)

target_sources(bycyrlat
PRIVATE
    src/maincyrlat.cpp
    src/headers/unicode.hpp
    src/headers/cyrlat.hpp
    src/code/unicode.cpp
    src/code/cyrlat.cpp
)

add_executable(bylatcyr)

target_sources(bylatcyr
PRIVATE
    src/mainlatcyr.cpp
    src/headers/unicode.hpp
    src/headers/latcyr.hpp
    src/code/unicode.cpp
    src/code/latcyr.cpp
)