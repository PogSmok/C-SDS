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

#ifndef v_stdlib
#define v_stdlib
#include <stdlib.h> // malloc() free()
#endif // #ifndef v_stdlib

#ifndef v_string
#define v_string
#include <string.h> // memcpy() memmove()
#endif // #ifndef v_string

/**
 * @brief Helper struct for storing information about the vector, it is stored at vector[-1]
 * @private
 */
#define Vector_meta_data struct { size_t size; size_t capacity; }
#define VECTOR_META_SIZE sizeof(Vector_meta_data)

/**
 * @brief Standardization of the syntax for definition of a vector
 * @param {Type} T
 */
#define vector(T) T*

/**
 * @brief Returns memory adress of vector's meta data
 * @private
 */
#define v_meta(vector) \
    ((Vector_meta_data*)(vector-VECTOR_META_SIZE))

/**
 * @brief Returns number of bytes vector allocates, including meta data
 * @param {vector} vector
 * @return {size_t}
 * @private
 */
#define v_raw_byte_size(vector) \
    (v_capacity(vector)*sizeof(*vector)+VECTOR_META_SIZE)

/**
 * @brief Destructs a vector
 * @param {vector} vector
 */
#define v_free(vector) \
    free(v_meta(vector))

/**
 * @brief Returns the number of elements in the vector.
 * @param {vector} vector
 * @return size_t
 */
#define v_size(vector) \
    (vector ? v_meta(vector)->size : 0)

/**
 * @brief Helper function for exponential growth
 * @param {vector}
 */
#define DEFAULT_VECTOR_CAPACITY 32
#define v_grow(vector)                                                                                         \
    do {                                                                                                       \
        void* p = NULL;                                                                                        \
        if(v_capacity(vector)) { p = realloc(vector-VECTOR_META_SIZE, v_meta(vector)->capacity*(*vector)*2); } \
        else { p = malloc(DEFAULT_VECTOR_CAPACITY*sizeof(*vector)+VECTOR_META_SIZE); }                         \
        if(p != NULL) {                                                                                        \
            vector = p+VECTOR_META_SIZE;                                                                       \
            size_t capacity = v_meta(vector)->capacity;                                                        \
            v_meta(vector)->capacity = capacity ? capacity<<1 : DEFAULT_VECTOR_CAPACITY;                       \
        }                                                                                                      \
    }  while(0)

/**
 * @brief Resizes the container so that it contains n elements
 * @param {vector} vector
 * @param {size_t} n
 */
#define v_resize(vector, n)                                            \
    do {                                                               \
        void* old_ptr = vector;                                        \
        do v_grow(vector);                                             \
        while((n) > v_capacity(vector) && (*vector)old_ptr != vector); \
    } while(0)

/**
 * @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
 * @param {vector} vector
 * @return size_t
 */
#define v_capacity(vector) \
    (vector ? v_meta(vector)->capacity : 0)

/**
 * @brief Checks whether there are any elements in vector
 * @param {vector} vector
 * @return boolean 
 */
#define v_empty(vector) \
    (!vector || (v_meta(vector)->size == 0))

/**
 * @brief Requests that the vector capacity be at least enough to contain n elements.
 * @param {vector} vector
 * @param {size_t} n
 */
#define v_reserve(vector, n)                                                         \
    do {                                                                             \
        if(n > v_capacity(vector)) {                                                 \
            void* p = malloc((n)*sizeof(*vector)+VECTOR_META_SIZE);                  \
            if(p != NULL) vector = p+VECTOR_META_SIZE, v_meta(vector)->capacity = n; \
        }                                                                            \
     } while(0)

/**
 * @brief Returns a reference to the element at position n in the vector.
 * @param {vector} vector
 * @param {size_t} n
 * @return typename(*vector)
 */
#define v_at(vector, n) \
    (vector[n])

/**
 * @brief Returns a reference to the first element in the vector.
 * @param {vector} vector
 * @return typename(*vector)
 */
#define v_front(vector) \
    (vector[0])

/**
 * @brief Returns a reference to the last element in the vector.
 * @param {vector} vector
 * @return typename(*vector)
 */
#define v_back(vector) \
    vector[v_size(vector)-1]

/**
 * @brief Adds a new element at the end of the vector, after its current last element. The content of val is copied to the new element.
 * @param {vector} vector
 * @param {typename(*vector)} val
 */
#define v_push_back(vector, val)                                 \
    if(v_size(vector) == v_capacity(vector)) { v_grow(vector); } \
    vector[v_size(vector)] = (val);                              \
    v_meta(vector)->size++;

/**
 * @brief Removes the last element in the vector, effectively reducing the container size by one.
 * @param {vector} vector
 */
#define v_pop_back(vector)  \
    if(v_meta(vector)->size) { v_meta(vector)->size--; }

/**
 * @brief The vector is extended by inserting a new element before the element at given index, effectively increasing the container size by one.
 * @param {vector} vector
 * @param {size_t} index
 * @param {typename(*vector)} val
 */
#define v_insert(vector, index, val)                                   \
    if(v_size(vector) == v_capacity(vector)) { v_grow(vector) };       \
    memmove(vector+(index)+1, vector+(index), v_size(vector)-(index)); \
    vector[index] = (val);  
/**
 * @brief Removes from the vector a range of elements ([from,to)).
 * @param {vector} vector
 * @param {size_t} from
 * @param {size_t} to
 */
#define v_erase(vector, from, to)                                                    \
   memcpy(vector+(from), vector+(to), (v_size(vector)-(to)+(from))*sizeof(*vector)); \
   v_meta(vector)->size -= (to)-(from);

/**
 * @brief Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
 * @param {vector} vector
 */
#define v_clear(vector) \
    memset(vector, 0, v_size(vector)*typeof(*vector)); \
    vector.size = 0;

/**
 * @brief Creates a copy of src_vector and stores it at dst_vector.
 * @param {vector} dst_vector
 * @param {vector} src_vector
 */
#define v_copy(dst_vector, src_vector)                                 \
    dst_vector = malloc(v_raw_byte_size(src_vector))+VECTOR_META_SIZE; \
    v_meta(dst_vector)->capacity = v_capacity(src_vector);             \
    v_meta(dst_vector)->size = v_size(src_vector);                     \
    memcpy(dst_vector, src_vector, v_size(src_vector)*sizeof(*src_vector));
