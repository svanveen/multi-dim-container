cmake_minimum_required(VERSION 3.11)

enable_testing()
find_package(GTest REQUIRED)

add_executable(container-test)

target_sources(container-test
    PRIVATE
        main.cpp
        ArrayTest.cpp
)

target_link_libraries(container-test
    PRIVATE
        GTest::GTest
        multi-dim-container
)

install(TARGETS container-test
    RUNTIME DESTINATION test
)
