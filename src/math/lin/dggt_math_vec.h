/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_VEC_H_
/*! @endcond */

#include "math/dggt_math_utils.h"

namespace dggt
{
	template <uint32 D,typename T>
	struct vec
	{
		/*!
		 * @brief A static const unsigned integer representing the vector's dimension.
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
		 * A vector is a mathematical construct consisting of an ordered list of elements along with operations on it.
		 * @tparam D An integer representing the dimension of the vector. (ie. The number of elements in the ordered list)
		 * @tparam T A type, usually a numeric type.  Each element in the vector will be of this type.  T must be a type that overloads basic arithmetic operations.
		 * */

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

		/*!
		 * @brief right-scaling operator.
		 *
		 * Scales a vector by right-multiplying every element by a scalar. (ie. the scalar appears on the right hand side of the multiplication.  Normally
		 * this does not matter as multiplication is normally commutative.).
		 * @param scalar A scalar (ie. non-vector or a mathematical construct with only magnitude) of type T. 
		 * @return The scaled vector.
		 * */
		vec operator*(const T& scalar) const;

		/*!
		 * @brief 'Contraction' operator.
		 *
		 * The 'inverse' of the scaling operator.  The vector this operator returns is still a scaled by the parameter but through the division of every element
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

		/*!
		 * @brief Index operator.
		 *
		 * Can access any element in the vector by integer index (eg. vector[0] will return the zeroth element in the vector or the x-value.).
		 * @param index An integer from 0 to D-1.
		 * @return A reference to the corresponding element.
		 * */
		T& operator[](uint32 index);

		/*!
		 * @brief Index operator (const version).
		 *
		 * Can access any element in the vector by integer index (eg. vector[0] will return the zeroth element in the vector or the x-value.).
		 * @param index An integer from 0 to D-1.
		 * @return A const reference to the corresponding element.
		 * */
		const T& operator[](uint32 index) const;

		/*!
		 * @brief Dot product operator.
		 *
		 * Returns a scalar value which is equal to the dot product of this vector and the parameter.  (eg. Given v0=[1,2] and v1=[2,2] then
		 * v0.dot(v1)=(1*2)+(2*2)=2+4=6.
		 * @param A vector which will be the right hand side of the dot product.
		 * @return A scalar quantity representing the dot product of the two vectors.
		 * */
		T dot(const vec& rhs) const;

		/*!
		 * @brief Returns a pointer to the element array.
		 *
		 * Used for passing the vector's element array to other libraries.
		 * @return A pointer to the first element in the array.
		 * */
		T* data() { return e; }

		/*!
		 * @brief Returns a const pointer to the element array.
		 *
		 * Used for passing the vector's element array to other libraries.
		 * @return A const pointer to the first element in the array.
		 * */
		const T* data() const {return e; }
	};

	/*!
	 * @brief left-scaling operator.
	 *
	 * Scales a vector by a scalar by left-multiplying the scalar by every element. (ie. The scalar appear on the left hand side of the multiplication.).
	 * @tparam D The dimension of the vector.
	 * @tparam T The element type.
	 * @param scalar The scalar to scale the vector by.
	 * @param vector The vector to scale.
	 * @return The scaled vector.
	 * */
	template <uint32 D, typename T>
	vec<D,T> operator*(const T& scalar,const vec<D,T>& vector);

	/*!
	 * @brief The dot product.
	 *
	 * Finds the dot product of two vectors.
	 * @param lhs The vector on the left hand side of the dot product.
	 * @param rhs The vector on the right hand side of the dot product.
	 * @return The dot product of the given vectors.
	 * */
	template <uint32 D, typename T>
	T dot(const vec<D,T>& lhs,const vec<D,T>& rhs);
}
#include "dggt_math_vec.inl"

/*! @cond IncludeGuard */
#define _DGGT_MATH_VEC_H_
#endif
/*! @endcond */
