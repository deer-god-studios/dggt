/// @cond IncludeGuard
#ifndef _DGGT_DEFINES_H_
/// @endcond

#include <climits>
#include <cfloat>

#ifdef DGGT_DEBUG
#ifdef ASSERT
#undef ASSERT(P)
#endif
#define ASSERT(P) { if(!(P)) { int oops=*((int*)0); } } 
#else
#ifdef ASSERT
#undef ASSERT(P)
#endif

#define ASSERT(P)
#endif

/*!
 * @def ASSERT(P)
 * @brief Halts (ie. crashes) the program if the given predicate evaluates to false.
 * */

/// @brief Resolves to the number of elements in a stack array.
/// @warning Only works with arrays defined with the syntax: type arrayName[#]
#define ARRAY_COUNT(X) (sizeof((X)))/(sizeof((X)[0]))

/// @brief Maximum 32-bit unsigned integer.
#define MAX_UINT32 UINT_MAX

/// @brief Maximum memory size integer.
///	@warning Always returns max unsigned long long (64-bit unsigned integer) which will be wrong on 32-bit systems.
#define MAX_MSIZE ULLONG_MAX

/// @brief Maximum 32-bit floating point.
#define MAX_FLOAT32 FLT_MAX

/// @brief Minimum positive 32-bit floating point.
#define MIN_FLOAT32 FLT_MIN

/// @brief A different way of representing MAX_REAL32
#define MAX_REAL32 MAX_FLOAT32

/// @brief A different way of representing MIN_REAL32
#define MIN_REAL32 MIN_REAL32

/// @cond IncludeGuard
#define _DGGT_DEFINES_H_
#endif
/// @endcond
