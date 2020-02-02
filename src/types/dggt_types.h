/*!
 * @file dggt_types.h
 * @brief Contains useful typedefs.
 *
 * This file contains many useful type definitions mostly for brevity, (often removing the "_t" from the standard library's types. (eg. uin64_t becomes uint64).)
 * but also for clarity (ie. float64 is more descriptive than double)
 * @todo Put these in the dggt namespace
 * */
/// @cond IncludeGuard
#ifndef _DGGT_TYPES_H_
/// @endcond

#include <cstdint>
#include <cstddef>

/// @typedef size_t msize
/// @brief Represents memory size.
///
/// This is an integer type that always represents a memory size and is the same type returned by sizeof and is platform dependent.
typedef size_t msize;

/// @typedef uint64_t uint64
/// @brief Unsigned 64-bit integer type.
typedef uint64_t uint64;

/// @typedef uint64_t u64
/// @brief A shortened version on uint64.
typedef uint64_t u64;

/// @typedef uint64_t bool64
/// @brief A 64-bit integer type for use in boolean expressions.
///
/// This 64-bit integer type can be used as a boolean value or as 64 boolean values.  Used in place of bool for memory alignment considerations.
typedef uint64_t bool64;

/// @typedef uint64_t b64
/// @brief A shortened version of bool64
typedef uint64_t b64;

typedef uint64_t flag64;
typedef uint64_t fl64;
typedef uint32_t uint32;
typedef uint32_t u32;
typedef uint32_t bool32;
typedef uint32_t b32;
typedef uint32_t flag32;
typedef uint32_t fl32;
typedef double float64;
typedef double real64;
typedef double f64;
typedef float float32;
typedef float real32;
typedef float f32;
typedef uint8_t uint8;
typedef uint8_t u8;
typedef uint8_t ubyte;
typedef int32_t i32;
typedef int8_t sbyte; 


/// @cond IncludeGuard
#define _DGGT_TYPES_H_
#endif
/// @endcond
