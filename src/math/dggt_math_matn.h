#ifndef _DGGT_MATH_MATN_H_

#include "dggt_math_mat.h"

template <uint32 N,typename T>
struct mat<N,N,T>
{
	static const uint32 DIM=N;

	T e[N*N];

	mat(const T e[N*N]);
	explicit mat(const T& diagonal);
	mat(const mat& other);
	mat();

	mat operator+(const mat& rhs) const;
	mat operator-(const mat& rhs) const;
	mat operator*(const T& scalar) const;
	mat operator*(const mat& rhs) const;

	mat& operator=(const mat& rhs);
	mat& operator+=(const mat& rhs);
	mat& operator-=(const mat& rhs);
	mat& operator*=(const T& scalar);
	mat& operator*=(const mat& rhs);

	vec<N,T> transform(const vec<N,T>& vector) const;

	T* data() { return e; }
	const T* data() const { return e; }

	mat<N-1,N-1,T> minor(uint32 columnToRemove,uint32 rowToRemove) const;
	mat comatrix() const;
	mat transpose() const;
	T determinant() const;
	T det() const;
	mat inverse() const;
	mat& invert();

	T& get(uint32 column,uint32 row);
	const T& get(uint32 column,uint32 row) const;
	vec<N,T> get_column(uint32 index) const;
	vec<N,T> get_row(uint32 index) const;
	mat& set_column(uint32 column,const vec<N,T>& val);
	mat& set_row(uint32 row,const vec<N,T>& val);
};

template <uint32 N,typename T>
vec<N,T> operator*(const vec<N,T>& vector,const mat<N,N,T>& matrix);
template <uint32 N,typename T>
mat<N,N,T> operator*(const T& scalar,const mat<N,N,T>& matrix);

#include "dggt_math_matn.inl"

template <uint32 N,typename T>
static const mat<N,N,T> MATN_IDENTITY=mat<N,N,T>(T(1));
template <uint32 N,typename T>
static const mat<N,N,T> MAT_IDENTITY=mat<N,N,T>(T(1));

template <uint32 N,typename T>
using matn=mat<N,N,T>;

#define _DGGT_MATH_MATN_H_
#endif
