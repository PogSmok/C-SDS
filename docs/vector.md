
# [vector.h][vector]
Introduces dynamically allocated array structure (vector) working for any type (even user-defined structs etc.). Includes several utility vector functions.
Entirely implemented using macros. Providing variables of types different than those documented will result in an undefined behaviour.

## Content
**[vec(T)][vec]** -> definition of vector struct <br >
**[new_vec(T)][new_vec]** -> constructs vec(T) <br >
**[vec_resize(vec(T) vec, size_t newSize)][vec_resize]** -> Changes `vec.capacity` to `newSize`. <br >
**[vec_free(vec(T) vec)][vec_free]** -> Frees memory allocated by `vec`. <br >
**[vec_push(vec(T) vec, T element)][vec_push]** -> Appends `element` to `vec`. <br >
**[vec_insert(vec(T) vec, T element, size_t index)][vec_insert]** -> Inserts `element` at `vec.at[index]` <br >
**[vec_remove(vec(T) vec, size_t index)][vec_remove]** -> Removes an element from `vec.at[index]` <br >

## Example
```c
#include<stdio.h>

#include "vector.h"

int main() {
    // Create a new vector of type int
    vec(int) myVec = new_vec(int);
    
    // Fill the vector with powers of 2
    for(int i = 1; i <= 128; i*=2) {
        vec_push(myVec, i);
    }
    for(int i = 0; i < myVec.size; i++) {
        printf("%i, ", myVec.at[i]); // 1, 2, 4, 8, 16, 32, 64, 128, 
    }
    printf("\n");
    
    // Insert 0 at the front
    vec_insert(myVec, 0, 0);
    for(int i = 0; i < myVec.size; i++) {
        printf("%i, ", myVec.at[i]); // 0, 1, 2, 4, 8, 16, 32, 64, 128, 
    }
    printf("\n");

    // Remove 32 from the vector (6-th index)
    vec_remove(myVec, 6);
    for(int i = 0; i < myVec.size; i++) {
        printf("%i, ", myVec.at[i]); // 0, 1, 2, 4, 8, 16, 64, 128, 
    }
    printf("\n");
    
    //Free the vector
    vec_free(myVec);
    
    return 0;
}
```
## vec

## new_vec

## vec_resize

## vec_insert

## vec_remove
[vector]: https://github.com/PogSmok/C-SDS/blob/master/src/vector.h
[vec]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec
[new_vec]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#new_vec
[vec_resize]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_resize
[vec_free]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_free
[vec_push]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_push
[vec_insert]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#vec_insert
[vec_remove]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md#new_vec_remove