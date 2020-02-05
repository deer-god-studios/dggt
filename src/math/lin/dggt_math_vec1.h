/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_VEC1_H_
/*! @endcond */

#include "dggt_math_vec.h"

namespace dggt
{
	/*!
	 * @addtogroup lin
	 * @{
	 * */

	/*!
	 * @brief A vec<D,T> specialization with a single element.
	 * @tparam T A type, normally numeric, the vector's element will be of.
	 * @note Used mostly as a base case in certain recursive functions.
	 * */
	template <typename T>
	struct vec<1,T>
	{
		/*!
		 * @brief The vector's dimension.
		 * */
		static const uint32 DIM=1;

		/*!
		 * @brief The vector's only element.
		 * */
		T x;

		/*!
		 * @brief Default constructor.
		 *
		 * Initializes x to T(0).
		 * */
		vec();

		/*!
		 * @brief An explicit constructor taking an array containing a single element.
		 * @param element An array with one element of type T.
		 * */
		explicit vec(const T element[1]);

		/*!
		 * @brief A constructor taking a value to set x to.
		 * @param val x is set to this value.
		 * */
		vec(const T& val);

		/*!
		 * @brief Basic copy constructor.
		 * @param other The vector to copy.
		 * */
		vec(const vec& other);

		/*!
		 * @brief Copy constructor for copying a vector of a different dimension.
		 *
		 * Will only copy the first element.
		 * @tparam D The other vector's dimension.
		 * @param other The vector to copy.
		 * */
		template <uint32 D>
		vec(const vec<D,T>& other);

		/*!
		 * @brief Addition operator.
		 *
		 * Adds two vectors by adding eachother's x values.
		 * @param rhs The right hand side of the '+' symbol.
		 * @return A vector where x is the sum of the each vectors' x's.
		 * */
		vec operator+(const vec& rhs) const;

		/*!
		 * @brief Subtraction operator.
		 *
		 * Subtracts two vectors by subtracting eachother's x values.
		 * @param rhs The right hand side of the '-' symbol.
		 * @return A vector where x is the difference of the vectors' x's.
		 * */
		vec operator-(const vec& rhs) const;

		/*!
		 * @brief Unary negation operator.
		 *
		 * Negates a vector by negating it's x resulting in a vector pointing in the opposite direction.
		 * @return The negative of the vector.
		 * */
		vec operator-() const;

		/*!
		 * @brief right-scaling operator.
		 *
		 * Scales a vector by right-multiplying x by a scalar. (ie. the scalar appears on the right hand side of the multiplication.  Normally
		 * this does not matter as multiplication is normally commutative.).
		 * @param scalar A scalar (ie. non-vector or a mathematical construct with only magnitude) of type T. 
		 * @return The scaled vector.
		 * */
		vec operator*(const T& scalar) const;

		/*!
		 * @brief 'Contraction' operator.
		 *
		 * The 'inverse' of the scaling operator.  The vector this operator returns is still scaled by the parameter but through the division of every element
		 * in the vector by scalar.  (ie. It's contracted.)
		 * @param scalar A scalar of type T.
		 * @return The contracted vector.
		 * */
		vec operator/(const T& scalar) const;

		/*!
		 * @brief Equality check operator.
		 *
		 * Two vectors are equal if each of their elements are equal. 
		 * @param rhs The right hand side of the '==' symbol.
		 * @return A bool32 which is non-zero if the two vectors are equal and zero otherwise.
		 * */
		bool32 operator==(const vec& rhs) const;

		/*!
		 * @brief Non-equality check operator.
		 *
		 * Two vectors are unequal if there is at least one element that does not equal it's corresponding element in the other vector. 
		 * @param rhs The right hand side of the '!=' symbol.
		 * @return A bool32 which is non-zero if the two vectors are not equal and zero otherwise.
		 * */
		bool32 operator!=(const vec& rhs) const;

		/*!
		 * @brief Assignment operator.
		 * 
		 * Assigns every element of a given vector to another.
		 * @param rhs The source vector in the assignment.
		 * @return A reference to the assigned vector.
		 * */
		vec& operator=(const vec& rhs);

		/*!
		 * @brief Subtract and assign operator.
		 *
		 * Finds the difference of two vectors and assigns the result to the vector on the left hand side of the  '-=' symbol. (ie. Short hand for v0=v0-v1.).
		 * @param rhs The right hand side of the '-=' symbol.
		 * @return A reference to the subtracted and assigned vector.
		 * */
		vec& operator-=(const vec& rhs);

		/*!
		 * @brief Add and assign operator.
		 *
		 * Finds the sum of two vectors and assigns the result to the vector on the left hand side of the  '+=' symbol. (ie. Short hand for v0=v0+v1.).
		 * @param rhs The right hand side of the '+=' symbol.
		 * @return A reference to the added and assigned vector.
		 * */
		vec& operator+=(const vec& rhs);

		/*!
		 * @brief Scale and assign operator.
		 *
		 * Scales a vector and assigns the result to the vector on the left hand side of the  '*=' symbol. (ie. Short hand for v0=v0*scalar.).
		 * @param rhs The scalar on the right hand side of the '*=' symbol.
		 * @return A reference to the scaled and assigned vector.
		 * */
		vec& operator*=(const T& scalar);

		/*!
		 * @brief Contract and assign operator.
		 *
		 * Contracts a vector and assigns the result to the vector on the left hand side of the '*=' symbol. (ie. Short hand for v0=v0/scalar.).
		 * @param rhs The scalar on the right hand side of the '/=' symbol.
		 * @return A reference to the contracted and assigned vector.
		 * */
		vec& operator/=(const T& scalar);

		operator T() const;
		operator T&();

		/*!
		 * @brief Index operator (const version).
		 *
		 * Can access any element in the vector by integer index (eg. vector[0] will return the zeroth element in the vector or the x-value.).
		 * @param index An integer equal to 0.
		 * @return A const reference to the corresponding element.
		 * */
		T& operator[](uint32 index);

		/*!
		 * @brief Index operator (const version).
		 *
		 * Can access any element in the vector by integer index (eg. vector[0] will return the zeroth element in the vector or the x-value.).
		 * @param index An integer equal to 0.
		 * @return A const reference to the corresponding element.
		 * */
		const T& operator[](uint32 index) const;

		/*!
		 * @brief Dot product operator.
		 *
		 * Returns a scalar value which is equal to the dot product of this vector and the parameter.  (eg. Given v0=[1] and v1=[2] then
		 * v0.dot(v1)=(1*2)=2  
		 * @param A vector which will be the right hand side of the dot product.
		 * @return A scalar quantity representing the dot product of the two vectors.
		 * */
		T dot(const vec& rhs) const;
	};

	/*!
	 * @brief A vec<1,T> whose x value is equal to T(1).
	 * @tparam T A type that can be initialized with 1.
	 * */
	template <typename T>
	static const vec<1,T> VEC1_ONE=vec<1,T>(T(1));

	/*!
	 * @brief Another way to write VEC1_ONE<T>.
	 * */
	template <typename T>
	static const vec<1,T> VEC1_XAXIS=vec<1,T>(T(1));

	/*!
	 * @brief left-scaling operator.
	 *
	 * Scales a vector by a scalar by left-multiplying the scalar by the vector's x-value. (ie. The scalar appear on the left hand side of the multiplication.).
	 * @tparam T The element type.
	 * @param scalar The scalar to scale the vector by.
	 * @param vector The vector to scale.
	 * @return The scaled vector.
	 * */
	template <typename T>
	vec<1,T> operator*(const T& scalar,const vec<1,T>& vector);

	/*!
	 * @brief The dot product.
	 *
	 * Finds the dot product of two vectors.
	 * @param lhs The vector on the left hand side of the dot product.
	 * @param rhs The vector on the right hand side of the dot product.
	 * @return The dot product of the given vectors.
	 * */
	template <typename T>
	T dot(const vec<1,T>& lhs,const vec<1,T>& rhs);

	/*!
	 * *}
	 * */
}

#include "dggt_math_vec1.inl"

namespace dggt
{
	/*!
	 * @ingroup lin
	 * @brief Short hand for vec<1,T>.
	 * */
	template <typename T>
	using vec1=vec<1,T>;

	/*!
	 * @ingroup lin
	 * @brief Short hand for vec<1,real32>.
	 * */
	typedef vec<1,real32> vec1f;
}

/*! @cond IncludeGuard */
#define _DGGT_MATH_VEC1_H_
#endif
/*! @endcond */
