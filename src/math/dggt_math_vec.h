#ifndef _DGGT_MATH_VEC_H_

#include "dggt_math_utils.h"

template <uint32 D,typename T>
struct vec
{
	static const uint32 DIM=D;
	T e[D];

	vec(const T elements[D]);
	explicit vec(const T& val);
	vec();
	vec(const vec& other);
	vec(const vec<D-1,T>& other, T last=T(1));
	template <uint32 D2>
	vec(const vec<D2,T>& other);

	vec operator+(const vec& rhs) const;
	vec operator-(const vec& rhs) const;
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
