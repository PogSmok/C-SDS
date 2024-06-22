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

#ifndef deque_stdlib
#define deque_stdlib
#include <stdlib.h> // malloc() calloc() free() realloc()
#endif // #ifndef deque_stdlib

#ifndef deque_string
#define deque_string
#include <string.h> // memcpy() memmove()
#endif // #ifndef deque_string

/**
 * @brief Declaration of deque type
 */
#define deque(T)         \
    struct {             \
        T* content;      \
        size_t front;    \
        size_t back;     \
        size_t capacity; \
    }*

/**
 * @brief Destructs a deque
 * @param {deque} deque
 */
#define deque_free(deque) \
    free(deque->content); \
    free(deque);          \
    deque = NULL;

/**
 * @brief Returns a pointer pointing to the first element in the deque container.
 * @param {deque} deque
 * @return {typeof(deque->content)}
 */
#define deque_begin(deque) \
    (deque->content+deque->front)

/**
 * @brief Returns a pointer pointing to the past-the-end element in the deque container.
 * @param {deque} deque
 * @return {typeof(deque->content)}
 */
#define deque_end(deque) \
    (deque->content+deque->back)

/**
 * @brief Returns the number of elements in the deque container.
 * @param {deque} deque
 * @return {size_t}
 */
#define deque_size(deque) \
    (deque ? deque->back-deque->front : 0)

/**
 * @brief Initializes a deque
 * @param {deque} deque
 * @private
 */
#define DEFAULT_DEQUE_CAPACITY 32
#define deque_init(deque)                                                    \
    deque = malloc(sizeof(*deque));                                          \
    deque->content = malloc(sizeof(*deque->content)*DEFAULT_DEQUE_CAPACITY); \
    deque->capacity = DEFAULT_DEQUE_CAPACITY;                                \
    deque->front = deque->back = DEFAULT_DEQUE_CAPACITY/2;

/**
 * @brief Resizes the container so that it contains n elements. 
 *        If n is greater than current container size, the additional elements will be 0 initialized at the back of the deque.
 *        If n is smaller than current container size, the excessive elements will be removed from the back of the deque.
 * @param {deque} deque
 * @param {size_t} n
 */
#define deque_resize(deque, n)                                                                          \
    do {                                                                                                \
        if(!deque) { deque_init(deque); }                                                               \
        if(n < deque_size(deque)) {                                                                     \
            deque->back -= deque_size(deque)-(n);                                                       \
        } else {                                                                                        \
            if(n-deque_size(deque)+deque->back > deque->capacity) {                                     \
                size_t new_cap = deque->capacity;                                                       \
                while(new_cap < (n)) new_cap *= 2;                                                      \
                typeof(deque->content) p = calloc(new_cap, sizeof(*deque->content));                    \
                if(p) {                                                                                 \
                    /* "center" the content within new memory */                                        \
                    memcpy(p+(new_cap - (n))/2 , deque->content+deque->front, deque_size(deque));       \
                    free(deque->content);                                                               \
                    deque->content = p;                                                                 \
                    deque->front = (new_cap - (n))/2;                                                   \
                    deque->back = deque->front + (n);                                                   \
                    deque->capacity = new_cap;                                                          \
                }                                                                                       \
            } else {                                                                                    \
                memset(deque->content+deque->back, 0, sizeof(*deque->content)*((n)-deque_size(deque))); \
                deque->back += (n)-deque_size(deque);                                                   \
            }                                                                                           \
        }                                                                                               \
    } while(0)

/**
 * @brief Returns whether the deque container is empty (i.e. whether its size is 0).
 * @param {deque} deque
 * @returns {bool}
 */
#define deque_empty(deque) \
    (deque ? deque->back == deque->front : 1)

/**
 * @brief Returns a reference to the element at position n in the deque container object.
 * @param {deque} deque
 * @param {size_t} n
 * @returns {typeof(*deque->content)}
 */
#define deque_at(deque, n) \
    (deque->content[deque->front+n])

/**
 * @brief Returns the first element in the deque container.
 * @param {deque} deque
 * @returns {typeof(*deque->content)}
 */
#define deque_front(deque) \
    (deque->content[deque->front])

/**
 * @brief Returns the last element in the container.
 * @param {deque} deque
 * @returns {typeof(*deque->content)}
 */
#define deque_back(deque) \
    (deque->content[deque->back-1])

/**
 * @brief Adds a new element at the end of the deque container, after its current last element.
 * @param {deque} deque
 * @param {typeof(*deque->content)} val
 */
#define deque_push_back(deque, val)                                                                                      \
    do {                                                                                                                 \
        if(!deque) { deque_init(deque); }                                                                                \
        if(deque->back == deque->capacity) {                                                                             \
            typeof(deque->content) p = malloc(sizeof(*deque->content)*deque->capacity*2);                                \
            if(p) {                                                                                                      \
                size_t old_size = deque_size(deque);                                                                     \
                /* "center" the content within new memory */                                                             \
                memcpy(p+deque->capacity-(old_size/2), deque->content+deque->front, old_size * sizeof(*deque->content)); \
                free(deque->content);                                                                                    \
                deque->content = p;                                                                                      \
                deque->front = deque->capacity-(old_size)/2;                                                             \
            deque->back = deque->front + old_size;                                                                       \
                deque->capacity *= 2;                                                                                    \
            }                                                                                                            \
        }                                                                                                                \
        if(deque->back < deque->capacity) {                                                                              \
            deque->content[deque->back] = (val);                                                                         \
            deque->back++;                                                                                               \
        }                                                                                                                \
    } while(0)

/**
 * @brief Adds a new element at the beginning of the deque container, before its current first element.
 * @param {deque} deque
 * @param {typeof(*deque->content)} val
 */
#define deque_push_front(deque, val)                                                                                     \
    do {                                                                                                                 \
        if(!deque) { deque_init(deque); }                                                                                \
        if(deque->front == 0) {                                                                                          \
            typeof(deque->content) p = malloc(sizeof(*deque->content) * deque->capacity * 2);                            \
            if(p) {                                                                                                      \
                size_t old_size = deque_size(deque);                                                                     \
                /* "center" the content within new memory */                                                             \
                memcpy(p+deque->capacity-(old_size/2), deque->content+deque->front, old_size * sizeof(*deque->content)); \
                free(deque->content);                                                                                    \
                deque->content = p;                                                                                      \
                deque->front = deque->capacity-(old_size)/2;                                                             \
                deque->back = deque->front + old_size;                                                                   \
                deque->capacity *= 2;                                                                                    \
            }                                                                                                            \
        }                                                                                                                \
        if(deque->front != 0) {                                                                                          \
            deque->front--;                                                                                              \
            deque->content[deque->front] = (val);                                                                        \
        }                                                                                                                \
    } while(0)

/**
 * @brief Removes the last element in the deque container, effectively reducing the container size by one.
 * @param {deque} deque
 */
#define deque_pop_back(deque) \
    if(deque_size(deque)) { deque->back--; }

/**
 * @brief Removes the first element in the deque container, effectively reducing the container size by one.
 * @param {deque} deque
 */
#define deque_pop_front(deque) \
    if(deque_size(deque)) { deque->front++; }

/**
 * @brief The deque container is extended by inserting the new element before the element at the specified position.
 * @param {deque} deque
 * @param {size_t} position
 * @param {typeof(*deque->content)} val
 */
#define deque_insert(deque, position, val)                                                                                                                               \
    do {                                                                                                                                                                 \
        if(deque->back == deque->capacity) {                                                                                                                             \
            typeof(deque->content) p = malloc(sizeof(deque->content)*deque->capacity*2);                                                                                 \
            if(p) {                                                                                                                                                      \
                    size_t old_size = deque_size(deque);                                                                                                                 \
                    /* "center" the content within new memory */                                                                                                         \
                    memcpy(p+(deque->capacity*2-old_size)/2, deque->content+deque->front, old_size);                                                                     \
                    free(deque->content);                                                                                                                                \
                    deque->content = p;                                                                                                                                  \
                    deque->front = (deque->capacity-old_size)/2;                                                                                                         \
                    deque->back = deque->front + old_size + 1;                                                                                                           \
                    deque->capacity *= 2;                                                                                                                                \
                                                                                                                                                                         \
                    memmove(deque->content+deque->front+(position)+1, deque->content+deque->front+(position), (deque_size(deque)-(position)) * sizeof(*deque->content)); \
                    deque->content[deque->front+position] = (val);                                                                                                       \
                    deque->back++;                                                                                                                                       \
                }                                                                                                                                                        \
        } else {                                                                                                                                                         \
            memmove(deque->content+deque->front+(position)+1, deque->content+deque->front+(position), (deque_size(deque)-(position)) * sizeof(*deque->content));         \
            deque->content[deque->front+position] = (val);                                                                                                               \
            deque->back++;                                                                                                                                               \
        }                                                                                                                                                                \
    } while(0)

/**
 * @brief Removes the element at the specified position.
 * @param {deque} deque
 * @param {size_t} position
 */
#define deque_erase(deque, position)                                                                                                                           \
    if((position) == 0) { deque_pop_front(deque) }                                                                                                             \
    else if((position) == deque->capacity-1) { deque_pop_back(deque) }                                                                                         \
    else {                                                                                                                                                     \
        memmove(deque->content+deque->front+(position), deque->content+deque->front+(position)+1, (deque_size(deque)-(position)-1) * sizeof(*deque->content)); \
        deque->back--;                                                                                                                                         \
    }
