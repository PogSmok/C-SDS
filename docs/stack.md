
# [stack.h][stack.h]
Introduces dynamically allocated stack structure. Includes several utility stack functions. <br >
Entirely implemented using macros. Providing variables of types different than those documented will result in an undefined behaviour.

# Content
**[stack(T)][stack]** -> definition of stack struct <br >
**[new_stack(T)][new_stack]** -> constructs stack(T) <br >
**[stack_free(stack(T) stack)][stack_free]** -> Frees memory allocated by `stack`. <br >
**[stack_is_empty(stack(T) stack)][stack_is_empty]** -> Checks whether there are elements in `stack` <br >
**[stack_top(stack(T) stack)][stack_top]** -> Returns the top-most element of `stack` <br >
**[stack_push(stack(T) stack, T element)][stack_push]** -> Pushes `element` to the top of `stack`. <br >
**[stack_pop(stack(T) stack)][stack_pop]** -> Removes the top-most element of `stack`. <br >

# Example
```c
#include<stdio.h>

#include "stack.h"

int main() {
    // Create a new stack of type int
    stack(int) myStack = new_stack(int);
    
    // Fill the stack with powers of 2
    for (int i = 1; i <= 128; i*=2) {
        stack_push(myStack, i);
    }
    
    // Iterate over stack
    while(!stack_is_empty(myStack)) {
        printf("%i, ", stack_top(myStack)); // 128, 64, 32, 16, 8, 4, 2, 1,
        stack_pop(myStack);
    }
    
    // Free the stack
    stack_free(myStack);
    return 0;
}
}
```

----
# stack
Stack structure is an anonymous struct defined as follows (`T` is the type of values the stack is holding):
```c 
struct { 
    T* content; 
    size_t  elementSize; 
    size_t  size; 
    size_t  capacity;
}
```
The structure should be used as a type declaration. Example for stack of ints: `stack(int) myStack;`. <br >
Working on such a "raw" stack is undefined. All stacks must be initialized with the constructor [new_stack(T)][new_stack]. <br >
Manual modification of `stack(T)` is unadvised; however, if the criteria below are met, all stack methods will work accordingly. Otherwise, behaviour will be undefined:
1) `elementSize == sizeof(T)`
2) `capacity != 0`
3) `capacity > size`
4) `content` has `sizeof(T)*capacity` bytes allocated

----
# new_stack
```c
stack(T) new_stack(type T)
```
Constructs a stack of the given type. The function *must* be called before working on a stack. <br >
The constructed stack has capacity of 32 and `stack(T).content` has memory allocated for `32*sizeof(T)` bytes. <br >
Example of initializing a stack of ints:
```c
stack(int) myStack = new_stack(int);
printf("%zu\n", myStack.capacity); // 32
```
If a program runs out of free memory for allocation, `stack(T).content` will be set to `NULL`.

----
# stack_free
```c
void stack_free(stack(T) stack)
```
Deconstructs a stack and frees the memory allocated by it. Sets all stack fileds to 0. <br >
Freeing the memory is shallow, thus for stacks of uncopyable types, elements must be freed first. <br >
Working on a freed stack is an undefined behaviour, until it is initialized using `new_stack`. <br >
Example of freeing a stack: 
```c
stack(float) myStack = new_stack(float);
stack_free(myStack);
printf("%p %zu %zu %zu", (void*)myStack.content, myStack.elementSize, myStack.size, myStack.capacity); // (nil) 0 0 0
```

----
# stack_is_empty
```c
bool stack_is_empty(stack(T) stack)
```
Checks whether there are any elements contained within `stack`. If there is no elements `stack_is_empty` returns `true`, otherwise `false`.
Example of checking if a stack is empty:
```c
stack(char) myStack = new_stack(char);
printf("%i\n", stack_is_empty(myStack)); // 1
stack_push(myStack, 'a');
printf("%i\n", stack_is_empty(myStack)); // 0
```
----
# stack_top
```c
T stack_top(stack(T) stack)
```
Returns the top-most element of the stack. <br >
If the stack is empty function returns whatever data is stored at `stack.content[0]` <br >
Example of checking the top-most element of a stack: 
```c
stack(bool) myStack = new_stack(bool);
stack_push(myStack, true);
printf("%i\n", stack_top(myStack)); // 1
stack_push(myStack, false);
printf("%i\n", stack_top(myStack)); // 0
```
----
# stack_push
```c
void stack_push(stack(T) stack, T element)
```
Pushes `element` to the top of the `stack`, increments `stack.size`. <br >
Example of pushing an element to the stack:
```c
stack(double) myStack = new_stack(double);
stack_push(myStack, -2.23);
stack_push(myStack, 17.92);
printf("%0.2f\n", stack_top(myStack)); // 17.92
```
----
# stack_pop
```c
void stack_pop(stack(T) stack)
```
Removes the top-most element from `stack`, deincrements `stack.size`. <br >
If `stack.size == 0` `stack.size` will mantain 0. <br >
Example of popping element from the stack:
```c
stack(unsigned int) myStack = new_stack(unsigned int);
stack_push(myStack, 2);
stack_push(myStack, 17);
printf("%u\n", stack_top(myStack)); // 17
stack_pop(myStack);
printf("%u\n", stack_top(myStack)); // 2
```
[stack.h]: https://github.com/PogSmok/C-SDS/blob/master/src/stack.h
[example]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#example
[stack]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#stack
[new_stack]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#new_stack
[stack_free]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#stack_free
[stack_is_empty]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#stack_is_empty
[stack_top]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#stack_top
[stack_push]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#stack_push
[stack_pop]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md#stack_pop
