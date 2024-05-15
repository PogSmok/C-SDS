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

// T* content -> Array of type T, containing elements of the stack.
// size_t size -> Amount of elements in stack.
// size_t capacity -> Number of currently allocated elements (stack(T).content), once exceeded stack(T).content must be reallocated to greater size.
#ifndef stack
#define stack(T) \
    struct { \
        T* content; \
        size_t size; \
        size_t capacity; \
    } 

#endif // #ifndef stack

// Input: 
//      T -> Type of the variable to create the stack for.
// Output:
//      stack(T) -> Created stack.
// Description:
//      Constructor of stack(T).
//      stack(int) myStack = new_stack(int);
// Behaviour:
//      1) If malloc fails stack(T).content will be a NULL pointer.
//      2) By default capacity of a stack(T) is 32
#ifndef new_stack
#define new_stack(T) \
    { \
        malloc(sizeof(T)*32), \
        0, \
        32, \
    }

#endif // #ifndef new_stack

// Input:
//      stack(T) stack
// Output:
//      bool -> True if stack is empty, otherwise false.
// Description: 
//      Checks whether there are any elements in stack.
//      stack_is_empty({71,2}) -> false
//      stack_is_empty({}) -> true
#ifndef stack_is_empty
#define stack_is_empty(stack) \
    stack.size == 0

#endif // #ifndef stack_is_empty

// Input:
//      stack(T) stack
// Output:
//      T -> top-most element of the stack.
// Description: 
//      Returns top-most element of the stack.
//      stack_top({6,2,1}) -> 1
// Behaviour:
//      1) If the stack is empty, stack_top(stack(T)) will return whatever data is stored at stack(T).content[0]
#ifndef stack_top
#define stack_top(stack) \
    stack.size == 0 ? stack.content[0] : stack.content[stack.size-1]  

#endif // #ifndef stack_top

// Input:
//      stack(T) stack
// Output:
//      void -> Function works in-place.
// Description: 
//      Removes top-most element of the stack.
//      stack_pop({12,5,1}) -> {12,5}
// Behaviour:
//      1) If the stack is empty nothing is done.
#ifndef stack_pop
#define stack_pop(stack) \
    if (stack.size != 0) stack.size--;

#endif // #ifndef stack_pop

// Input:
//      stack(T) stack
//      T element -> Element that is going to be pushed to the top.
// Output:
//      void -> Function works in-place.
// Description: 
//      Adds a new element to the top of the stack.
//      Reallocates stack(T).content, if it is needed to fit the new element.
//      stack_push({24,6,3}, 7) -> {24,6,3,7}
// Behaviour:
//      1) If reallocation fails nothing is done.
#ifndef stack_push
#define stack_push(stack, element) \
    do { \
        void* p = stack.content; \
        if (stack.size >= stack.capacity) p = realloc(stack.content, stack.capacity*2); \
        if (p != NULL) { \
            stack.capacity *= 2; \
            stack.content = p; \
            stack.content[stack.size++] = element; \
        } \
    } while(0)

#endif // #ifndef stack_push
