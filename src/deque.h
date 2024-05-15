/*
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <stdlib.h>
#include <string.h>

// Using any of the functions below with different than expected datatypes (see comments and documentation) will result in an undefined behaviour

// T* content -> Array of type T, containing elements of the deque.
// size_t elementSize -> Size in bytes of an element stored in content, equivilent to sizeof(T).
// size_t front -> Offset from the beginning of content to current first element in deque.
// size_t back -> Offset from the beginning of content to BEHIND last element in deque.
// size_t capacity -> Number of currently allocated elements (deque(T).content), once either front or back exceed scope of content, content must be reallocated
#ifndef deque
#define deque(T) \
    struct { \
        T* content; \
        size_t elementSize; \
        size_t front; \
        size_t back; \
        size_t capacity; \
    }

#endif // #ifndef deque

// Input: 
//      T -> Type of the variable to create the deque for
// Output:
//      deque(T) -> created deque
// Description:
//      Constructor of deque(T)
//      deque(int) mydeque = new_deque(int);
// Behaviour:
//      1) If malloc fails deque(T).content will be a NULL pointer
//      2) Front and back are offset directly in the middle of the allocated memory
//      3) By default capacity of a deque(T) is 32
#ifndef new_deque
#define new_deque(T) \
    { \
        malloc(sizeof(T)*32), \
        sizeof(T), \
        16, \
        16, \
        32, \
    }

#endif // #ifndef new_deque

// Input:
//      deque(T) deque
// Output:
//      void -> Function works in-place.
// Description:
//      Deallocates content of the deque and sets all values to 0.
//      free({2,0,9}) -> {}
// Behaviour:
//      1) deque.content is explicitly set to NULL, thus all unsaved data is irreversably lost.
#ifndef deque_free
#define deque_free(deque) \
    free(deque.content); \
    deque.content = NULL; \
    deque.elementSize = 0; \
    deque.front = 0; \
    deque.back = 0; \
    deque.capacity = 0;

#endif // #ifndef deque_free

// Input:
//      deque(T)
// Output:
//      bool (true if deque is empty, false otherwise)
//      deque_is_empty({71,2}) -> false
//      deque_is_empty({}) -> true
// Description: 
//      Checks whether there are any elements in deque
#ifndef deque_is_empty
#define deque_is_empty(deque) \
    deque.front == deque.back
    
#endif // #ifndef deque_is_empty

// Input:
//      deque(T)
// Output:
//      size_t -> size of the deque
// Description: 
//      Returns number of elements stored in the deque
#ifndef deque_size
#define deque_size(deque) \
    deque.back - deque.front 

#endif // #ifndef deque_size

// Input:
//      deque(T) deque
// Output:
//      T -> first element of the deque.
// Description: 
//      Returns first element of the deque.
//      deque_front({6,2,1}) -> 6
// Behaviour:
//      1) If the deque is empty, deque_front(deque(T)) will return whatever data is stored at deque(T).content[deque(T).front]
#ifndef deque_front
#define deque_front(deque) \
    deque.content[deque.front]

#endif // #ifndef deque_front

// Input:
//      deque(T) deque
// Output:
//      T -> Last element of the deque.
// Description: 
//      Returns last element of the deque.
//      deque_front({6,2,1}) -> 1
// Behaviour:
//      1) If the deque is empty, deque_back(deque(T)) will return whatever data is stored at deque(T).content[deque(T).back-1]
#ifndef deque_back
#define deque_back(deque) \
    deque.content[deque.back-1]

#endif // #ifndef deque_back

// Input:
//      deque(T) deque
//      size_T index
// Output:
//      T -> Element at index
// Description: 
//      Returns element located at given index
//      deque_at({6,2,1}, 1) -> 2
// Behaviour:
//      1) If index >= deque.size, deque_back(deque) is called
#ifndef deque_at
#define deque_at(deque, index) \
    index > deque_size(deque) ? deque_back(deque) : deque.content[deque.front+index]

#endif // #ifndef deque_at

// Input:
//      deque(T) deque
//      T element
// Output:
//      void -> function works in place
// Description: 
//      Pushes element to the front of the deque.
//      Reallocates deque(T).content, if it is needed to fit the new element.
//      deque_push_front({24,6,3}, 7) -> {7, 24, 6, 3}
// Behaviour:
//      1) If reallocation fails nothing is done
#ifndef deque_push_front
#define deque_push_front(deque, element) \
    do { \
        if(deque.front == 0) { \
            void* p = realloc(deque.content, deque.elementSize*deque.capacity*2); \
            if(p != NULL) { \
                deque.content = p; \
                memmove(deque.content+deque.capacity/2, deque.content, deque.elementSize*deque.capacity); \
                deque.front += deque.capacity/2; \
                deque.back += deque.capacity/2; \
                deque.capacity *= 2; \
            } \
        } \
        deque.content[--deque.front] = element; \
    } while(0)

#endif // #ifndef deque_push_front

// Input:
//      deque(T) deque
//      T element
// Output:
//      void -> function works in place
// Description: 
//      Pushes element to the back of the deque.
//      Reallocates deque(T).content, if it is needed to fit the new element.
//      deque_push_front({24,6,3}, 7) -> {24, 6, 3, 7}
// Behaviour:
//      1) If reallocation fails nothing is done
#ifndef deque_push_back
#define deque_push_back(deque, element) \
    do { \
        if(deque.back == deque.capacity) { \
            void* p = realloc(deque.content, deque.elementSize*deque.capacity*2); \
            if(p != NULL) { \
                deque.content = p; \
                memmove(deque.content+deque.capacity/2, deque.content, deque.elementSize*deque.capacity); \
                deque.front += deque.capacity/2; \
                deque.back += deque.capacity/2; \
                deque.capacity *= 2; \
            } \
        } \
        deque.content[deque.back++] = element; \
    } while(0)

#endif // #ifndef deque_push_back

// Input:
//      deque(T) deque
// Output:
//      T -> removed element
// Description: 
//      Removes element from the front of the deque.
//      deque_pop_front({13,2,8}) -> 13
// Behaviour:
//      1) If deque is empty, deque_pop_front(deque(T)) will return whatever data is stored at deque(T).content[deque.front] 
#ifndef deque_pop_front
#define deque_pop_front(deque) \
    deque_is_empty(deque) ? deque.content[deque.front] : deque.content[deque.front++]

#endif // #ifndef deque_pop_front

// Input:
//      deque(T) deque
// Output:
//      T -> removed element
// Description: 
//      Removes element from the back of the deque.
//      deque_pop_back({13,2,8}) -> 8
// Behaviour:
//      1) If deque is empty, deque_pop_back(deque(T)) will return whatever data is stored at deque(T).content[deque.back-1] 
#ifndef deque_pop_back
#define deque_pop_back(deque) \
    deque_is_empty(deque) ? deque.content[deque.back-1] : deque.content[--deque.back]

#endif // #ifndef deque_pop_back
