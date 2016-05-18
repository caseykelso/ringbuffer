cmake_minimum_required (VERSION 2.8.10.2)
project(ringbuffer)

set(CMAKE_BUILD_TYPE Debug)
if(APPLE)
set(CMAKE_C_FLAGS_DEBUG "-O0 -g -std=c11")
set(CMAKE_C_FLAGS_RELEASE "-O3  -std=c11")
else(APPLE)
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb -g3 -std=c11")
set(CMAKE_C_FLAGS_RELEASE "-O3 -std=c11")
endif(APPLE)
set(RINGBUFFER_TEST_SOURCES test.cpp)
set(RINGBUFFER_TEST_HEADERS RingBufferTest.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${INCLUDE_DIR})

set(LIB_FIFO_SOURCES test.cpp)
set(PROJECT_SOURCE_FILES ${LIB_FIFO_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${GTEST_INCLUDE_DIR} ${INSTALL_INCLUDE_DIR})
link_directories(${GTEST_LIBRARY_DIR} ${INSTALL_LIBRARY_DIR})
add_executable(ringbuffer_test ${PROJECT_SOURCE_FILES})

if (APPLE)
target_link_libraries(ringbuffer_test ringbuffer gtest pthread )
else(APPLE)
target_link_libraries(ringbuffer_test ringbuffer gtest pthread rt)
endif(APPLE)

install(TARGETS ringbuffer_test DESTINATION bin)

