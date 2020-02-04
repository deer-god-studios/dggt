
/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_MAT_H_
/*! @endcond */

#include "dggt_math_vec.h"

namespace dggt
{
	/*!
	 * @brief A matrix struct with C columns and R rows of elements of type T.
	 * @tparam C An integer representing the number of columns.
	 * @tparam R An integer representing the  number of rows.
	 * @tparam T A type, usually a numeric type.  Each element in the matrix will be of this type.  T must be a type that overloads basic arithmetic operations. 
	 * */
	template <uint32 C,uint32 R,typename T>
	struct mat
	{
		/*!
		 * @brief A static const unsigned integer representing the number of columns in the matrix.
		 * */
		static const uint32 COLUMNS=C;

		/*!
		 * @brief A static const unsigned integer representing the number of rows in the matrix.
		 * */
		static const uint32 ROWS=R;

		/*!
		 * @brief The underlying array containing all the matrix's elements.
		 *
		 * The array's memory layout is column-major to be in accordance with OpenGL's.
		 * */
		T e[C*R];

		/*!
		 * @breif Default constructor.
		 *
		 * Initialized all elements to T(0).
		 * */
		mat();

		/*!
		 * @brief Constructor taking an array.
		 *
		 * Initialized the elements by copying every element in the given array
		 * @param e[C*R] An array of elements to be copied into the matrix's internal array.
		 * */
		mat(const T e[C*R]);

		/*!
		 * @brief Copy constructor.
		 * @param other The matrix to copy.
		 * */
		mat(const mat& other);

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
		 * Multiplies two matrices, lhs<C,R,T> and rhs<R,M,T>, to produce a product, S<C,M,T> where S=lhs*rhs.  Matrix multiplication is defined such that the i'th
		 * row and the j'th element of the product is equal to the dot product of the left hand side's row vectors with the right hand side's column vectors.
		 * (ie. S[j,i] (columns written first) is equal to lhs_row[i].dot(rhs_col[j]) where lhs_row and rhs_col are the i'th row of the left hand matrix and the j'th
		 * column of the right hand matrix, respectively.).
		 * @note In general A*B!=B*A for matrices A and B.
		 * @tparam M An unsigned integer representing the number of rows in the right hand side of the product.
		 * @param rhs A matrix with R columns and M rows.
		 * @return The matrix product.
		 * */
		template <uint32 M>
		mat<C,M,T> operator*(const mat<R,M,T>& rhs) const;

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
		 * @tparam M A u32 representing the number of rows of the right hand side of the multiplication.
		 * @param rhs The matrix to multiply.
		 * @return A reference to the multiplied and assigned matrix.
		 * */
		template <uint32 M>
		mat<C,M,T>& operator*=(const mat<R,M,T>& rhs);

		/*!
		 * @brief Transformation operator.
		 *
		 * Transforms a vector by a matrix and returns the transformed vector.
		 * Vector/matrix multiplication (ie. v'=A*v where A is a transformation
		 * matrix, v is a vector and v' is a vector such that:  
		 * v'[i]=v.dot(mat_row[i]) where mat_row[i] is the i'th row vector
		 * of A.  We can also say the transformed vector is a linear combination
		 * of all the columns of A where the elements of v are scaling factors).
		 * @param vector A vector of dimension C.
		 * @return The transformed vector of dimension R. 
		 * */
		vec<R,T> transform(const vec<C,T>& vector) const;

		/*!
		 * @brief Returns a pointer to the element array.
		 *
		 * Used for passing the matrix's element array to other libraries.
		 * @return A pointer to the first element in the array.
		 * */
		T* data() { return e; }

		/*!
		 * @brief Returns a const pointer to the element array.
		 *
		 * Used for passing the matrix's element array to other libraries.
		 * @return A const pointer to the first element in the array.
		 * */
		const T* data() const { return e; }

		/*!
		 * @brief Transpose operator.
		 *
		 * The transpose of a matrix simply switches rows for columns.
		 * @return A matrix with R columns and C rows which is the transpose of original matrix.
		 * */
		mat<R,C,T> transpose() const;

		/*!
		 * @brief Gets an element.
		 * @param An unsigned integer representing the desired column ranging from 0 to C-1.
		 * @param An unsigned integer representing he desired row from ranging from 0 to R-1. 
		 * @return A reference to the matrix's column'th, row'th element.
		 * */
		T& get(uint32 column,uint32 row);

		/*!
		 * @brief Gets a const reference to an element.
		 * @param An unsigned integer representing the desired column ranging from 0 to C-1.
		 * @param An unsigned integer representing he desired row from ranging from 0 to R-1. 
		 * @return A const reference to the matrix's column'th, row'th element.
		 * */
		const T& get(uint32 column,uint32 row) const;

		/*!
		 * @brief Gets a column vector.
		 *
		 * The elements of the vector are copies of the matrix's corresponding column's elements.
		 * @param index A u32 representing the desired column ranging from 0 to R-1.
		 * @return A column vector containing copies of the matrix's corresponding index'th column's elements.
		 * */
		vec<R,T> get_column(uint32 index) const;

		/*!
		 * @brief Gets a row vector.
		 *
		 * The elements of the vector are copies of the matrix's corresponding row's elements.
		 * @param index A u32 representing the desired row ranging from 0 to C-1.
		 * @return A row vector containing copies of the matrix's corresponding index'th row's elements.
		 * */
		vec<C,T> get_row(uint32 index) const;

		/*!
		 * @brief Sets a column.
		 * @param column A u32 representing the column to set ranging from 0 to R-1.
		 * @param val A const reference to a vector of type vec<R,T> (R elements of type T) representing the desired column to set.
		 * @return A reference to the newly transformed matrix.
		 * */
		mat& set_column(uint32 column,const vec<R,T>& val);

		/*!
		 * @brief Sets a row.
		 * @param row A u32 representing the row to set ranging from 0 to C-1.
		 * @param val A const reference to a vector of type vec<C,T> (C elements of type T) representing the desired row to set.
		 * @return A reference to the newly transformed matrix.
		 * */
		mat& set_row(uint32 row,const vec<C,T>& val);
	};

	/*!
	 * @brief Vector/matrix multiplication operator.
	 *
	 * Transforms a vector by a matrix.
	 * @tparam C A u32 representing the dimension of the vector and the number of columns of the transformation matrix.
	 * @tparam R A u32 representing the dimension of the resulting vector and the number of rows of the transformation matrix.
	 * @tparam T The type of the vector's and matrix's elements.
	 * @param vector The vector to transform.
	 * @param matrix The transformation matrix.
	 * @return The transformed vector.
	 * */
	template <uint32 C,uint32 R,typename T>
	vec<R,T> operator*(const vec<C,T>& vector,const mat<C,R,T>& matrix);

	/*!
	 * @brief Matrix scaling operator.
	 *
	 * Scales a matrix by a scalar.
	 * @tparam C A u32 representing the number of columns.
	 * @tparam R A u32 representing the number of row.
	 * @tparam T The type of the scalar and the matrix's elements.
	 * @param scalar A const reference to a scalar of type T representing the scaling factor.
	 * @param matrix A const reference to the matrix to scale.
	 * @return The scaled matrix.
	 * */
	template <uint32 C,uint32 R,typename T>
	mat<C,R,T> operator*(const T& scalar,const mat<C,R,T>& matrix);
}

#include "dggt_math_mat.inl"

/*! @cond IncludeGuard */
#define _DGGT_MATH_MAT_H_
#endif
/*! @endcond */
