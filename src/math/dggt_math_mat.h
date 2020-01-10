#ifndef _DGGT_MATH_MAT_H_

#include "dggt_math_vec.h"

template <uint32 C,uint32 R,typename T>
struct mat
{
	static const uint32 COLUMNS=C;
	static const uint32 ROWS=R;

	T e[C*R];

	mat(const T e[C*R]);
	mat(const mat& other);
	mat();

	mat operator+(const mat& rhs) const;
	mat operator-(const mat& rhs) const;
	mat operator*(const T& scalar) const;
	template <uint32 M>
	mat<C,M,T> operator*(const mat<R,M,T>& rhs) const;

	mat& operator=(const mat& rhs);
	mat& operator+=(const mat& rhs);
	mat& operator-=(const mat& rhs);
	mat& operator*=(const T& scalar);
	template <uint32 M>
	mat<C,M,T>& operator*=(const mat<R,M,T>& rhs);

	vec<R,T> transform(const vec<C,T>& vector) const;

	T* data() { return e; }
	const T* data() const { return e; }

	mat<R,C,T> transpose() const;

	T& get(uint32 column,uint32 row);
	const T& get(uint32 column,uint32 row) const;
	vec<R,T> get_column(uint32 index) const;
	vec<C,T> get_row(uint32 index) const;
	mat& set_column(uint32 column,const vec<R,T>& val);
	mat& set_row(uint32 row,const vec<C,T>& val);
};

template <uint32 C,uint32 R,typename T>
vec<R,T> operator*(const vec<C,T>& vector,const mat<C,R,T>& matrix);
template <uint32 C,uint32 R,typename T>
mat<C,R,T> operator*(const T& scalar,const mat<C,R,T>& matrix);

#include "dggt_math_mat.inl"

#define _DGGT_MATH_MAT_H_
#endif
