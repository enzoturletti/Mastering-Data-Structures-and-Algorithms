from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout

class MasteringDataStructuresAndAlgorithms(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def layout(self):
        cmake_layout(self)
        self.folders.build = "_build"  
        self.folders.generators = "_build/generators" 

    def requirements(self):
        self.requires("gtest/1.15.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.31.0")
