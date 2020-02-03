#ifndef _DGGT_MATH_VEC3_H_

#include "dggt_math_vec.h"

namespace dggt
{
	template <typename T>
	struct vec<3,T>
	{
		static const uint32 DIM=3;

		T x;
		T y;
		T z;

		vec(const T elements[3]);
		explicit vec(const T& val);
		vec();
		vec(const T& x,const T& y,const T& z);
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

		T dot(const vec& rhs) const;
		vec cross(const vec& rhs) const;

		T len_sq() const;
		T len() const;

		vec normal() const;
		vec& normalize();
		vec hadamard(const vec& rhs) const;
		vec lerp(const T& t,const vec& b) const;
		T* data() {return &x; }
		const T* data() const {return &x;}
	};

	template <typename T>
	static const vec<3,T> VEC3_ONE=vec<3,T>(T(1));
	template <typename T>
	static const vec<3,T> VEC3_XAXIS=vec<3,T>(T(1),T(0),T(0));
	template <typename T>
	static const vec<3,T> VEC3_YAXIS=vec<3,T>(T(0),T(1),T(0));
	template <typename T>
	static const vec<3,T> VEC3_ZAXIS=vec<3,T>(T(0),T(0),T(1));

	template <typename T>
	vec<3,T> operator*(const T& scalar,const vec<3,T>& vector);

	template <typename T>
	T dot(const vec<3,T>& lhs,const vec<3,T>& rhs);

	template <typename T>
	vec<3,T> cross(const vec<3,T>& lhs,const vec<3,T>& rhs);

	template <typename T>
	T len_sq(const vec<2,T>& vector);

	template <typename T>
	T len(const vec<2,T>& vector);

	template <typename T>
	vec<2,T> normal(const vec<2,T>& vector);

	template <typename T>
	vec<2,T>& normalize(vec<2,T>& vector);

	template <typename T>
	vec<2,T> perp(const vec<2,T>& vector);

	template <typename T>
	vec<2,T> hadamard(const vec<2,T>& lhs,vec<2,T>& rhs);

	template <typename T>
	vec<2,T> lerp(const vec<2,T>& a,const T& t,const vec<2,T>& b);
}
#include "dggt_math_vec3.inl"

namespace dggt
{
	template <typename T>
	using vec3=vec<3,T>;

	typedef vec<3,real32> vec3f;

	template <typename T>
	static const vec<3,T> VEC3_XAXIS=vec<3,T>(T(1),T(0),T(0));
	template <typename T>
	static const vec<3,T> VEC3_YAXIS=vec<3,T>(T(0),T(1),T(0));
	template <typename T>
	static const vec<3,T> VEC3_ZAXIS=vec<3,T>(T(0),T(0),T(1));
	template <typename T>
	static const vec<3,T> VEC3_UP=vec<3,T>(T(0),T(1),T(0));
	template <typename T>
	static const vec<3,T> VEC3_RIGHT=vec<3,T>(T(1),T(0),T(0));
	template <typename T>
	static const vec<3,T> VEC3_FORWARD=vec<3,T>(T(0),T(0),T(1));
	template <typename T>
	static const vec<3,T> VEC3_ONE=vec<3,T>(T(1),T(1),T(1));
	template <typename T>
	static const vec<3,T> VEC3_ZERO=vec<3,T>();
}
#define _DGGT_MATH_VEC3_H_
#endif
