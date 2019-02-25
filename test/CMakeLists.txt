cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.8.1
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_executable(container-test
    main.cpp
    ArrayTest.cpp
)

target_link_libraries(container-test gtest)
target_link_libraries(container-test multi-dim-container)
