project(libsimple)
cmake_minimum_required(VERSION 2.8)

if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
	add_definitions(-DLINUX=1)
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	add_definitions(-DARCH64=1)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	add_definitions(-DARCH32=1)
endif()

FILE(GLOB LIBS_SOURCE_FILES ./src/*.c)
FILE(GLOB TESTS_SOURCE_FILES ./tests/*.c)

add_library("simple" SHARED ${LIBS_SOURCE_FILES})
target_include_directories("simple" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

# Tests
add_executable("simple_tests" ${TESTS_SOURCE_FILES})
add_dependencies("simple_tests" "simple")
target_include_directories("simple_tests" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/tests/")
target_link_libraries("simple_tests" "simple")
