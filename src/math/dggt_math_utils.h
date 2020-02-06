/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_UTILS_H_
/*! @endcond */

#include <cmath> // TODO: get rid of this!

#include "types/dggt_types.h"

namespace dggt
{
	/*!
	 * @addtogroup math
	 * @{
	 * */

	/*!
	 * @brief Finds the maximum of two values.
	 * @tparam T Any type that overloads the greater-than operator.
	 * @param val0 A value to compare.
	 * @param val1 A value to compare.
	 * @return If val0 is strictly greater-than val1 then val0 is returned, otherwise if val0 is less-than or equal to val1 then val1 is returned.
	 * */
	template <typename T>
	T max(const T& val0,const T& val1)
	{
		return val0>val1?val0:val1;
	}

	/*!
	 * @brief Finds the minimum of two values.
	 * @tparam T Any type that overloads the less-than operator.
	 * @param val0 A value to compare.
	 * @param val1 A value to compare.
	 * @return If val0 is strictly less-than val1 then val0 is returned, otherwise if val0 is greater-than or equal to val1 then val1 is returned.
	 * */
	template <typename T>
	T min(const T& val0,const T& val1)
	{
		return val0<val1?val0:val1;
	}

	/*!
	 * @brief Squares a number.
	 * @tparam T Any type that overloads multiplication.
	 * @param val The value to square.
	 * @return The square of the passed value.
	 * */
	template <typename T>
	T sq(T val)
	{
		return val*val;
	}

	/*!
	 * @brief Raises a value to a power.
	 * @tparam T Any type that can initialize itself from 1 and overloads multiplication.
	 * @param val The value to raise to a power.
	 * @param p The unsigned integer power to raise the value by.
	 * @return val raised to the power, p.
	 * */
	template <typename T>
	T pow(T val,uint32 p)
	{
		if (p==0)
		{
			return T(1);
		}
		else
		{
			return val*pow(val,p-1);
		}
	}

	/*!
	 * @brief Calculates powers of two.
	 * @tparam T An integer type.
	 * @param p The power to raise two.
	 * @return Two raised to the p power.
	 * */
	template <typename T>
	T pow2(uint32 p)
	{
		return T(1<<p);
	}

	/*!
	 * @brief Determines if a number is a power of two.
	 * @tparam T An integer type.
	 * @param val The value to check.
	 * @return Returns nonzero if val is a power of two and zero otherwise.
	 * */
	template <typename T>
	b32 is_pow2(T val)
	{
		if (val)
		{
			return val&(val-T(1))==T(0);
		}
		else
		{
			return 0;
		}
	}

	/*!
	 * @brief Calculates the next power of two larger than a given value.
	 * @tparam T An integer type.
	 * @param val The value used to find the next power of two.
	 * @return The next power of two greater than val.  If val is a power of two next_gt_pow2 still returns the next greater power of two.
	 * */
	template <typename T>
	T next_gt_pow2(T val)
	{
		if (is_pow2(val))
		{
			return val<<T(1);
		}
		else
		{
			T count=T(0);
			while (val>T(0))
			{
				val>>T(1);
				++count;
			}
			return T(1)<<count;
		}
	}

	/*!
	 * @brief Sums the first k powers of two.
	 *
	 * Given k, sum_pow2 will calculate 1+2+4+8+16+...+2^k
	 * @tparam T An integer type.
	 * @param k The highest power of two in the sum.
	 * @return The summation of the first k powers of two.
	 * */
	template <typename T>
	T sum_pow2(u32 k)
	{
		return pow2<T>(k+1)-T(1);
	}

	/*!
	 * @brief Determines if a value is a sum of consecutive powers of two.
	 * @tparam T An integer type.
	 * @param val The value to check.
	 * @return A nonzero value if val is the result of sum_pow2(k) for some k, otherwise returns zero.
	 * */
	template <typename T>
	b32 is_sum_pow2(T val)
	{
		return is_pow2(val+T(1));
	}

	/*!
	 * @brief Finds the next summation of consecutive powers of two which is greater or equal to a given value.
	 * @tparam T An integer type.
	 * */
	template <typename T>
	T next_ge_sum_pow2(T val)
	{
		if (is_sum_pow2(val))
		{
			return val;
		}
		else
		{
			return next_gt_pow2(val)-T(1);
		}
	}

	/*!
	 * @brief Calculates the square root of a 32-bit floating point value.
	 * @param val The value to calculate it's square root.
	 * @return The square root.
	 * */
	inline real32 sqrt(real32 val)
	{
		return std::sqrt(val);
	}

	/*!
	 * @brief Calculates the square root of a 64-bit floating point value.
	 * @param val The value to calculate it's square root.
	 * @return The square root.
	 * */
	inline real64 sqrt(real64 val)
	{
		return std::sqrt(val);
	}

	/*!
	 * @brief Calculates the cosine of a 32-bit floating point value.
	 * @param val The value to calculate it's cosine.
	 * @return The cosine.
	 * */
	inline real32 cosine(real32 val)
	{
		return (real32)cos((real64)val);
	}

	/*!
	 * @brief Calculates the sine of a 32-bit floating point value.
	 * @param val The value to calculate it's sine.
	 * @return The sine.
	 * */
	inline real32 sine(real32 val)
	{
		return (real32)sin((real64)val);
	}

	/*!
	 * @brief Calculates the cosine of a 64-bit floating point value.
	 * @param val The value to calculate it's cosine.
	 * @return The cosine.
	 * */
	inline real64 cosine(real64 val)
	{
		return cos(val);
	}

	/*!
	 * @brief Calculates the cosine of a numerical type.
	 * @param val The value to calculate it's cosine.
	 * @return The cosine.
	 * */
	template <typename T>
	T cosine(T val)
	{
		return T(cosine(real64(val))); 
	}

	/*!
	 * @brief Calculates the sine of a 64-bit floating point value.
	 * @param val The value to calculate it's sine.
	 * @return The sine.
	 * */
	inline real64 sine(real64 val)
	{
		return sin(val);
	}

	/*!
	 * @brief Calculate the sine of a numerical type.
	 * @param val The value to calculate it's sine.
	 * @return The sine.
	 * */
	template <typename T>
	T sine(T val)
	{
		return T(sine(real64(val))); 
	}

	/*!
	 * @brief An enum representing different types of intervals.
	 *
	 * Used as parameters in utility functions.  An open interval is a range of numbers where the endpoints are not included (eg. (5, 7) in mathematical
	 * notation.), a closed interval is one where the endpoints are included (eg. [2, 5].), a left-closed interval has the left side of the interval closed while
	 * the right is open (eg. [5, 7).), and finally a right closed interval is closed on the right side (eg. (1, 7].).
	 * */
	enum intvl_ends
	{
		OPN_INTVL=0, ///< Open interval (eg. (a, b).).
		CLSD_INTVL=1, ///< Closed interval (eg. [a, b].).
		L_CLSD_INTVL=2, ///< Left-closed interval (eg. [a, b).).
		R_CLSD_INTVL=3, ///< Right-closed interval (eg. (a, b].).
		L_OPN_INTVL=R_CLSD_INTVL, ///< Left-open interval.  Same as @ref R_CLSD_INTVL.
		R_OPN_INTVL=L_CLSD_INTVL, ///< Right-open interval.  Same as @ref L_CLSD_INTVL.
	};

	/*!
	 * @brief Determines if a value is within an interval with end-point inclusion is determined by an intvl_ends enum value.
	 * @tparam Any type with a total ordering on it.
	 * @param val The value to test for interval inclusion.
	 * @param leftP The left endpoint in the interval.
	 * @param rightP The right endpoint in the interval.
	 * @param ends Interval endpoint inclusion.
	 * @return A b32 which is nonzero if val is included in the interval and zero otherwise.
	 * */
	template <typename T=real32>
	inline bool32 intvl(T val,
			T leftP,T rightP,intvl_ends ends=CLSD_INTVL)
	{
		bool32 result=0;
		switch(ends)
		{
			case OPN_INTVL:
				{
					result=val>leftP&&val<rightP;
				} break;
			case CLSD_INTVL:
				{
					result=val>=leftP&&val<=rightP;
				} break;
			case R_CLSD_INTVL:
				{
					result=val>leftP&&val<=rightP;
				} break;
			case L_CLSD_INTVL:
				{
					result=val>=leftP&&val<rightP;
				} break;
		}
		return result;
	}

	/*!
	 * @brief Determines if a value is within an interval starting at zero and ending in a passed value.
	 * @tparam Any type with a total ordering on it.
	 * @param val The value to test for interval inclusion.
	 * @param n The right endpoint of the interval.
	 * @param ends Interval endpoint inclusion enum.
	 * @return A b32 which is nonzero if val is included in the interval and zero otherwise.
	 * */
	template <typename T=real32>
	inline bool32 intvl_0n(T val,T n,intvl_ends ends=CLSD_INTVL)
	{
		return intvl(val,T(0),n,ends);
	}

	/*!
	 * @brief Determines if a value is within the interval from zero to one.
	 * @tparam T Any type with a total ordering on it.
	 * @param val The value to test for interval inclusion.
	 * @param ends Interval endpoint inclusion enum.
	 * @return A b32 which is nonzero if val is included in the interval and zero otherwise.
	 * */
	template <typename T=real32>
	inline bool32 intvl_01(T val,intvl_ends ends=CLSD_INTVL)
	{
		return intvl_0n(val,T(1),ends);
	}

	/*!
	 * @brief Determines if a value is within an interval ranging from -n to n.
	 * @tparam T Any type with a total ordering on it. 
	 * @param val The value to test for interval inclusion.
	 * @param n The endpoints of the interval.
	 * @param ends Interval endpoint inclusion enum.
	 * @return A b32 which is nonzero if val is included in the interval and zero otherwise.
	 * */
	template <typename T=real32>
	inline bool32 intvl_centered(T val,
			T n,intvl_ends ends=CLSD_INTVL)
	{
		return intvl(val,-n,n,ends);
	}

	/*!
	 * @brief Determines if a value is within an interval ranging from -1 to 1.
	 * @tparam T Any type with a total ordering on it.
	 * @param val The value to test for interval inclusion.
	 * @param ends Interval endpoint inclusion enum.
	 * @return A b32 which is nonzero if val is included in the interval and zero otherwise.
	 * */
	template <typename T=real32>
	inline bool32 intvl_unit_disk(T val,intvl_ends ends=CLSD_INTVL)
	{
		return intvl_centered(val,T(1),ends);
	}

	/*!
	 * @}
	 * */
}

/*! @cond IncludeGuard */
#define _DGGT_MATH_UTILS_H_
#endif
/*! @endcond */
