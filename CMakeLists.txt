# CMakeLists.txt -- Build system for palimpsest
#
# Copyright 2022 Stéphane Caron
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.1)

project(palimpsest)
set(PROJECT_URL https://github.com/stephane-caron/palimpsest)
set(PROJECT_VERSION 1.1.0)

# CMake options
option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_MPACK "Build and install MPack from third_party/mpack" ON)

# C++17 or later
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dependencies
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(fmt)
if(BUILD_MPACK)
    add_subdirectory(third_party)
endif()

# Library
add_library(palimpsest SHARED
    src/Dictionary.cpp
    src/mpack/Writer.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include
    third_party/mpack/src/mpack
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Eigen3::Eigen
    fmt
    mpack
)

# Unit tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install shared library
install(TARGETS palimpsest
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Install headers
install(DIRECTORY include
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    FILES_MATCHING REGEX ".h$")
