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

// Using any of the functions below with different than expected datatypes (see comments and documentation) will result in an undefined behaviour.

// T* at -> Array of type T, containing elements of the array.
// size_t elementSize -> Size in bytes of an element stored in at, equivilent to sizeof(T).
// size_t size -> Amount of elements stored in vector (at), index of last element is at[size-1].
// size_t capacity -> Number of currently allocated elements (vec(t).at), once exceeded vec(T).at must be reallocated to greater size.
#ifndef vec
#define vec(T) \
    struct { \
        T* at; \
        size_t elementSize; \
        size_t size; \
        size_t capacity; \
    }

#endif // #ifndef vec

// Input: 
//      T -> Type of the variable to create the vector for.
// Output:
//      vec(T) -> The created vector.
// Description:
//      Constructor of vec(T).
//      vec(int) myVector = new_vec(int);
// Behaviour:
//      1) If malloc fails vec(T).at will be a NULL pointer.
//      2) By default capacity of a vec(T) is 32.
#ifndef new_vec
#define new_vec(T) \
    { \
        malloc(sizeof(T)*32), \
        sizeof(T), \
        0, \
        32, \
    }

#endif // #ifndef new_vec

// Input:
//      vec(T) vec
// Output:
//      void -> Function works in-place.
// Description:
//      Deallocates at of the vector and sets all values to 0.
//      free({2,0,9}) -> {}
// Behaviour:
//      1) vec.at is explicitly set to NULL, thus all unsaved data is irreversably lost.
#ifndef vec_free
#define vec_free(vec) \
    free(vec.at); \
    vec.at = NULL; \
    vec.elementSize = 0; \
    vec.size = 0; \
    vec.capacity = 0;

#endif // #ifndef vec_free

// Input:
//      vec(T) vec
//      size_t newSize -> New capacity of vector, amount of elements (not bytes!).
// Output:
//      void -> Function works in-place.
// Description:
//      Changes capacity of the vector to a desired value.
//      {1,4,-2}.capacity = 32, vec_resize({1,4,-2}, 100) -> {1,4,-2}.capacity = 100
// Behaviour:
//      1) If realloc fails nothing is done.
//      2) If the new capacity is smaller than vector's size, excessive elements will be lost and vector's size will be set to vector's capacity.
#ifndef vec_resize
#define vec_resize(vec, newSize) \
    do { \
        void* p = realloc(vec.at, newSize*vec.elementSize); \
        if (p != NULL) { \
            vec.capacity = newSize; \
            vec.at = p; \
            if(vec.capacity <= vec.size) vec.size = vec.capacity; \
        } \
    } while(0) 

#endif // #ifndef vec_resize

// Input:
//      vec(T) vec
//      T element -> Element to be pushed to the vector.
// Output:
//      void -> Function works in-place.
// Description: 
//      Increments vector's size by 1 and appends provided element. Reallocates and increases capacity if needed.
//      Uses memcpy to avoid type assertion for nested vectors.
//      vec_push({13,9,5}, 3) -> {13,9,5,3} 
// Behaviour:
//      1) If reallocation is needed to fit the element and realloc fails nothing is done.
#ifndef vec_push
#define vec_push(vec, element) \
    do { \
        typeof(element) e = element; \
        size_t lastCapacity = 0; \
        if (vec.size >= vec.capacity) { \
            lastCapacity = vec.capacity; \
            vec_resize(vec, vec.capacity*2); \
        } \
        if (lastCapacity == 0 || lastCapacity < vec.capacity) \
          memcpy(&vec.at[vec.size++], &e, vec.elementSize); \
    } while(0)
#endif // #ifndef vec_push

// Input:
//      vec(T) vec
// Output:
//      T -> the removed element
// Description:
//      Removes the last element of the vector and returns it.
//      vec_pop({4,-1,25,31}) -> 31
// Behaviour:
//      1) If the vector has size of 0, vec.at[0] is returned.
#ifndef vec_pop
#define vec_pop(vec) \
    vec.at[vec.size ? --vec.size : 0]

#endif // #ifndef vec_pop

// Input:
//      vec(T) vec
//      T element -> Element to be pushed to the vector.
//      size_t index -> Index the element is to be inserted at.
// Output:
//      void -> Function works in-place.
// Description: 
//      Increments vector's size by 1 and inserts given elementa at the given index, shifting all bigger indexes one to the right.
//      Uses memcpy for asigning element at index to avoid type assertion for nested vectors.
//      vec_insert({2,6,-24,1}, -9, 1) -> {2,-9,6,-24,1}
// Behaviour:
//      1) If index is out of bounds, works as vec_push
#ifndef vec_insert
#define vec_insert(vec, element, index) \
    do { \
        if (index >= vec.size) vec_push(vec, element); \
        else { \
            typeof(element) e = element; \
            size_t lastCapacity = 0; \
            if (vec.size >= vec.capacity) { \
                lastCapacity = vec.capacity; \
                vec_resize(vec, vec.capacity*2); \
            } \
            if (lastCapacity == 0 || lastCapacity < vec.capacity) { \
                memcpy(&vec.at[index+1], &vec.at[index], (vec.size-index)*vec.elementSize); \
                memcpy(&vec.at[index], &e, vec.elementSize); \
                vec.size++; \
            } \
        } \
    } while(0)

#endif // #ifndef vec_insert

// Input:
//      vec(T) vec
//      T index -> Index of the element that is to be removed.
// Output:
//      void -> Function works in-place.
// Description:
//      Removes element at the given index. Shifts all elements after the index by one to the left ([i]th index becomes [i-1]th index).
//      vec_remove({1,2,12,6,-4}, 2) -> {1,2,6,-4}
// Behaviour:
//      1) If index is out of bounds, nothing is done.
#ifndef vec_remove
#define vec_remove(vec, index) \
    if (index < vec.size) { \
        memcpy(&vec.at[index], &vec.at[index+1], (vec.size-index-1)*vec.elementSize); \
        vec.size--; \
    }

#endif // #ifndef vec_remove
