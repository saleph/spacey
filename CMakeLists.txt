#
# CI Hello World
#
# Copyright (C) 2017 Assured Information Security, Inc.
# Author: Rian Quinn        <quinnr@ainfosec.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 20)

# ------------------------------------------------------------------------------
# CI setup
# ------------------------------------------------------------------------------
include("cmake/CountinousIntegration.cmake")
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include)

# ------------------------------------------------------------------------------
# Hunter gate
# ------------------------------------------------------------------------------
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.190.tar.gz"
    SHA1 "bc7da329d2493201de28f0c2a5fcd4de1415c477"
    LOCAL
)

# ------------------------------------------------------------------------------
# Project
# ------------------------------------------------------------------------------
project(spacey C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# allow to use find_package for libraries built outside linking directory
# used in Hunter packages linking - all added packages are built from root
# directory, whereas all the usages are placed in subfolders like "common"
cmake_policy(SET CMP0079 NEW)
# clang-tidy does not like GTest, produces a lot of warnings, treated as errors
set(SKIP_TEST_BUILD ${ENABLE_CLANG_TIDY})

# ------------------------------------------------------------------------------
# Hunter libraries in use
# ------------------------------------------------------------------------------
hunter_add_package(GTest)
hunter_add_package(Microsoft.GSL)

# ------------------------------------------------------------------------------
# Project components
# ------------------------------------------------------------------------------
add_subdirectory(common)
add_subdirectory(neat)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(spacey main.cpp)
target_link_libraries(spacey common)
target_link_libraries(spacey neat)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
include(CTest)

add_test(common_test common/common_test)
add_test(neat_test neat/neat_test)