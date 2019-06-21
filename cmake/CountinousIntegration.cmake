set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(ExternalProject)
find_package(Git REQUIRED)

# ------------------------------------------------------------------------------
# Astyle
# ------------------------------------------------------------------------------
if(ENABLE_ASTYLE)
    list(APPEND ASTYLE_CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
    )
    ExternalProject_Add(
        astyle
        GIT_REPOSITORY      https://github.com/Bareflank/astyle.git
        GIT_TAG             v1.2
        GIT_SHALLOW         1
        CMAKE_ARGS          ${ASTYLE_CMAKE_ARGS}
        PREFIX              ${CMAKE_BINARY_DIR}/external/astyle/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/external/astyle/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/external/astyle/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/astyle/download
        SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/astyle/src
        BINARY_DIR          ${CMAKE_BINARY_DIR}/external/astyle/build
    )
    list(APPEND ASTYLE_ARGS
        --style=1tbs
        --lineend=linux
        --suffix=none
        --pad-oper
        --unpad-paren
        --break-closing-brackets
        --align-pointer=name
        --align-reference=name
        --indent-preproc-define
        --indent-switches
        --indent-col1-comments
        --keep-one-line-statements
        --keep-one-line-blocks
        --pad-header
        --convert-tabs
        --min-conditional-indent=0
        --indent=spaces=4
        --close-templates
        --add-brackets
        --break-after-logical
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/test/*.cpp
    )
    if(NOT WIN32 STREQUAL "1")
        add_custom_target(
            format
            COMMAND ${CMAKE_BINARY_DIR}/bin/astyle ${ASTYLE_ARGS}
            COMMENT "running astyle"
        )
    else()
        add_custom_target(
            format
            COMMAND ${CMAKE_BINARY_DIR}/bin/astyle.exe ${ASTYLE_ARGS}
            COMMENT "running astyle"
        )
    endif()
endif()

# ------------------------------------------------------------------------------
# Clang Tidy
# ------------------------------------------------------------------------------
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_BIN clang-tidy-8)
    find_program(RUN_CLANG_TIDY_BIN run-clang-tidy-8.py)
    message("egaltom: clang tidy")
    message(${CLANG_TIDY_BIN})
    message("egaltom: run clang tidy py")
    message(${RUN_CLANG_TIDY_BIN})
    if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate clang-tidy-8")
    endif()
    if(RUN_CLANG_TIDY_BIN STREQUAL "RUN_CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate run-clang-tidy-8.py")
    endif()
    list(APPEND RUN_CLANG_TIDY_BIN_ARGS
        -clang-tidy-binary ${CLANG_TIDY_BIN}
        -header-filter=.*
        -checks=clan*,cert*,misc*,perf*,cppc*,read*,mode*,-cert-err58-cpp,-misc-noexcept-move-constructor
    )
    message(${RUN_CLANG_TIDY_BIN_ARGS})
    add_custom_target(
        tidy PROPERTIES
        CXX_CLANG_TIDY "${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}"
        COMMENT "running clang tidy"
    )
endif()

# ------------------------------------------------------------------------------
# CppCheck
# ------------------------------------------------------------------------------
if(ENABLE_CPPCHECK)
    list(APPEND CPPCHECK_CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
    )
    ExternalProject_Add(
        cppcheck
        GIT_REPOSITORY      https://github.com/danmar/cppcheck.git
        GIT_TAG             1.87
        GIT_SHALLOW         1
        CMAKE_ARGS          ${CPPCHECK_CMAKE_ARGS}
        PREFIX              ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/cppcheck/download
        SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/src
        BINARY_DIR          ${CMAKE_BINARY_DIR}/external/cppcheck/build
    )
    list(APPEND CPPCHECK_ARGS
        --enable=warning,style,performance,portability,unusedFunction
        --std=c++11
        --verbose
        --error-exitcode=1
        --language=c++
        -DMAIN=main
        -I ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/*.h
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/test/*.cpp
    )
    add_custom_target(
        check
        COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS}
        COMMENT "running cppcheck"
    )
endif()

# ------------------------------------------------------------------------------
# Coverage
# ------------------------------------------------------------------------------
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# ------------------------------------------------------------------------------
# Google Sanitizers
# ------------------------------------------------------------------------------
if(ENABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif()

if(ENABLE_USAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

if(ENABLE_TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
endif()

# ------------------------------------------------------------------------------
# Valgrind
# ------------------------------------------------------------------------------
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --track-fds=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --trace-children=yes")
set(MEMORYCHECK_COMMAND_OPTIONS "${MEMORYCHECK_COMMAND_OPTIONS} --error-exitcode=1")