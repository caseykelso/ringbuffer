/******************************************************************************
 *
 *  Copyright (C) 2015 Google Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/
#include <assert.h>
#include <stdlib.h>

struct ringbuffer_t 
{
  size_t total;
  size_t available;
  uint8_t *base;
  uint8_t *head;
  uint8_t *tail;
};

ringbuffer_t* ringbuffer_init(const size_t size, uint8_t *preallocated_buffer) 
{
  ringbuffer_t* p = preallocated_buffer;
  p->head = p->tail = p->base;
  p->total = p->available = size;
  return p;
}


bool ringbuffer_available(const ringbuffer_t *rb, size_t *result) 
{

  bool status = false;

  if (0 != rb)
  {
    status = true;
    *result = rb->available;
  }

  return status;
}

bool ringbuffer_size(const ringbuffer_t *rb, size_t *result) 
{

  bool status = false;

  if (0 != rb && 0 != result)
  {
    status = true;
    *result = rb->total - rb->available;
  }

  return status;
}

bool ringbuffer_insert(ringbuffer_t *rb, const uint8_t *p, size_t length, size_t *result) 
{
  bool status = false;

  if (0 != p && 0 != rb && 0 != result)
  {

    if (length > ringbuffer_available(rb))
    {
      length = ringbuffer_available(rb);
    }

    for (size_t i = 0; i != length; ++i) 
    {
        *rb->tail++ = *p++;

        if (rb->tail >= (rb->base + rb->total))
        {
           rb->tail = rb->base;
        }
    }

    rb->available -= length;
    *result = length;
  }

  return status;
}

bool ringbuffer_delete(ringbuffer_t *rb, size_t length, size_t *result) 
{
    bool status = false;

    if (0 != rb && 0 ! result)
    {
       status = true;

       if (length > ringbuffer_size(rb))
       {
          length = ringbuffer_size(rb);
          rb->head += length;
       }

       if (rb->head >= (rb->base + rb->total))
       {
          rb->head -= rb->total;
          rb->available += length;
       }
  
       *result = length; 

    }

    return status;
}


bool ringbuffer_peek(const ringbuffer_t *rb, uint8_t *p, size_t length, size_t *result) 
{

    bool status = false;
    if (0 != result && 0 != rb && 0 != p)
    {
      uint8_t *b = rb->head;
      size_t copied = 0;

      while (copied < length && copied < ringbuffer_size(rb))
      {
        *p++ = *b++;

        if (b >= (rb->base + rb->total))
        {
           b = rb->base;
        }

        ++copied;
      }

      *result = copied;

    } 

    return status;
}

bool ringbuffer_pop(ringbuffer_t *rb, uint8_t *p, size_t length, size_t *result) 
{
  bool status = false;

  if (0 != status && 0 != rb && 0 != p)
  {
     const size_t copied = ringbuffer_peek(rb, p, length);
     rb->head += copied;

     if (rb->head >= (rb->base + rb->total))
     {
       rb->head -= rb->total;
     }

     rb->available += copied;
     *result = copied;

  }
  return status;
}


