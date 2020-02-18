/// @cond IncludeGuard
#ifndef _DGGT_TYPES_H_
/// @endcond

#include <cstdint>
#include <cstddef>

namespace dggt
{

	/*! @brief Represents memory size.
	 *
	 * This is an integer type that always represents a memory size and is the same type returned by sizeof and is platform dependent.
	 * */
	typedef size_t msize;

	/*!
	* @brief Unsigned 64-bit integer type.
	* */
	typedef uint64_t uint64;

	/*!
	 * @brief A shortened version on uint64.
	 * */
	typedef uint64_t u64;

	/*!
	 * @brief A 64-bit integer type for use in boolean expressions.
	 *
	 * This 64-bit integer type can be used as a boolean value or as 64 boolean values.  Used in place of bool for memory alignment considerations.
	 * */
	typedef uint64_t bool64;

	/*!
	 * @brief A shortened version of bool64.
	 * */
	typedef uint64_t b64;

	/*!
	 * @brief 64-bit flag integer type.
	 * */
	typedef uint64_t flag64;

	/*!
	 * @brief Short hand for flag64.
	 * */
	typedef uint64_t fl64;

	/*!
	 * @brief An unsigned 32-bit integer type.  Short hand for uint32_t.
	 * */
	typedef uint32_t uint32;

	/*!
	 * @brief Short hand for uint32.
	 * */
	typedef uint32_t u32;

	typedef bool1 bool;
	typedef b1 bool;
	/*!
	 * @brief A 32-bit integer type for use in boolean expressions.
	 *
	 * This 32-bit integer type can be used as a boolean value or as 64 boolean values.  Used in place of bool for memory alignment considerations.
	 * */
	typedef uint32_t bool32;

	/*!
	 * @brief Short hand for bool32.
	 * */
	typedef uint32_t b32;

	/*!
	 * @brief A 32-bit flag integer type.
	 * */
	typedef uint32_t flag32;

	/*!
	 * @brief Short hand for flag32.
	 * */
	typedef uint32_t fl32;

	/*!
	 * @brief A 64-bit floating point number type.
	 * */
	typedef double float64;

	/*!
	 * @brief An alternate way to write float64.
	 * */
	typedef double real64;

	/*!
	 * @brief Short hand for float64.
	 * */
	typedef double f64;

	/*!
	 * @brief A 32-bit floating point number type.
	 * */
	typedef float float32;

	/*!
	 * @brief An alternate way to write float32.
	 * */
	typedef float real32;

	/*!
	 * @brief Short hand for float32.
	 * */
	typedef float f32;

	/*!
	 * @brief An unsigned 8-bit integer.
	 * */
	typedef uint8_t uint8;

	/*!
	 * @brief Short hand for uint8.
	 * */
	typedef uint8_t u8;

	/*!
	 * @brief An unsigned 8-bit integer type.
	 * */
	typedef uint8_t ubyte;

	/*!
	 * @brief A 32-bit signed integer type.
	 * */
	typedef int32_t int32;

	/*!
	 * @brief Short hand for int32.
	 * */
	typedef int32_t i32;

	/*!
	 * @brief An 8-bit signed integer type.
	 * */
	typedef int8_t sbyte; 
}

/// @cond IncludeGuard
#define _DGGT_TYPES_H_
#endif
/// @endcond
