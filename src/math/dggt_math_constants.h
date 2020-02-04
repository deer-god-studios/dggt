/// @cond IncludeGuard
#ifndef _DGGT_MATH_CONSTANTS_H_
/// @endcond
#include "types/dggt_types.h"

namespace dggt
{
	/*!
	 * @brief The ratio of a circle's circumference over it's diameter. 
	 * */
	template <typename T>
	static const T PI=T(3.141592653589793238);

	static const u32 LARGE_PRIME32=2'038'074'743;
	static const u64 LARGE_PRIME64=19'957'072'636'091;
}

/// @cond IncludeGuard
#define _DGGT_MATH_CONSTANTS_H_
#endif
/// @endcond IncludeGuard
