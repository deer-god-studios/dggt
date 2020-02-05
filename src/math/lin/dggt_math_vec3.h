
/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_VEC3_H_
/*! @endcond */

#include "dggt_math_vec.h"

namespace dggt
{
	/*!
	 * @addtogroup lin
	 * @{
	 * */

	/*!
	 * @brief A 3D vector struct.
	 *
	 * A specialization of vec<D,T>.
	 * @tparam T The vector's underlying type.
	 * */
	template <typename T>
	struct vec<3,T>
	{
		/*!
		 * @brief The vector's dimension.
		 * */
		static const uint32 DIM=3;

		/*!
		 * @brief The vector's x-value.
		 * */
		T x;

		/*!
		 * @brief The vector's y-value.
		 * */
		T y;

		/*!
		 * @brief The vector's z-value.
		 * */
		T z;

		/*!
		 * @brief Default constructor.
		 *
		 * Initializes all the vector's elements to T(0).
		 * */
		vec();

		/*!
		 * @brief Constructor taking an array of elements with 3 values.
		 * 
		 * Initializes each element of the vector to it's corresponding
		 * element in the array.
		 * @param elements The array to copy. 
		 * */
		vec(const T elements[3]);

		/*!
		 * @brief Explicit constructor taking a value that x, y and z will be
		 * set to.
		 * @param val The value to initialize x, y and z with.
		 * */
		explicit vec(const T& val);

		/*!
		 * @brief A constructor taking an x, y and z value.
		 * @param x The vector's x value.
		 * @param y The vector's y value.
		 * @param z The vector's z value.
		 * */
		vec(const T& x,const T& y,const T& z);

		/*!
		 * @brief Basic copy constructor.
		 * @param other The vector to copy.
		 * */
		vec(const vec& other);

		/*!
		 * @brief Copy constructor taking a vector with a different dimension.
		 *
		 * Copies as many elements as possible setting any missed elements
		 * with T(0) unless it's the last element in which case it sets it
		 * to T(1).
		 * @tparam D The dimension of the vector to copy.
		 * @param other The vector to copy.
		 * */
		template <uint32 D>
		vec(const vec<D,T>& other);

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

		/*!
		 * @brief Index operator.
		 *
		 * Can access any element in the vector by integer index (eg. vector[0] will return the zeroth element in the vector or the x-value.).
		 * @param index An integer equal to 0, 1 or 2.
		 * @return A reference to the corresponding element.
		 * */
		T& operator[](uint32 index);

		/*!
		 * @brief Index operator (const version).
		 *
		 * Can access any element in the vector by integer index (eg. vector[0] will return the zeroth element in the vector or the x-value.).
		 * @param index An integer equal to 0, 1 or 2.
		 * @return A const reference to the corresponding element.
		 * */
		const T& operator[](uint32 index) const;

		/*!
		 * @brief Calculates the dot product.
		 * @param rhs The right hand side of the dot product.
		 * @return The dot product.
		 * */
		T dot(const vec& rhs) const;

		/*!
		 * @brief Cross product.
		 *
		 * The cross product of two vectors is a vector perpendicular to both
		 * vectors in the direction determined by the right-hand rule.
		 * (ie. Hold your hand so your fingers can curl in the direction
		 * from the left hand side to the right hand side.  Your thumb is
		 * pointing in the direction of the cross product.).  The length
		 * is determined by the product of the length's of each vector
		 * multiplied by the sine of the angle between them.
		 * @param rhs The right hand side of the cross product.
		 * @return The cross product of the two vectors.
		 * */
		vec cross(const vec& rhs) const;

		/*!
		 * @brief Calculates the length of a vector squared.
		 * @return The length squared.
		 * */
		T len_sq() const;

		/*!
		 * @brief Calculates a vector's length.
		 * @return The length.
		 * */
		T len() const;

		/*!
		 * @brief Calculates the normal of a vector.
		 *
		 * A vector's normal is a vector of unit length pointing in the same
		 * direction.
		 * @return The normal.
		 * */
		vec normal() const;

		/*!
		 * @brief Normalizes a vector.
		 *
		 * This actually changes the vector normalize was called on, setting
		 * it's elements to that of it's normal.
		 * @return A reference to the normalized vector.
		 * */
		vec& normalize();

		/*!
		 * @brief The hadamard product.
		 * 
		 * The hadamard product of two vectors is another vector with elements
		 * that are simply the product of the two vector's corresponding elements.
		 * (eg. given v0=[x,y] and v1=[s,t] then v0.hadamard(v1)=[x*s,y*t].).
		 * These are often used for color blending.
		 * @param rhs The right hand side of the product.
		 * @return The hadamard product.
		 * */
		vec hadamard(const vec& rhs) const;

		/*!
		 * @brief Linearly interpolates two vectors weighted by t.
		 *
		 * A linear interpolation is a kind of blending between two values
		 * assuming one transforms continuously and linearly into the other
		 * as a parameter, t, varies.  When t=0 the return value is this vector and
		 * when t=1 the return value is b and everything in between.
		 * @param t The blend amount toward b.
		 * @param b The vector to interpolate with this one.
		 * @return The linear interpolation of the two vectors.
		 * */
		vec lerp(const T& t,const vec& b) const;

		/*!
		 * @brief Returns a pointer to the element array.
		 *
		 * Used for passing the vector's element array to other libraries.
		 * @return A pointer to the first element in the array.
		 * */
		T* data() {return &x; }

		/*!
		 * @brief Returns a const pointer to the element array.
		 *
		 * Used for passing the vector's element array to other libraries.
		 * @return A const pointer to the first element in the array.
		 * */
		const T* data() const {return &x;}
	};

	/*!
	 * @brief Scaling operator.
	 * @tparam T The vector's underlying type.
	 * @param scalar The scaling factor.
	 * @param vector The vector to scale.
	 * @return The scaled vector.
	 * */
	template <typename T>
	vec<3,T> operator*(const T& scalar,const vec<3,T>& vector);

	/*!
	 * @brief The dot product.
	 * @tparam The vectors' underlying type.
	 * @param lhs The left hand side of the dot product.
	 * @param rhs The right hand side of the dot product.
	 * @return The dot product.
	 * */
	template <typename T>
	T dot(const vec<3,T>& lhs,const vec<3,T>& rhs);

	/*!
	 * @brief Cross product.
	 *
	 * The cross product of two vectors is a vector perpendicular to both
	 * vectors in the direction determined by the right-hand rule.
	 * (ie. Hold your hand so your fingers can curl in the direction
	 * from the left hand side to the right hand side.  Your thumb is
	 * pointing in the direction of the cross product.).  The length
	 * is determined by the product of the length's of each vector
	 * multiplied by the sine of the angle between them.
	 * @tparam T The vectors' underlying type.
	 * @param lhs The left hand side of the cross product.
	 * @param rhs The right hand side of the cross product.
	 * @return The cross product of the two vectors.
	 * */
	template <typename T>
	vec<3,T> cross(const vec<3,T>& lhs,const vec<3,T>& rhs);

	/*!
	 * @brief Calculates the length of a vector squared.
	 * @tparam The vectors' underlying type.
	 * @param vector The vector whose length squared to find.
	 * @return The length squared.
	 * */
	template <typename T>
	T len_sq(const vec<2,T>& vector);

	/*!
	 * @brief Calculates a vector's length.
	 * @tparam The vectors' underlying type.
	 * @param vector The vector whose length to find.
	 * @return The length.
	 * */
	template <typename T>
	T len(const vec<2,T>& vector);

	/*!
	 * @brief Calculates the normal of a vector.
	 *
	 * A vector's normal is a vector of unit length pointing in the same
	 * direction.
	 * @tparam T The vector's underlying type.
	 * @param vector The vector whose normal to find.
	 * @return The normal.
	 * */
	template <typename T>
	vec<2,T> normal(const vec<2,T>& vector);

	/*!
	 * @brief Normalizes a vector.
	 *
	 * This actually changes the vector passed in, setting
	 * it's elements to that of it's normal.
	 * @tparam T The vector's underlying type.
	 * @param vector The vector to normalize
	 * @return A reference to the normalized vector.
	 * */
	template <typename T>
	vec<2,T>& normalize(vec<2,T>& vector);

	/*!
	 * @brief Calculates a vector's perpendicular.
	 *
	 * Raises a vector counter clockwise to be at a right angle with
	 * the vector passed in.
	 * @tparam T The vector's underlying type.
	 * @param vector The vector whose perpendicular to find.
	 * @return The perpendicular vector.
	 * */
	template <typename T>
	vec<2,T> perp(const vec<2,T>& vector);

	/*!
	 * @brief The hadamard product.
	 * 
	 * The hadamard product of two vectors is another vector with elements
	 * that are simply the product of the two vector's corresponding elements.
	 * (eg. given v0=[x,y] and v1=[s,t] then v0.hadamard(v1)=[x*s,y*t].).
	 * These are often used for color blending.
	 * @tparam T The vectors' underlying type.
	 * @param lhs The left hand side of the product.
	 * @param rhs The right hand side of the product.
	 * @return The hadamard product.
	 * */
	template <typename T>
	vec<2,T> hadamard(const vec<2,T>& lhs,vec<2,T>& rhs);

	/*!
	 * @brief Linearly interpolates two vectors weighted by t.
	 *
	 * A linear interpolation is a kind of blending between two values
	 * assuming one transforms continuously and linearly into the other
	 * as a parameter, t, varies.  When t=0 the return value is a and
	 * when t=1 the return value is b and everything in between.
	 * @tparam T The vectors' underlying type. 
	 * @param a The first vector in the lerp.
	 * @param t The blend amount toward b.
	 * @param b The second vector in the lerp
	 * @return The linear interpolation of the two vectors.
	 * */
	template <typename T>
	vec<2,T> lerp(const vec<2,T>& a,const T& t,const vec<2,T>& b);

	/*!
	 * @}
	 * */
}

#include "dggt_math_vec3.inl"

namespace dggt
{
	/*!
	 * @addtogroup lin
	 * @{
	 * */

	/*!
	 * @brief Another way to express the type vec<3,T>.
	 * */
	template <typename T>
	using vec3=vec<3,T>;

	/*!
	 * @brief Another way to express the type vec<3,real32>.
	 * */
	typedef vec<3,real32> vec3f;

	/*!
	 * @brief A 3D vector with just it's x value set to T(1).
	 * @tparam T The vector's underlying type.
	 * */
	template <typename T>
	static const vec<3,T> VEC3_XAXIS=vec<3,T>(T(1),T(0),T(0));

	/*!
	 * @brief A 3D vector with just it's y value set to T(1).
	 * @tparam T The vector's underlying type.
	 * */
	template <typename T>
	static const vec<3,T> VEC3_YAXIS=vec<3,T>(T(0),T(1),T(0));

	/*!
	 * @brief A 3D vector with just it's z value set to T(1).
	 * @tparam T The vector's underlying type.
	 * */
	template <typename T>
	static const vec<3,T> VEC3_ZAXIS=vec<3,T>(T(0),T(0),T(1));

	/*!
	 * @brief Another way to write VEC3_YAXIS.
	 * */
	template <typename T>
	static const vec<3,T> VEC3_UP=vec<3,T>(T(0),T(1),T(0));

	/*!
	 * @brief Another way to write VEC3_XAXIS.
	 * */
	template <typename T>
	static const vec<3,T> VEC3_RIGHT=vec<3,T>(T(1),T(0),T(0));

	/*!
	 * @brief Another way to write VEC3_ZAXIS.
	 * */
	template <typename T>
	static const vec<3,T> VEC3_FORWARD=vec<3,T>(T(0),T(0),T(1));

	/*!
	 * @brief A 3D vector with x, y and z set to T(1).
	 * @tparam T The vector's underlying type.
	 * */
	template <typename T>
	static const vec<3,T> VEC3_ONE=vec<3,T>(T(1),T(1),T(1));

	/*!
	 * @brief A 3D vector with both elements set to T(0).
	 * */
	template <typename T>
	static const vec<3,T> VEC3_ZERO=vec<3,T>();

	/*!
	 * @}
	 * */
}

/*! @cond IncludeGuard */
#define _DGGT_MATH_VEC3_H_
#endif
/*! @endcond */
