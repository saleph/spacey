include("../cmake/Utilities.cmake")

find_package(Microsoft.GSL CONFIG REQUIRED)
find_package(Fruit CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED)

# main target
add_library(neat src/Neuron.cpp src/Neuron.hpp)
target_sources(neat
    PRIVATE
        "src/Neuron.cpp"
    PUBLIC
        "src/Response.hpp"
        "src/Neuron.hpp"
)
target_link_libraries(neat Microsoft.GSL::GSL)
target_link_libraries_system(neat Fruit::fruit)
target_link_libraries_system(neat Boost::boost)
target_compile_definitions(neat PUBLIC NEAT)
target_include_directories(neat PUBLIC ${PROJECT_SOURCE_DIR})

# test
if (NOT SKIP_TEST_BUILD)
    add_library(neat_test_lib)
    target_sources(neat_test_lib
        PUBLIC
            "test/NodeTest.cpp"
    )
    target_link_libraries_system(neat_test_lib GMock::main)
    target_link_libraries(neat_test_lib Microsoft.GSL::GSL)
    target_link_libraries(neat_test_lib neat)

    target_compile_definitions(neat_test_lib PUBLIC NEAT_TEST_LIB)
    target_include_directories(neat_test_lib PUBLIC ${PROJECT_SOURCE_DIR})
    add_executable(neat_test "test/main.cpp")
    target_link_libraries(neat_test neat_test_lib)
endif()
