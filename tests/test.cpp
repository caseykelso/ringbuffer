/* Test Suite for ringbuffer */

#include <stdint.h>
#include <iomanip>
extern "C" {
#include <stdbool.h>
#include <stdlib.h>
#include "ringbuffer/ringbuffer.h"
}

#include "RingBufferTests.h"
#define BUFFER_SIZE   4096
#define RESULT_SIZE   512
#define INSERT_SIZE   256

uint8_t buffer_raw[BUFFER_SIZE];
uint8_t buffer_random[BUFFER_SIZE];
uint8_t buffer_copy[BUFFER_SIZE];
uint8_t buffer_result[RESULT_SIZE];
uint8_t buffer_insert[INSERT_SIZE];

ringbuffer_t buffer_meta;

static bool generate_document(uint8_t* const storage, const uint32_t length )
{
   bool result = false;

   srand(time(0));
   memset((void*)storage, 0, (size_t)length);

   if (0 != storage)
   {
      for (uint32_t i = 0; i < length; i++)
      {
         storage[i] = rand()%255;
      }
   }

   return result;
}


TEST_F(RingBufferTests, OVERFILL_AND_EMPTY)
{

    size_t available = 0;
    size_t size      = 0; 

    generate_document(buffer_random, BUFFER_SIZE);

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


    uint8_t data = 0xAB;

    /* fill the buffer with random data */
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
       /* test available */
       EXPECT_EQ(true, ringbuffer_available(&buffer_meta, &size));
       EXPECT_EQ(size, BUFFER_SIZE-i);

       /* test buffer size */
       EXPECT_EQ(true, ringbuffer_size(&buffer_meta, &size));
       EXPECT_EQ(size, i);

       /* test insert */
       EXPECT_EQ(true, ringbuffer_insert(&buffer_meta, buffer_random+i , 1, &size));
       EXPECT_EQ(1, size); 
    }

    /* attempt to stuff more data into the full buffer */
    EXPECT_EQ(false, ringbuffer_insert(&buffer_meta, &data , 1, &size));
    EXPECT_EQ(0, size); 


    /* empty the buffer into another buffer for comparison  */
    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
       /* test available */
       EXPECT_EQ(true, ringbuffer_available(&buffer_meta, &size));
       EXPECT_EQ(size, i);

       /* test buffer size */
       EXPECT_EQ(true, ringbuffer_size(&buffer_meta, &size));
       EXPECT_EQ(size, BUFFER_SIZE-i);
 
       /* test pop */
       EXPECT_EQ(true, ringbuffer_pop(&buffer_meta, buffer_copy+i , 1, &size));
       EXPECT_EQ(1, size); 
    }

    /* test pop on empty buffer */
    EXPECT_EQ(true, ringbuffer_pop(&buffer_meta, &data , 1, &size));
    EXPECT_EQ(0, size); 
 
    /* compare original random document to the copied document */
    EXPECT_EQ(0, memcmp(buffer_copy, buffer_random, BUFFER_SIZE)); 

    /* test available on empty buffer */
    EXPECT_EQ(true, ringbuffer_available(&buffer_meta, &size));
    EXPECT_EQ(size, BUFFER_SIZE);

    /* test buffer size on empty buffer */
    EXPECT_EQ(true, ringbuffer_size(&buffer_meta, &size));
    EXPECT_EQ(size, 0);
 

}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



