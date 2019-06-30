include("../cmake/Utilities.cmake")

find_package(GTest CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

# main target
add_library(neat)
target_sources(neat
    PRIVATE
        "src/null.cpp"
    PUBLIC
        "include/consumer.hpp"
        "include/producer.hpp"
)
target_link_libraries(neat PUBLIC Microsoft.GSL::GSL)
target_compile_definitions(neat PUBLIC NEAT)
target_include_directories(neat PUBLIC ${PROJECT_SOURCE_DIR})

# test
if (NOT SKIP_TEST_BUILD)
    add_library(neat_test_lib)
    target_sources(neat_test_lib
        PRIVATE
            "test/test_producer.cpp"
    )
    target_link_libraries_system(neat_test_lib GTest::main)
    target_link_libraries(neat_test_lib neat)
    target_link_libraries(neat_test_lib Microsoft.GSL::GSL)

    target_compile_definitions(neat_test_lib PUBLIC NEAT_TEST_LIB)
    target_include_directories(neat_test_lib PUBLIC ${PROJECT_SOURCE_DIR})
    add_executable(neat_test "test/main.cpp")
    target_link_libraries(neat_test neat_test_lib)
endif()
