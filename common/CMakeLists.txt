include("../cmake/Utilities.cmake")

find_package(GMock CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

# main target
add_library(common)
target_sources(common
    PRIVATE
        "src/null.cpp"
    PUBLIC
        "include/FloatingPointUtils.hpp"
)
target_link_libraries(common PUBLIC Microsoft.GSL::GSL)
target_compile_definitions(common PUBLIC COMMON)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR})

# test
if (NOT SKIP_TEST_BUILD)
    add_library(common_test_lib)
    target_sources(common_test_lib
        PRIVATE
            "test/null_test.cpp"
    )
    target_link_libraries_system(common_test_lib GMock::main)
    target_link_libraries(common_test_lib Microsoft.GSL::GSL)
    target_link_libraries(common_test_lib common)

    target_compile_definitions(common_test_lib PUBLIC COMMON_TEST_LIB)
    target_include_directories(common_test_lib PUBLIC ${PROJECT_SOURCE_DIR})
    add_executable(common_test "test/main.cpp")
    target_link_libraries(common_test common_test_lib)
endif()
