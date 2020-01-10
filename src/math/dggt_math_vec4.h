#ifndef _DGGT_MATH_VEC4_H_

#include "dggt_math_vec.h"

template <typename T>
struct vec<4,T>
{
	static const uint32 DIM=4;

	T x;
	T y;
	T z;
	T w;

	vec(const T elements[4]);
	explicit vec(const T& val);
	vec();
	vec(const T& x,const T& y,const T& z,const T& w);
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

	T& operator[](uint32 index);
	const T& operator[](uint32 index) const;

	T len_sq() const;
	T len() const;

	vec normal() const;
	vec& normalize();

	T dot(const vec& rhs) const;
	vec hadamard(const vec& rhs) const;
	vec lerp(const T& t,const vec& b) const;
	T* data() { return &x;}
	const T* data() const { return &x;}
};

template <typename T>
static const vec<4,T> VEC4_ONE=vec<4,T>(T(1));
template <typename T>
static const vec<4,T> VEC4_XAXIS=vec<4,T>(T(1),T(0),T(0),T(0));
template <typename T>
static const vec<4,T> VEC4_YAXIS=vec<4,T>(T(0),T(1),T(0),T(0));
template <typename T>
static const vec<4,T> VEC4_ZAXIS=vec<4,T>(T(0),T(0),T(1),T(0));
template <typename T>
static const vec<4,T> VEC4_WAXIS=vec<4,T>(T(0),T(0),T(0),T(1));

template <typename T>
vec<4,T> operator*(const T& scalar,const vec<4,T>& vector);

template <typename T>
T dot(const vec<4,T>& lhs,const vec<4,T>& rhs);

template <typename T>
T len_sq(const vec<4,T>& vector);

template <typename T>
T len(const vec<4,T>& vector);

template <typename T>
vec<4,T> hadamard(const vec<4,T>& lhs,vec<4,T>& rhs);

template <typename T>
vec<4,T> lerp(const vec<4,T>& a,const T& t,const vec<4,T>& b);

#include "dggt_math_vec4.inl"

template <typename T>
using vec4=vec<4,T>;

typedef vec4<real32> vec4f;

#define _DGGT_MATH_VEC4_H_
#endif
