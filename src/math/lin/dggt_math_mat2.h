/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_MAT2_H_
/*! @endcond */

#include "dggt_math_matn.h"

namespace dggt
{
	/*!
	 * @addtogroup lin
	 * @{
	 * */
	/*!
	 * @brief A 2-by-2 matrix struct.
	 * @tparam T The matrix element's type.
	 * */
	template <typename T>
	struct mat<2,2,T>
	{
		/*!
		 * @brief A static const u32 representing the matrix's dimension.
		 * */
		static const uint32 DIM=2;

		/*!
		 * @brief The (0,0)'th element, columns written first.
		 * */
		T m00;

		/*!
		 * @brief The (0,1)'th element, columns written first.
		 * */
		T m01;

		/*!
		 * @brief The (1,0)'th element, columns written first.
		 * */
		T m10;

		/*!
		 * @brief The (1,1)'th element, columns written first.
		 * */
		T m11;

		/*!
		 * @brief The default constructor.
		 *
		 * Each element in the main diagonal is set to T(1) (ie. the 2x2
		 * identity matrix.).
		 * */
		mat();

		/*!
		 * @brief A constructor taking an array of 4 elements to be copied
		 * column-major-wise.
		 * @param The array to copy.
		 * */
		mat(const T e[4]);

		/*!
		 * @brief An explicit constructor taking a scalar value.
		 *
		 * Sets the main diagonal to the desired value.
		 * @param diagonal The value to be set.
		 * @note This constructor is explicit to avoid seemingly nonsensical and confusing statements like mat<2,2,real32> matrix=5.0f.
		 * */
		explicit mat(const T& diagonal);

		/*!
		 * @brief The copy constructor.
		 * @param other The matrix to copy.
		 * */
		mat(const mat& other);

		/*!
		 * @brief A constructor taking each element.
		 *
		 * The parameters have their subscript with column written first.
		 * @param m00 The (0,0)'th element.
		 * @param m01 The (0,1)'th element.
		 * @param m10 The (1,0)'th element.
		 * @param m11 The (1,1)'th element.
		 * */
		mat(const T& m00,const T& m01, const T& m10,const T& m11);

		/*!
		 * @brief Addition operator.
		 *
		 * Adds two matrices together by adding each corresponding element.
		 * @param rhs The right hand side of the '+' symbol.
		 * @return A matrix where every element is the sum of the corresponding elements in the matrix sum.
		 * */
		mat operator+(const mat& rhs) const;

		/*!
		 * @brief Subtraction operator.
		 *
		 * Subtracts two matrices together by subtracting each corresponding element.
		 * @param rhs The right hand side of the '-' symbol.
		 * @return A matrix where every element is the difference of the corresponding elements in the matrix difference.
		 * */
		mat operator-(const mat& rhs) const;

		/*!
		 * @brief Scaling operator.
		 *
		 * Scales a matrix by multiplying every element with a scalar value.
		 * @param scalar The value of type T used to scale the matrix.
		 * @return The scaled matrix.
		 * */
		mat operator*(const T& scalar) const;

		/*!
		 * @brief Matrix multiplication.
		 *
		 * Multiplies two 2-by-2 matrices, lhs and rhs, to produce a product, S where S=lhs*rhs.  Matrix multiplication is defined such that the i'th
		 * row and the j'th element of the product is equal to the dot product of the left hand side's row vectors with the right hand side's column vectors.
		 * (ie. S[j,i] (columns written first) is equal to lhs_row[i].dot(rhs_col[j]) where lhs_row and rhs_col are the i'th row of the left hand matrix and the j'th
		 * column of the right hand matrix, respectively.).
		 * @note In general A*B!=B*A for matrices A and B.
		 * @return The matrix product.
		 * */
		mat operator*(const mat& rhs) const;

		/*!
		 * @brief Assignment operator.
		 * @param rhs The source matrix in the assignment.
		 * @return A reference to the assigned matrix.
		 * */
		mat& operator=(const mat& rhs);

		/*!
		 * @brief Addition assignment operator.
		 * 
		 * Adds a matrix then assigns the result.
		 * @param rhs The matrix to add.
		 * @return A reference to the added and assigned matrix.
		 * */
		mat& operator+=(const mat& rhs);

		/*!
		 * @brief Subtraction assignment operator.
		 * 
		 * Subtracts a matrix then assigns the result.
		 * @param rhs The matrix to subtract.
		 * @return A reference to the subtracted and assigned matrix.
		 * */
		mat& operator-=(const mat& rhs);

		/*!
		 * @brief Scale assignment operator.
		 * 
		 * Scales a matrix then assigns the result.
		 * @param scalar The scalar of type to.
		 * @return A reference to the scaled and assigned matrix.
		 * */
		mat& operator*=(const T& scalar);

		/*!
		 * @brief Multiply and assignment operator.
		 *
		 * Multiplies and assigns the result.  (ie. short hand for A=A*B.).
		 * @param rhs The matrix to multiply.
		 * @return A reference to the multiplied and assigned matrix.
		 * */
		mat& operator*=(const mat& rhs);

		/*!
		 * @brief Transformation operator.
		 *
		 * Transforms a vector by a matrix and returns the transformed vector.
		 * Vector/matrix multiplication (ie. v'=A*v where A is a transformation
		 * matrix, v is a vector and v' is a vector such that:  
		 * v'[i]=v.dot(mat_row[i]) where mat_row[i] is the i'th row vector
		 * of A.  We can also say the transformed vector is a linear combination
		 * of all the columns of A where the elements of v are scaling factors).
		 * @param vector The vector to transform.
		 * @return The transformed vector.
		 * */
		vec<2,T> transform(const vec<2,T>& vector) const;

		/*!
		 * @brief Returns a pointer to the element array.
		 *
		 * Used for passing the matrix's element array to other libraries.
		 * @return A pointer to the first element in the array.
		 * */
		T* data() { return &m00; }

		/*!
		 * @brief Returns a const pointer to the element array.
		 *
		 * Used for passing the matrix's element array to other libraries.
		 * @return A const pointer to the first element in the array.
		 * */
		const T* data() const { return &m00; }

		/*!
		 * @brief Transpose operator.
		 *
		 * The transpose of a matrix simply switches rows for columns.
		 * @return A 2-by-2 matrix which is the transpose of original matrix.
		 * */
		mat transpose() const;

		/*!
		 * @brief The determinant operator.
		 *
		 * A matrix's determinant is a value used in finding a matrix's inverse
		 * and if the inverse exists (An 2-by-N matrix is invertable if and
		 * only if it's determinant is nonzero.).  In the 2-by-2 case where
		 * A = <br>
		 * [ a b ] <br>
		 * [ c d ] <br>
		 * then det(A)=a*d-b*c.
		 * @return The determinant of type T.
		 * */
		T determinant() const;

		/*!
		 * @brief An alternate way to write determinant.
		 * @return The determinant of type T.
		 * */
		T det() const;

		/*!
		 * @brief The inverse operator.
		 *
		 * If the matrix's determinant is nonzero then this returns a matrix
		 * whose elements are defined and
		 * mat*mat.inverse()=mat.inverse*mat=MAT2_IDENTITY<T>.  If the
		 * determinant is zero, it's elements are NaN (if T supports NaN.).
		 * In the 2-by-2 case where A = <br>
		 * [ a b ] <br>
		 * [ c d ] <br>
		 * and det(A)=m then A^(-1)= <br>
		 * [  d/m -b/m ] <br>
		 * [ -c/m  a/m ] <br>
		 * @return The inverse.
		 * */
		mat inverse() const;

		/*!
		 * @brief Inverts the matrix.
		 *
		 * This function will change the matrix you call it on setting it's
		 * elements to that of it's inverse (if it exists.).
		 * @return A reference to the now inverted matrix.
		 * */
		mat& invert();

		/*!
		 * @brief Gets an element.
		 * @param An unsigned integer representing the desired column equal to 0 or 1.
		 * @param An unsigned integer representing he desired row equal to 0 or 1. 
		 * @return A reference to the matrix's column'th, row'th element.
		 * */
		T& get(uint32 column,uint32 row);

		/*!
		 * @brief Gets a const reference to an element.
		 * @param An unsigned integer representing the desired column equal to 0 or 1.
		 * @param An unsigned integer representing he desired row from equal to 0 to 1. 
		 * @return A const reference to the matrix's column'th, row'th element.
		 * */
		const T& get(uint32 column,uint32 row) const;

		/*!
		 * @brief Gets a column vector.
		 *
		 * The elements of the vector are copies of the matrix's corresponding column's elements.
		 * @param index A u32 representing the desired column equal to 0 or 1.
		 * @return A column vector containing copies of the matrix's corresponding index'th column's elements.
		 * */
		vec<2,T> get_column(uint32 index) const;

		/*!
		 * @brief Gets a row vector.
		 *
		 * The elements of the vector are copies of the matrix's corresponding row's elements.
		 * @param index A u32 representing the desired row ranging from 0 to N-1.
		 * @return A row vector containing copies of the matrix's corresponding index'th row's elements.
		 * */
		vec<2,T> get_row(uint32 index) const;

		/*!
		 * @brief Sets a column.
		 * @param column A u32 representing the column to set ranging from 0 to N-1.
		 * @param val A const reference to a vector of type vec<N,T> (N elements of type T) representing the desired column to set.
		 * @return A reference to the newly transformed matrix.
		 * */
		mat& set_column(uint32 column,const vec<2,T>& val);

		/*!
		 * @brief Sets a row.
		 * @param row A u32 representing the row to set ranging from 0 to N-1.
		 * @param val A const reference to a vector of type vec<N,T> (N elements of type T) representing the desired row to set.
		 * @return A reference to the newly transformed matrix.
		 * */
		mat& set_row(uint32 row,const vec<2,T>& val);
	};

	/*!
	 * @brief Vector/matrix multiplication operator.
	 *
	 * Transforms a vector by a matrix.
	 * @tparam N A u32 representing the dimension of the vector and the number of columns of the transformation matrix.
	 * @tparam T The type of the vector's and matrix's elements.
	 * @param vector The vector to transform.
	 * @param matrix The transformation matrix.
	 * @return The transformed vector.
	 * */
	template <typename T>
	vec<2,T> operator*(const vec<2,T>& vector,const mat<2,2,T>& matrix);

	/*!
	 * @brief Matrix scaling operator.
	 *
	 * Scales a matrix by a scalar.
	 * @tparam N A u32 representing the dimension of the matrix.
	 * @tparam T The type of the scalar and the matrix's elements.
	 * @param scalar A const reference to a scalar of type T representing the scaling factor.
	 * @param matrix A const reference to the matrix to scale.
	 * @return The scaled matrix.
	 * */
	template <typename T>
	mat<2,2,T> operator*(const T& scalar,const mat<2,2,T>& matrix);
	/*!
	 * @}
	 * */
}

#include "dggt_math_mat2.inl"

namespace dggt
{
	/*!
	 * @addtogroup lin
	 * @{
	 * */

	/*!
	 * @brief A 2-by-2 identity matrix.
	 * @tparam T The matrix's underlying type.
	 * */
	template <typename T>
	static const mat<2,2,T> MAT2_IDENTITY=mat<2,2,T>(T(1));

	/*!
	 * @brief Short hand for mat<2,2,T>.
	 * @tparam T The matrix's underlying type.
	 * */
	template <typename T>
	using mat2=mat<2,2,T>;

	/*!
	 * @brief Another way to write mat<2,2,real32>.
	 * */
	typedef mat2<real32> mat2f;

	/*!
	 * @}
	 * */
}

/*! @cond IncludeGuard */
#define _DGGT_MATH_MAT2_H_
#endif
/*! @endcond */
