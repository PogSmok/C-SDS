#pragma once

#include <stdlib.h>

#define vec(T) \
    struct { \
        T* content; \
        int   elementSize; \
        int   size; \
        int   capacity; \
    }

#define new_vec(T) \
    { \
        malloc(sizeof(T)*32), \
        sizeof(T), \
        0, \
        32, \
    }

#define vec_resize(vec, newSize) \
    do { \
        void* p = realloc(vec.content, newSize*vec.elementSize); \
        if(newSize <= (size_t)-1 && newSize >= 0 && p != NULL) { \
            vec.content = p; \
            vec.capacity = newSize; \
            if(vec.capacity < vec.size) vec.size = vec.capacity; \
        } \
    } while(0)

#define vec_destroy(vec) \
    free(vec.content); \
    vec.content = NULL; \
    vec.elementSize = 0; \
    vec.size = 0; \
    vec.capacity = 0;

#define vec_push(vec, element) \
    do { \
        int lastCapacity = -1; \
        if(vec.size >= vec.capacity) { \
            lastCapacity = vec.capacity; \
            vec_resize(vec, vec.capacity*2); \
        } \
        if(lastCapacity != vec.capacity) vec.content[vec.size++] = element; \
    } while(0)

#define vec_pop(vec) \
    if(vec.size) vec.content[--vec.size];
