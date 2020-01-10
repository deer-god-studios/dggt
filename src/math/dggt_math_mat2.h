#ifndef _DGGT_MATH_MAT2_H_

#include "dggt_math_matn.h"

template <typename T>
struct mat<2,2,T>
{
	static const uint32 DIM=2;
	T m00;
	T m01;
	T m10;
	T m11;

	mat(const T e[4]);
	explicit mat(const T& diagonal);
	mat(const mat& other);
	mat();
	mat(const T& m00,const T& m01, const T& m10,const T& m11);

	mat operator+(const mat& rhs) const;
	mat operator-(const mat& rhs) const;
	mat operator*(const T& scalar) const;
	mat operator*(const mat& rhs) const;

	mat& operator=(const mat& rhs);
	mat& operator+=(const mat& rhs);
	mat& operator-=(const mat& rhs);
	mat& operator*=(const T& scalar);
	mat& operator*=(const mat& rhs);

	vec<2,T> transform(const vec<2,T>& vector) const;

	T* data() { return &m00; }
	const T* data() const { return &m00; }

	mat transpose() const;
	T determinant() const;
	T det() const;
	mat inverse() const;
	mat& invert();

	T& get(uint32 column,uint32 row);
	const T& get(uint32 column,uint32 row) const;
	vec<2,T> get_column(uint32 index) const;
	vec<2,T> get_row(uint32 index) const;
	mat& set_column(uint32 column,const vec<2,T>& val);
	mat& set_row(uint32 row,const vec<2,T>& val);
};

template <typename T>
vec<2,T> operator*(const vec<2,T>& vector,const mat<2,2,T>& matrix);
template <typename T>
mat<2,2,T> operator*(const T& scalar,const mat<2,2,T>& matrix);

#include "dggt_math_mat2.inl"

template <typename T>
static const mat<2,2,T> MAT2_IDENTITY=mat<2,2,T>(T(1));

template <typename T>
using mat2=mat<2,2,T>;

typedef mat2<real32> mat2f;

#define _DGGT_MATH_MAT2_H_
#endif
