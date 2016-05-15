/* Test Suite for ringbuffer */

#include <stdint.h>
extern "C" {
#include <stdbool.h>
#include "ringbuffer.h"
}

#include "ringbuffer.h"


TEST_F(RingBufferTests, INIT)
{
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



