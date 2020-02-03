/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_VEC_H_
/*! @endcond */

#include "math/dggt_math_utils.h"

/*!
 * @brief A vector struct of dimension, D and type T.
 *
 * A vector is a mathematical construct consisting of an ordered list of elements along with operations on it.
 * @tparam D An integer representing the dimension of the vector. (ie. The number of elements in the ordered list)
 * @tparam T A type, usually a numeric type.  Each element in the vector will be of this type.  T must be a type that overloads basic arithmetic operations.
 * */
template <uint32 D,typename T>
struct vec
{
	/*!
	 * @brief A static const integer representing the vector's dimension.
	 * */
	static const uint32 DIM=D;
	/*!
	 * @brief The underlying array containing the vector's elements.
	 * */
	T e[D];

	/*!
	 * @brief Default constructor.
	 *
	 * Initializes all elements to T(0).
	 * */
	vec();
	/*!
	 * @brief An explicit constructor which initializes every element to a given value.
	 * @param val The value each element will be initialized to.
	 * @note This constructor is explicit so one can't simply write something like, vec<2,float32> v=5.0f, a seemingly nonsensical and confusing mathematical statement.
	 * */
	explicit vec(const T& val);
	/*!
	 * @brief Basic copy constructor.  Will copy every element in a given vector.
	 * @param other A vector of the same type and dimension to copy.
	 * */
	vec(const vec& other);
	/*!
	 * @brief A constructor for instantiating vectors from a vector of a dimension one less than D.
	 *
	 * One occasionally needs to instatiate a vector from a vector of a lower dimension.  The last element will default to one to be in accordance with homogeneous coordinates used in rendering. 
	 * @param other A vector with a dimension one less than the instantiated vector.
	 * @param last The last element in the new vector.  Defaults to T(1).
	 * */
	vec(const vec<D-1,T>& other, T last=T(1));
	/*!
	 * @brief A copy constructor for instantiating vectors from a vector of any other dimension.
	 * @tparam D2 The dimension of the other vector.
	 * @param other A vector of any other dimension.  If D2 is less than D then it will copy everything in other, followed by setting further elements to T(0)
	 * except for the last element which will be set to T(1).  If D2 is greater than D then everything that can be copied will effectively truncating the vector.
	 * */
	template <uint32 D2>
	vec(const vec<D2,T>& other);

	/*!
	 * @brief Addition operator.
	 *
	 * Adds two vectors by adding each corresponding element.
	 * @param rhs The right hand side of the '+' symbol.
	 * @return A vector where every element is the sum of the corresponding elements in the vector sum.
	 * */
	vec operator+(const vec& rhs) const;
	/*!
	 * @brief Subtraction operator.
	 *
	 * Subtracts two vectors by subtracting each corresponding element.
	 * @param rhs The right hand side of the '-' symbol.
	 * @return A vector where every element is the difference of the corresponding elements in the vector difference.
	 * */
	vec operator-(const vec& rhs) const;
	/*!
	 * @brief Unary negation operator.
	 *
	 * Negates a vector by negating every element resulting in a vector pointing in the opposite direction.
	 * @return The negative of the vector.
	 * */
	vec operator-() const;
	vec operator*(const T& scalar) const;
	vec operator/(const T& scalar) const;
	bool32 operator==(const vec& rhs) const;
	bool32 operator!=(const vec& rhs) const;
	vec& operator=(const vec& rhs);
	vec& operator-=(const vec& rhs);
	vec& operator+=(const vec& rhs);
	vec& operator*=(const T& scalar);
	vec& operator/=(const T& scalar);

	T& operator[](uint32 index);
	const T& operator[](uint32 index) const;

	T dot(const vec& rhs) const;

	T* data() { return e; }
	const T* data() const {return e; }
};

template <uint32 D, typename T>
vec<D,T> operator*(const T& scalar,const vec<D,T>& vector);

template <uint32 D, typename T>
T dot(const vec<D,T>& lhs,const vec<D,T>& rhs);

#include "dggt_math_vec.inl"

#define _DGGT_MATH_VEC_H_
#endif
