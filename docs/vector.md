
# [vector.h][vector]
Introduces dynamically allocated array structure (vector). Includes several utility vector functions. <br >
Entirely implemented using macros. Providing variables of types different than those documented will result in an undefined behaviour.

# Content
**[vec(T)][vec]** -> definition of vector struct <br >
**[new_vec(T)][new_vec]** -> constructs vec(T) <br >
**[vec_resize(vec(T) vec, size_t newSize)][vec_resize]** -> Changes `vec.capacity` to `newSize`. <br >
**[vec_free(vec(T) vec)][vec_free]** -> Frees memory allocated by `vec`. <br >
**[vec_push(vec(T) vec, T element)][vec_push]** -> Appends `element` to `vec`. <br >
**[vec_pop(vec(T) vec)][vec_pop]** -> Removes the last element from `vec`. <br >
**[vec_insert(vec(T) vec, T element, size_t index)][vec_insert]** -> Inserts `element` at `vec.at[index]` <br >
**[vec_remove(vec(T) vec, size_t index)][vec_remove]** -> Removes an element from `vec.at[index]` <br >

# Examples
```c
#include<stdio.h>

#include "vector.h"

int main() {
    // Create a new vector of type int
    vec(int) myVec = new_vec(int);
    
    // Fill the vector with powers of 2
    for (int i = 1; i <= 128; i*=2) {
        vec_push(myVec, i);
    }
    for (int i = 0; i < myVec.size; i++) {
        printf("%i, ", myVec.at[i]); // 1, 2, 4, 8, 16, 32, 64, 128, 
    }
    printf("\n");
    
    // Insert 0 at the front
    vec_insert(myVec, 0, 0);
    for (int i = 0; i < myVec.size; i++) {
        printf("%i, ", myVec.at[i]); // 0, 1, 2, 4, 8, 16, 32, 64, 128, 
    }
    printf("\n");

    // Remove 32 from the vector (6-th index)
    vec_remove(myVec, 6);
    for (int i = 0; i < myVec.size; i++) {
        printf("%i, ", myVec.at[i]); // 0, 1, 2, 4, 8, 16, 64, 128, 
    }
    printf("\n");
    
    // Free the vector
    vec_free(myVec);
    
    return 0;
}
```

```c
#include <stdio.h>

#include "vector.h"

int main() {    
    // Initialize nested 2D vector
    vec(vec(int)) myVec = new_vec(vec(int));

    // Fill our vector of vectors with empty vectors
    for (int i = 0; i < 10; i++) {
        // NOTE: vec_push(myVec, new_vec(int)) will not work,
        //      since each new_vec(TYPE) is an unique anonymous type, it has to be declared first
        vec(int) emptyVec = new_vec(int);
        vec_push(myVec, emptyVec);
    }
    
    // Fill our 2D vector with each row containing elements from 0 to row's index
    for (int i = 0; i < myVec.size; i++) {
        for (int j = 0; j <= i; j++) {
            vec_push(myVec.at[i], j);
        }
    }
    
    for (int i = 0; i < myVec.size; i++) {
        for (int j = 0; j < myVec.at[i].size; j++) {
            printf("%i ", myVec.at[i].at[j]);
        }
        printf("\n");
    }
    /* 
        0 
        0 1 
        0 1 2 
        0 1 2 3 
        0 1 2 3 4 
        0 1 2 3 4 5 
        0 1 2 3 4 5 6 
        0 1 2 3 4 5 6 7 
        0 1 2 3 4 5 6 7 8 
        0 1 2 3 4 5 6 7 8 9
    */ 

    // Free our vector
    for (int i = 0; i < myVec.size; i++) {
        vec_free(myVec.at[i]);
    }
    vec_free(myVec);

    return 0;
}
```

----
# vec
Vector structure is an anonymous struct defined as follows (`T` is the type of values the vector is holding):
```c 
struct { 
    T* at; 
    size_t  elementSize; 
    size_t  size; 
    size_t  capacity;
}
```
The structure should be used as a type declaration. Example for vector of ints: `vec(int) myVector;`. <br >
Working on such a "raw" vector is undefined. All vectors must be initialized with the constructor [new_vec(T)][new_vec]. <br >
Manual modification of `vec(T)` is unadvised; however, if the criteria below are met, all vector methods will work accordingly. Otherwise, behaviour will be undefined:
1) `elementSize == sizeof(T)`
2) `capacity != 0`
3) `capacity > size`
4) `at` has `sizeof(T)*capacity` bytes allocated

----
# new_vec
```c
vec(T) new_vec(type T)
```
Constructs a vec of the given type. The function *must* be called before working on vec. <br >
The constructed vector has capacity of 32 and `vec(T).at` has memory allocated for `32*sizeof(T)` bytes. <br >
Example of initializing a vector of ints:
```c
vec(int) myVec = new_vec(int);
printf("%zu\n", myVec.capacity); // 32
```
If a program runs out of free memory for allocation, `vec(T).at` will be set to `NULL`.

----
# vec_free
```c
void vec_free(vec(T) vec)
```
Deconstructs a vector and frees the memory allocated by it. Sets all vector fileds to 0. <br >
Freeing the memory is shallow, thus for multidimensional vectors or vectors of uncopyable types, elements must be freed first. <br >
See the second [example][examples] for freeing a 2d vector. <br >
Working on a freed vector is an undefined behaviour, until it is initialized using `new_vec`. <br >
Example of freeing a vector: 
```c
vec(float) myVec = new_vec(float);
vec_free(myVec);
printf("%p %zu %zu %zu", (void*)myVec.at, myVec.elementSize, myVec.size, myVec.capacity); // (nil) 0 0 0
```

----
# vec_resize
```c
void vec_resize(vec(T) vec, size_t newSize)
```
Reallocates `vec.at` to contain `newSize*sizeof(T)` bytes. If newSize is smaller than current `vec.size`, `vec.size` will be set to `newSize`. <br >
If reallocation fails, function performs no operations on `vec`. <br >
Example of resizing vector's capacity:
```c
vec(char) myVec = new_vec(char);
vec_resize(myVec, 128);
printf("%zu\n", myVec.capacity); // 128
```
----
# vec_push
```c
void vec_push(vec(T) vec, T element)
```
Appends `element` to `vec`. <br >
If necessary calls `vec_resize` to fit the new element. If reallocation fails and `vec.at` cannot be expanded to fit the new element no operation is performed on the vector. <br >
Example of pushing an element to a vector: 
```c
vec(double) myVec = new_vec(double);
vec_push(myVec, -2.23);
vec_push(myVec, 17.92);
printf("%0.2f %0.2f\n", myVec.at[0], myVec.at[1]); // -2.23 17.92
```
----
# vec_pop
```c
T vec_pop(vec(T) vec)
```
Removes last element from `vec`, deincrements `vec.size` and returns the removed element. <br >
If `vec.size == 0` vec_pop will return whatever data is stored at `vec.at[0]` and `vec.size` will mantain 0. <br >
Example of popping element from the vector:
```c
vec(unsigned int) myVec = new_vec(unsigned int);
vec_push(myVec, 2);
vec_push(myVec, 17);
unsigned int removedElement = vec_pop(myVec);
vec_push(myVec, 5);
printf("%u %u %u\n", myVec.at[0], myVec.at[1], removedElement); // 2 5 17
```
----
# vec_insert
```c
void vec_insert(vec(T) vec, T element, size_t index)
```
Inserts `element` at `index`, shifts elements from `vec.at[index]` to `vec.at[size-1]` one index to the right. <br >
If necessary calls `vec_resize` to fit the new element. If reallocation fails and `vec.at` cannot be expanded to fit the new element no operation is performed on the vector. <br >
If `index >= vec.size` function is equivalent to calling `vec_push`. <br >
Example of inserting an element to a vector at given index:
```c
vec(int) myVec = new_vec(int);
for(int i = 0; i < 3; i++) {
    vec_push(myVec, i*5);
    printf("%i, ", myVec.at[i]); // 0, 5, 10,
}
printf("\n");

vec_insert(myVec, -16, 1);
for(int i = 0; i < myVec.size; i++) {
    printf("%i, ", myVec.at[i]); // 0, -16, 5, 10,
}
```
----
# vec_remove
```c
void vec_remove(vec(T) vec, size_t index)
```
Removes `element` from `index`, shifts elements from `vec.at[index+1]` to `vec.at[size-1]` one index to the left. <br >
If `index >= vec.size` function is equivalent to calling `vec_pop`. <br >
Example of removing an element from a vector at given index:
```c
vec(int) myVec = new_vec(int);
for(int i = 0; i < 5; i++) {
    vec_push(myVec, i+7);
    printf("%i, ", myVec.at[i]); // 7, 8, 9, 10, 11
}
printf("\n");

vec_remove(myVec, 2);
for(int i = 0; i < myVec.size; i++) {
    printf("%i, ", myVec.at[i]); // 7, 8, 10, 11
}
```
[vector]: https://github.com/PogSmok/C-SDS/blob/master/src/vector.h
[examples]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#examples
[vec]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec
[new_vec]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#new_vec
[vec_free]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_free
[vec_resize]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_resize
[vec_push]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_push
[vec_pop]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_pop
[vec_insert]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_insert
[vec_remove]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_remove
