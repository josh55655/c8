set(GTEST_VERSION release-1.11.0)
set(GTEST_DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib/gtest-src)
set(GTEST_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib/gtest)

if (WIN32)
    set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
    set(CMAKE_USE_PTHREADS_INIT OFF)
    set(CMAKE_THREAD_LIBS_INIT OFF)
    add_definitions(-DGTEST_OS_WINDOWS_MINGW)
endif (WIN32)

set(BUILD_SHARED_LIBS no)

# Sorgenti dei test per il framework
set(TEST_SRC
        src/main.cpp                  # entry point
        src/test_gtest.cpp            # test for gtest framework is working
        src/test_state.cpp
        src/test_opcodes.cpp)

enable_testing()

# Download and unpack googletest at configure time
configure_file(lib/CMakeLists.txt.in lib/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines the gtest and gtest_main targets.
add_subdirectory(${GTEST_DOWNLOAD_DIR} ${GTEST_BUILD_DIR} EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories(
            "${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif ()

include_directories(
        src
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR})

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(chip8_test
        ${TEST_SRC})

target_link_libraries(chip8_test
        c8support
        c8opcodes
        gtest gmock)

add_test(NAME chip8_test COMMAND chip8_test)
