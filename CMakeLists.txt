cmake_minimum_required(VERSION 3.13)
project(MultiDimContainer VERSION 0.1)

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

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/MultiDimContainerConfigVersion.cmake
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/MultiDimContainerConfig.cmake.in
    ${CMAKE_BINARY_DIR}/MultiDimContainerConfig.cmake
    INSTALL_DESTINATION lib/cmake/MultiDimContainer
)

install(TARGETS multi-dim-container
    EXPORT MultiDimContainerTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION bin COMPONENT Runtime
)

install(EXPORT MultiDimContainerTargets
    NAMESPACE MultiDimContainer::
    DESTINATION lib/cmake/MultiDimContainer
)

install(FILES
    ${CMAKE_BINARY_DIR}/MultiDimContainerConfigVersion.cmake
    ${CMAKE_BINARY_DIR}/MultiDimContainerConfig.cmake
    DESTINATION lib/cmake/MultiDimContainer
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

option(WITH_TESTS "Build library including tests" off)

if(WITH_TESTS)
    add_subdirectory(test)
endif()