#pragma once

#include <stdlib.h>
#include <string.h>

#define vec(T) \
    struct { \
        T* content; \
        size_t   elementSize; \
        int   size; \
        int   capacity; \
    }

// Input: 
//      T -> Type of the variable to create input from
// Description:
//      Constructor of vec(T)
//      vec(int) myVector = new_vec(int);
// Behaviour:
//      1) If malloc fails vec(T).content will be a NULL pointer
//      2) By default capacity of a vec(T) is 32
#define new_vec(T) \
    { \
        malloc(sizeof(T)*32), \
        sizeof(T), \
        0, \
        32, \
    }

// Input:
//      vec -> vec(T)
//      newSize -> new capacity of vector, amount of elements (not bytes!)
// Description:
//      Changes capacity of the vector to a desired value.
// Behaviour:
//      1) If newSize overflows or is less than zero nothing is done
//      2) If realloc fails nothing is done
//      3) If the new capacity is smaller than vector's size, excessive elements will be lost and vector's size will be set to vector's capacity
#define vec_resize(vec, newSize) \
    do { \
        void* p = realloc(vec.content, newSize*vec.elementSize); \
        if(newSize <= (size_t)-1 && newSize >= 0 && p != NULL) { \
            vec.content = p; \
            vec.capacity = newSize; \
            if(vec.capacity < vec.size) vec.size = vec.capacity; \
        } \
    } while(0)

#define resize_check(vec, newSize, lastCapacity) \
    while(vec.size >= vec.capacity) { \
        *lastCapacity = vec.capacity; \
        vec_resize(vec, vec.capacity*2); \
    }

// Input:
//      vec -> vec(T)
// Description:
//      Deallocates content of the vector and sets all values to 0
// Behaviour:
//      1) vec.content is explicitly set to NULL, thus all unsaved data is irreversably lost.
#define vec_free(vec) \
    free(vec.content); \
    vec.content = NULL; \
    vec.elementSize = 0; \
    vec.size = 0; \
    vec.capacity = 0;

// Input:
//      vec -> vec(T)
//      element -> element to be pushed to the vector
// Description: 
//      Incremenet's vector's size by 1 and appends provided element. Reallocates and increases capacity if needed.
// Behaviour:
//      1) If reallocation is needed to fit the element and realloc fails nothing is done
#define vec_push(vec, element) \
    do { \
        int lastCapacity = -1; \
        resize_check(vec, newSize, &lastCapacity); \
        if(lastCapacity <= vec.capacity) vec.content[vec.size++] = element; \
    } while(0)

// Input:
//      vec -> vec(T)
// Description:
//      Removes the last element of the vector
//      vec_pop({4,-1,25,31}) -> {4,-1,25}
// Behaviour:
//      1) If the vector has size of 0 nothing is done
//      2) The last element is untouched, just vec.size is reduced, thus the element still can be technically reached
#define vec_pop(vec) \
    if(vec.size) vec.size--;

#define vec_insert(vec, element, index) \
    do { \
        if(index > 0 ) { \
            int lastCapacity = -1; \
            resize_check(vec, newSize, &lastCapacity); \
            if(lastCapacity <= vec.capacity) { \
                memcpy(&vec.content[index+1], &vec.content[index], (vec.size-index)*vec.elementSize); \
                vec.content[index] = element; \
                vec.size++; \
            } \
        } \
    } while(0)

// Input:
//      vec -> vec(T)
//      index -> index of the element that is to be removed
// Description:
//      Removes element at the given index. Shifts all elements after the index by one to the left ([i]th index becomes [i-1]th index).
//      vec_remove({1,2,12,6,-4}, 2) -> {1,2,6,-4}
// Behaviour:
//      1) If index is out of bounds (bigger than vector's size or smaller than one), nothing is done
#define vec_remove(vec, index) \
    if(index < vec.size && index > 0) { \
        memcpy(&vec.content[index], &vec.content[index+1], (vec.size-index-1)*vec.elementSize); \
        vec.size--; \
    } 
