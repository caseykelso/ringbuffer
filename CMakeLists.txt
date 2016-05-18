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

set(LIB_RINGBUF_SOURCES ringbuffer.c)
set(LIB_RINGBUF_HEADERS ringbuffer.h) 
set(RINGBUFFER_TEST_SOURCES test.cpp ${LIB_RINGBUF_SOURCES})
set(RINGBUFFER_TEST_HEADERS RingBufferTest.h)

set(PROJECT_SOURCE_FILES ${LIB_RINGBUF_SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR} )
add_library(ringbuffer STATIC ${PROJECT_SOURCE_FILES} ${LIB_RINGBUF_HEADERS})

install(TARGETS ringbuffer DESTINATION lib)
install(FILES ${LIB_RINGBUF_HEADERS} DESTINATION include/ringbuffer)

