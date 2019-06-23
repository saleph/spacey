include("../cmake/Utilities.cmake")

find_package(GTest CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

# main target
add_library(common)
target_sources(common
    PRIVATE
        src/null.cpp
    PUBLIC
        include/null.hpp
)
target_link_libraries(common PUBLIC Microsoft.GSL::GSL)
target_compile_definitions(common PUBLIC COMMON)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

# test
if (NOT ENABLE_CLANG_TIDY)
    add_library(common_test_lib)
    target_sources(common_test_lib
        PRIVATE
            test/null_test.cpp
    )
    target_link_libraries_system(common_test_lib GTest::main)
    target_link_libraries(common_test_lib Microsoft.GSL::GSL)
    target_link_libraries(common_test_lib common)

    target_compile_definitions(common_test_lib PUBLIC COMMON_TEST_LIB)
    target_include_directories(common_test_lib PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
    add_executable(common_test test/null.cpp)
    target_link_libraries(common_test common_test_lib)
endif()
