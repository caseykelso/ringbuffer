/* Test Suite for ringbuffer */

#include <stdint.h>
extern "C" {
#include <stdbool.h>
#include <stdlib.h>
#include "ringbuffer/ringbuffer.h"
}

//#include "ringbuffer/ringbuffer.h"
#include "RingBufferTests.h"
#define BUFFER_SIZE   4096
#define RESULT_SIZE   512

uint8_t buffer_raw[BUFFER_SIZE];
uint8_t buffer_result[RESULT_SIZE];

ringbuffer_t buffer_meta;

TEST_F(RingBufferTests, FILL_AND_EMPTY)
{

    size_t available = 0;
    size_t size      = 0; 

    EXPECT_EQ(false, ringbuffer_init(0, 0, 0));
    EXPECT_EQ(false, ringbuffer_init(0, BUFFER_SIZE, buffer_raw));
    EXPECT_EQ(false, ringbuffer_init(&buffer_meta, BUFFER_SIZE, 0));
    EXPECT_EQ(true,  ringbuffer_init(&buffer_meta, BUFFER_SIZE, buffer_raw));

    EXPECT_EQ(false, ringbuffer_available(0, &available));
    EXPECT_EQ(false, ringbuffer_available(&buffer_meta, 0));
  
    available = 0; 
    EXPECT_EQ(true,  ringbuffer_available(&buffer_meta, &available));
    EXPECT_EQ(BUFFER_SIZE, available);
 
    EXPECT_EQ(false, ringbuffer_size(0, &size));
    EXPECT_EQ(false, ringbuffer_size(&buffer_meta, 0));
 
    size = 0;
    EXPECT_EQ(true,  ringbuffer_size(&buffer_meta, &size));
    EXPECT_EQ(0, size);

    EXPECT_EQ(false, ringbuffer_delete(0, 0, 0));
    EXPECT_EQ(false, ringbuffer_delete(0, 0, &size));
    EXPECT_EQ(false, ringbuffer_delete(&buffer_meta, 0, 0));
    EXPECT_EQ(true,  ringbuffer_delete(&buffer_meta, 0, &size)); 
   
    memset(buffer_result, 0, RESULT_SIZE);
    EXPECT_EQ(false, ringbuffer_peek(0, 0, 0, 0));
    EXPECT_EQ(false, ringbuffer_peek(0, 0, 0, &size));
    EXPECT_EQ(false, ringbuffer_peek(0, buffer_result, RESULT_SIZE, &size));
    EXPECT_EQ(true,  ringbuffer_peek(&buffer_meta, buffer_result, RESULT_SIZE, &size));
    EXPECT_EQ(0, size);

    EXPECT_EQ(false, ringbuffer_pop(0, 0, 0, 0));
    EXPECT_EQ(false, ringbuffer_pop(0, 0, 0, &size));
    EXPECT_EQ(false, ringbuffer_pop(0, buffer_result, RESULT_SIZE, &size));
    EXPECT_EQ(true,  ringbuffer_pop(&buffer_meta, buffer_result, RESULT_SIZE, &size));
    EXPECT_EQ(0, size);


}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



