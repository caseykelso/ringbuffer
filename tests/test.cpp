/* Test Suite for ringbuffer */

#include <stdint.h>
extern "C" {
#include <stdbool.h>
#include <stdlib.h>
#include "ringbuffer/ringbuffer.h"
}

//#include "ringbuffer/ringbuffer.h"
#include "RingBufferTests.h"

TEST_F(RingBufferTests, INIT)
{
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



