cmake_minimum_required(VERSION 3.13)
project(MultiDimContainer)

add_library(multi-dim-container INTERFACE)

target_include_directories(multi-dim-container
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(multi-dim-container
    INTERFACE
        cxx_std_17
)

target_compile_definitions(multi-dim-container
    INTERFACE
        LIBRARY_HEADER_ONLY
)

install(TARGETS multi-dim-container
    EXPORT MultiDimContainerTargets
    INCLUDES DESTINATION include
)
install(EXPORT MultiDimContainerTargets
    FILE MultiDimContainerTargets.cmake
    NAMESPACE MultiDimContainer::
    DESTINATION lib/cmake/MultiDimContainer
)

option(WITH_TESTS "Build library including tests" off)

if(WITH_TESTS)
    add_subdirectory(test)
endif()