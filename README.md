<div align="center">
	<h1>C-SDS: C Standard Data Structures</h1>
	<h3>Collection of single file libraries of the most popular and useful data structures.</h3>

  <br>
  
  [![Report a bug][issue-badge]][issue-link]
  [![Suggest a data structure][feature-badge]][feature-link]
  
  <br>
  
  [![License][license-badge]][license-link]

</div>

# Overview
C-SDS is a comprehensive collection of well-known and practical data structures that have been implemented in the C programming language using only header files and preprocessor instructions (macro). Thanks to such a peculiar implementation all data structures are capable of working on any type, even user-defined ones. This project offers extensive and detailed documentation, making it incredibly easy and efficient to utilize any data structure of your choice. Functionality of said structures is similar to that present in C++.

# Files
C-SDS consists of:
* [README.md][readme-link] > File describing the project
* [LICENSE][license-link] > License under which the libraries must be used
* [docs][docs-link] > Directory with documentation for libraries
* [src][src-link] > Directory with source code of libraries

# Library progress
💎 - finished <br >
✔️ - operational <br > 
〽️ - work in progress <br > 
❌ - not implemented yet

## Dynamic String
| Library | Source Code | Documentation
| ------- | ----------- | -------------
| stringpp | 〽️ [stringpp.h][stringpp.h-link] | ❌          

## Sequence containers
| Library | Source code | Documentation 
| ------- | ----------- | -------------
| vector  | ✔️[vector.h][vector.h-link] | ❌
| deque   | 〽️ [deque.h][deque.h-link] | ❌
| forward_list | ❌         | ❌
| list | ❌         | ❌

## Associative containers
| Library | Source code | Documentation 
| ------- | ----------- | -------------
| set     |  ❌         | ❌
| map     |  ❌         | ❌

## Container adaptors
| Library | Source code | Documentation 
| ------- | ----------- | -------------
| stack   | ✔️[stack.h][stack.h-link] | ❌
| queue   | ❌         | ❌

[issue-link]: https://github.com/PogSmok/C-SDS/issues
[feature-link]: https://github.com/PogSmok//C-SDS/discussions/categories/ideas
[license-link]: https://github.com/PogSmok//C-SDS/blob/master/LICENSE
[readme-link]: https://github.com/PogSmok/C-SDS/blob/master/README.md
[docs-link]: https://github.com/PogSmok/C-SDS/tree/master/docs
[src-link]: https://github.com/PogSmok/C-SDS/tree/master/src
[stringpp.h-link]: https://github.com/PogSmok/C-SDS/blob/master/src/stringpp.h
[vector.h-link]: https://github.com/PogSmok/C-SDS/blob/master/src/vector.h
[vector.md-link]: https://github.com/PogSmok/C-SDS/blob/master/docs/vector.md
[stack.h-link]: https://github.com/PogSmok/C-SDS/blob/master/src/stack.h
[stack.md-link]: https://github.com/PogSmok/C-SDS/blob/master/docs/stack.md
[deque.h-link]: https://github.com/PogSmok/C-SDS/blob/master/src/deque.h

[issue-badge]: https://img.shields.io/badge/%F0%9F%91%BE-Report%20a%20bug-%23a8161b?style=for-the-badge&labelColor=%23ab5053
[feature-badge]: https://img.shields.io/badge/%F0%9F%92%A1-Suggest%20a%20feature-%2300d1ca?style=for-the-badge&labelColor=%23c8f7f6
[license-badge]: https://img.shields.io/badge/Apache%202.0-red?style=for-the-badge&label=License
