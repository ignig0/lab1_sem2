cmake_minimum_required(VERSION 3.14)
project(MatrixOperations)


set(CMAKE_C_COMPILER "E:/CodeBlocks/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "E:/CodeBlocks/MinGW/bin/g++.exe")
set(CMAKE_MAKE_PROGRAM "E:/CodeBlocks/MinGW/bin/mingw32-make.exe")


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)



if(NOT EXISTS ${CMAKE_SOURCE_DIR}/googletest/CMakeLists.txt)
    message(STATUS "Downloading Google Test...")
    find_package(Git REQUIRED)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone https://github.com/google/googletest.git
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE result
    )
    if(NOT result EQUAL "0")
        message(FATAL_ERROR "Failed to download Google Test")
    endif()
endif()


add_subdirectory(googletest)

set(SOURCES
    check_for_errors.c
    complex.c
    controller.c
    integer.c
    matrix.c
)


add_executable(matrix_operations 
    main.c
    ${SOURCES}
)

add_executable(tests
    googletests.cpp
    ${SOURCES}
)

target_include_directories(matrix_operations PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/googletest/googletest/include
)

target_link_libraries(tests PRIVATE gtest_main gmock_main)

enable_testing()
add_test(NAME MatrixTests COMMAND tests)