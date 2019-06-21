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

cmake_minimum_required(VERSION 3.12.4)
set(CMAKE_CXX_STANDARD 20)

# ------------------------------------------------------------------------------
# CI setup
# ------------------------------------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include("cmake/CountinousIntegration.cmake")

# ------------------------------------------------------------------------------
# Hunter gate
# ------------------------------------------------------------------------------
include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.190.tar.gz"
    SHA1 "bc7da329d2493201de28f0c2a5fcd4de1415c477"
)

# ------------------------------------------------------------------------------
# Project
# ------------------------------------------------------------------------------
project(spacey C CXX)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------
include_directories(include)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include)

# ------------------------------------------------------------------------------
# GTest
# ------------------------------------------------------------------------------
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

# ------------------------------------------------------------------------------
# GSL
# ------------------------------------------------------------------------------
hunter_add_package(Microsoft.GSL)
find_package(Microsoft.GSL CONFIG REQUIRED)

# ------------------------------------------------------------------------------
# Main Executable
# ------------------------------------------------------------------------------
add_executable(spacey src/main.cpp)
target_link_libraries(spacey Microsoft.GSL::GSL)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

include("cmake/Utilities.cmake")
include(CTest)

add_library(business_logic STATIC src/main.cpp)
target_link_libraries(business_logic PUBLIC Microsoft.GSL::GSL)
add_dependencies(business_logic Microsoft.GSL::GSL)

macro(do_test str)
    add_executable(test_${str} test/test_${str}.cpp)
    add_test(test_${str} test_${str})
    target_link_libraries_system(test_${str} GTest::main)
    target_link_libraries(test_${str} business_logic)
    add_dependencies(test_${str} Microsoft.GSL::GSL)
endmacro(do_test)

do_test(producer)
