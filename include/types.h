#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h> //size_t and ssize_t

//floating point
typedef float f32;
typedef double f64;
//unsigned ints
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
//signed ints
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
//integers for sizing/indexing
typedef size_t usize; //unsigned
typedef ssize_t isize; //signed


typedef struct vec2 {
  f32 x;
  f32 y;
} vec2_t;


#endif
