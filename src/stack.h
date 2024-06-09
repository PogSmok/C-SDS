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

#ifndef stack_stdlib
#define stack_stdlib
#include <stdlib.h> // malloc() free() realloc()
#endif // #ifndef stack_stdlib

/**
 * @brief Declaration of stack type
 */
#define stack(T)         \
    struct {             \
        T* content;      \
        size_t size;     \
        size_t capacity; \
    }*

/**
 * @brief Destructs a stack
 * @param {stack} stack
 */
#define stack_free(stack) \
    free(stack->content); \
    free(stack);          \
    stack = NULL;

/**
 * @brief Returns whether the stack is empty: i.e. whether its size is zero.
 * @param {stack} stack
 * @return bool
 */
#define stack_empty(stack) \
    (!stack || stack->size == 0)

/**
 * @brief Returns the number of elements in the stack.
 * @param {stack} stack
 * @return size_t
 */
#define stack_size(stack) \
    (stack ? stack->size : (size_t)0)

/**
 * @brief Returns the top element in the stack.
 *        Since stacks are last-in first-out containers, the top element is the last element inserted into the stack.
 * @param {stack} stack
 * @return typeof(stack->content)
 */
#define stack_top(stack) \
    (stack->content[stack->size-1])

/**
 * @brief Inserts a new element at the top of the stack, above its current top element.
 * @param {stack} stack
 * @param {typeof(*stack->content)} element
 */
#define DEFAULT_STACK_CAPACITY 32
#define stack_push(stack, element)                                                        \
    do {                                                                                  \
        if(!stack) {                                                                      \
            stack = malloc(sizeof(*stack));                                               \
            stack->content = malloc(sizeof(*stack->content)*DEFAULT_STACK_CAPACITY);      \
            stack->capacity = DEFAULT_STACK_CAPACITY;                                     \
            stack->size = 1;                                                              \
            stack->content[0] = (element);                                                \
        } else if(stack->size >= stack->capacity) {                                       \
            /* growth is exponential */                                                   \
            void* p = realloc(stack->content, sizeof(*stack->content)*2*stack->capacity); \
            if(p) {                                                                       \
                stack->content = p;                                                       \
                stack->capacity *= 2;                                                     \
                stack->content[stack->size++] = (element);                                \
            }                                                                             \
        } else stack->content[stack->size++] = (element);                                 \
    } while(0)

/**
 * @brief Removes the element on top of the stack, effectively reducing its size by one.
 * @param {stack} stack
 */
#define stack_pop(stack) \
    if(stack->size) { stack->size--; }
