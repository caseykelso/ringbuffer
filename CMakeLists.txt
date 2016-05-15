cmake_minimum_required (VERSION 2.8.10.2)
project(ringbuffer)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-O0")
set(CMAKE_C_FLAGS_RELEASE "-Os")


set(LIB_RINGBUF_SOURCES ringbuffer.c)
set(LIB_RINGBUF_HEADERS ringbuffer.h) 
set(RINGBUFFER_TEST_SOURCES test.cpp ${LIB_RINGBUF_SOURCES})
set(RINGBUFFER_TEST_HEADERS RingBufferTest.h)

set(PROJECT_SOURCE_FILES ${LIB_RINGBUF_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
add_library(ringbuffer STATIC ${PROJECT_SOURCE_FILES} ${LIB_RINGBUF_HEADERS})

install(TARGETS ringbuffer DESTINATION lib)
install(FILES ${LIB_RINGBUF_HEADERS} DESTINATION include/ringbuffer)

if (defined RINGBUFFER_TEST)
set(LIB_FIFO_SOURCES test.cpp fifo_bitbang.c)
set(PROJECT_SOURCE_FILES ${LIB_FIFO_SOURCES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${GTEST_INCLUDE_DIR} ${INSTALL_INCLUDE_DIR})
link_directories(${GTEST_LIBRARY_DIR} ${INSTALL_LIBRARY_DIR})
add_executable(ringbuffer_test ${PROJECT_SOURCE_FILES} ${LIB_CANINJA_HEADERS})

if (APPLE)
target_link_libraries(ringbuffer_test ringbuffer gtest pthread )
else(APPLE)
target_link_libraries(ringbuffer_test ringbuffer gtest pthread rt)
endif(APPLE)

endif(defined RINGBUFFER_TEST)
