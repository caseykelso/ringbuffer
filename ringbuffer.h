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
#pragma once


typedef struct
{
  size_t total;
  size_t available;
  uint8_t *base;
  uint8_t *head;
  uint8_t *tail;
} ringbuffer_t;

//typedef struct ringbuffer_t ringbuffer_t;
// NOTE:
// None of the functions below are thread safe when it comes to accessing the
// *rb pointer. It is *NOT* possible to insert and pop/delete at the same time.
// Callers must protect the *rb pointer separately.
// Create a ringbuffer with the specified size
bool ringbuffer_init(ringbuffer_t *rb, const size_t size, uint8_t *preallocated_buffer);
// Frees the ringbuffer structure and buffer
// Save to call with NULL.

//void ringbuffer_free(ringbuffer_t *rb);

// Returns remaining buffer size
bool ringbuffer_available(const ringbuffer_t *rb, size_t *result);

// Returns size of data in buffer
bool ringbuffer_size(const ringbuffer_t *rb, size_t *result); 

// Attempts to insert up to |length| bytes of data at |p| into the buffer
// Return actual number of bytes added. Can be less than |length| if buffer
// is full.
bool ringbuffer_insert(ringbuffer_t *rb, const uint8_t *p, size_t length, size_t *result);


// Peek |length| number of bytes from the ringbuffer into the buffer |p|
// Return the actual number of bytes peeked. Can be less than |length| if
// there is less than |length| data available.
bool ringbuffer_peek(const ringbuffer_t *rb, uint8_t *p, size_t length, size_t *result); 


// Does the same as |ringbuffer_peek|, but also advances the ring buffer head
bool ringbuffer_pop(ringbuffer_t *rb, uint8_t *p, size_t length, size_t *result); 

// Deletes |length| bytes from the ringbuffer starting from the head
// Return actual number of bytes deleted.
bool ringbuffer_delete(ringbuffer_t *rb, size_t length, size_t *result); 
