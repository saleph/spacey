if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 9.0)
    # workaround for GTest compilation under g++-9
    # multiple warnings introduced in rev. 9 causes build to fail (because of -Werror)
    set(GTEST_CMAKE_CSS_FLAGS "-w")
    hunter_config(GTest VERSION ${HUNTER_GTest_VERSION} CMAKE_ARGS CMAKE_CXX_FLAGS=${GTEST_CMAKE_CSS_FLAGS})
endif()
