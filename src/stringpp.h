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

#ifndef STRING_STDLIB
#define STRING_STDLIB
#include <stdlib.h> // malloc() free()
#endif // #ifndef STRING_STDLIB

#ifndef STRING_STRING
#define STRING_STRING
#include <string.h> // memcpy() memmove()
#endif // #ifndef STRING_STRING

/**
 * @brief Helper struct for storing information about the vector, it is stored at string[-1]
 * @private
 */
#define STRING_META_DATA struct { size_t size; size_t capacity; }
#define STRING_META_SIZE sizeof(STRING_META_DATA)

/**
 * @brief Standardization of the syntax for definition of a string
 */
#define string char*

/**
 * @brief NPOS is a constant value with the greatest possible value for an element of type size_t.
 *        As a return value, it is usually used to indicate no matches.
 */
#define NPOS -1ULL

/**
 * @brief Returns memory adress of string's meta data
 * @returns {STRING_META_DATA*}
 * @private
 */
#define string_meta(string) \
    ((STRING_META_DATA*)(string-STRING_META_SIZE))

/**
 * @brief Returns number of bytes string allocates, including meta data
 * @param {string} string
 * @return {size_t}
 * @private
 */
#define string_raw_byte_size(vector) \
    (string_capacity(string)*sizeof(*string)+STRING_META_SIZE)

/**
 * @brief Destructs a string
 * @param {string} string
 */
#define string_free(string) \
    free(string_meta(string))

/**
 * @brief Returns a pointer to the first character of the string.
 * @param {string} string
 * @returns {char*}
 */
#define string_begin(string) \
	(string)
	
/**
 * @brief Returns a pointer to the past-the-end character of the string.
 * @param {string} string
 * @returns {char*}
 */
#define string_end(string) \
	(string+string_length(string))
	
/**
 * @brief Returns the length of the string, in terms of bytes.
 *        Equivilent to string_length().
 * @param {string} string
 * @returns {size_t}
 */
#define string_size(string) \
	string_length(string) 

/**
 * @brief Returns the length of the string, in terms of bytes.
 *        	 to string_size().
 * @param {string} string
 * @returns {size_t}
 */
#define string_length(string) \
	(string ? (string_meta(string)->size) : 0)

/**
 * @brief Returns the size of the storage space currently allocated for the string, expressed in terms of bytes.
 * @param {string} string
 * @returns {size_t}
 */	
#define string_capacity(string) \
	(string ? (string_meta(string)->capacity) : 0)

/**
 * @brief Returns whether the string is empty (i.e. whether its length is 0).
 * @param {string} string
 * @returns {bool}
 */
#define string_empty(string) \
	(string_length(string) == 0)

/**
 * @brief Returns the character at position pos in the string.
 * @param {string} string
 * @param {size_t} pos
 * @returns {char}
 */
#define string_at(string, pos) \
	(string[pos])

/**
 * @brief Returns the last character of the string.
 * @param {string} string
 * @returns {char}
 */
#define string_back(string) \
	(string[string_length(string)-1])
	
/**
 * @brief Returns the first character of the string.
 * @param {string} string
 * @returns {char}
 */
#define string_front(string) \
	(string[0])
	
/**
 * Appends character c to the end of the string, increasing its length by one.
 * @param {string} string
 * @param {char} c
 */
#define string_push_back(string, c) \
	
