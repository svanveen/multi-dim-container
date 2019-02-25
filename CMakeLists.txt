cmake_minimum_required(VERSION 3.13)
project(MultiDimContainer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(test)

add_library(multi-dim-container INTERFACE)
target_sources(multi-dim-container INTERFACE ${CMAKE_SOURCE_DIR}/include)

target_include_directories(multi-dim-container INTERFACE ${CMAKE_SOURCE_DIR}/include)