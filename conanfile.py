from conans import CMake, ConanFile

class MultiDimContainerConan(ConanFile):
    name = 'multi-dim-container'
    version = '0.1'
    author = 'svanveen'

    default_user = 'svanveen'
    default_channel = 'stable'

    url = 'https://github.com/svanveen/multi-dim-container.git'
    description = 'C++ header only library for multi dimensional containers'

    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto",
    }

    generators = "cmake_paths"

    settings = "os", "compiler", "build_type", "arch"

    options = {
        "with_tests": [True, False]
    }
    default_options = {
        "with_tests": False
    }

    no_copy_sources = True

    def requirements(self):
        if self.options.with_tests:
            self.requires("gtest/[>=1.10.0]")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["WITH_TESTS"] = self.options.with_tests
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_id(self):
        if not self.options.with_tests:
            self.info.header_only()
