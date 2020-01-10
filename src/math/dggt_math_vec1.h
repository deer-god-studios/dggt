#ifndef _DGGT_MATH_VEC1_H_

template <typename T>
struct vec<1,T>
{
	static const uint32 DIM=1;
	T x;

	explicit vec(const T element[1]);
	vec(const T& val);
	vec();
	vec(const vec& other);
	template <uint32 D>
	vec(const vec<D,T>& other);

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

	operator T() const;
	operator T&();
	T& operator[](uint32 index);
	const T& operator[](uint32 index) const;

	T dot(const vec& rhs) const;
};

template <typename T>
static const vec<1,T> VEC1_ONE=vec<1,T>(T(1));
template <typename T>
static const vec<1,T> VEC1_XAXIS=vec<1,T>(T(1));

template <typename T>
vec<1,T> operator*(const T& scalar,const vec<1,T>& vector);

template <typename T>
T dot(const vec<1,T>& lhs,const vec<1,T>& rhs);

#include "dggt_math_vec1.inl"

template <typename T>
using vec1=vec<1,T>;

typedef vec<1,real32> vec1f;

#define _DGGT_MATH_VEC1_H_
#endif
