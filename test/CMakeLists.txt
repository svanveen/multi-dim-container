cmake_minimum_required(VERSION 3.11)

enable_testing()
find_package(GTest REQUIRED)

add_executable(container-test)

target_sources(container-test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ArrayTest.cpp
)


target_link_libraries(container-test
    PRIVATE
        GTest::GTest
        multi-dim-container
)
