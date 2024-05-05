#pragma once

#include <stdlib.h>
#include <string.h>

// Using any of the functions below with different than expected datatypes (see comments and documentation) will result in an undefined behaviour

// T* -> array of type T, containing elements of the array
// size_t elementSize -> size in bytes of an element stored in content, equivilent to sizeof(T) 
// size_t size -> amount of elements stored in vector (content), index of last element is content[size-1]
// size_t capacity -> currently allocated number of elements in (content), once size becomes greater than capacity vector must be resized
#define vec(T) \
    struct { \
        T* content; \
        size_t   elementSize; \
        size_t   size; \
        size_t  capacity; \
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
//      size_t newSize -> new capacity of vector, amount of elements (not bytes!)
// Description:
//      Changes capacity of the vector to a desired value.
//      {1,4,-2}.capacity = 32, vec_resize({1,4,-2}, 100) -> {1,4,-2}.capacity = 100
// Behaviour:
//      1) If realloc fails nothing is done
//      2) If the new capacity is smaller than vector's size, excessive elements will be lost and vector's size will be set to vector's capacity
#define vec_resize(vec, newSize) \
    do { \
        void* p = realloc(vec.content, newSize*vec.elementSize); \
        if(p != NULL) { \
            vec.content = p; \
            if(vec.capacity <= newSize) vec.size = vec.capacity; \
            else vec.size = newSize; \
        } \
    } while(0) 

// Input:
//      vec -> vec(T)
// Description:
//      Deallocates content of the vector and sets all values to 0
//      free({2,0,9}) -> {}
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
//      T element -> element to be pushed to the vector
// Description: 
//      Incremenet's vector's size by 1 and appends provided element. Reallocates and increases capacity if needed.
//      vec_push({13,9,5}, 3) -> {13,9,5,3} 
// Behaviour:
//      1) If reallocation is needed to fit the element and realloc fails nothing is done
#define vec_push(vec, element) \
    do { \
        size_t lastCapacity = 0; \
        while(vec.size >= vec.capacity && lastCapacity != vec.capacity) { \
            lastCapacity = vec.capacity; \
            vec_resize(vec, vec.capacity*2); \
        } \
        if(lastCapacity == 0 || lastCapacity < vec.capacity) vec.content[vec.size++] = element; \
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


// Input:
//      vec -> vec(T)
//      T element -> element to be pushed to the vector
//      size_t index -> index the element is to be inserted at
// Description: 
//      Incremenet's vector's size by 1 and inserts given elementa at the given index, shifting all bigger indexes one to the right
//      vec_insert({2,6,-24,1}, -9, 1) -> {2,-9,6,-24,1}
// Behaviour:
//      1) If index is out of bounds, nothing is done
#define vec_insert(vec, element, index) \
    do { \
        if(index <= vec.size) { \
            size_t lastCapacity = 0; \
            while(vec.size >= vec.capacity && lastCapacity != vec.capacity) { \
                lastCapacity = vec.capacity; \
                vec_resize(vec, vec.capacity*2); \
            } \
            if(lastCapacity == 0 || lastCapacity < vec.capacity) { \
                memcpy(&vec.content[index+1], &vec.content[index], (vec.size-index)*vec.elementSize); \
                vec.content[index] = element; \
                vec.size++; \
            } \
        } \
    } while(0)

// Input:
//      vec -> vec(T)
//      T index -> index of the element that is to be removed
// Description:
//      Removes element at the given index. Shifts all elements after the index by one to the left ([i]th index becomes [i-1]th index).
//      vec_remove({1,2,12,6,-4}, 2) -> {1,2,6,-4}
// Behaviour:
//      1) If index is out of bounds, nothing is done
#define vec_remove(vec, index) \
    if(index < vec.size) { \
        memcpy(&vec.content[index], &vec.content[index+1], (vec.size-index-1)*vec.elementSize); \
        vec.size--; \
    }
