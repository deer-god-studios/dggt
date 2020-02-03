#ifndef _DGGT_MATH_MAT3_H_

#include "dggt_math_matn.h"

namespace dggt
{
	template <typename T>
	struct mat<3,3,T>
	{
		static const uint32 DIM=3;
		T m00;
		T m01;
		T m02;
		T m10;
		T m11;
		T m12;
		T m20;
		T m21;
		T m22;

		mat(const T e[9]);
		explicit mat(const T& diagonal);
		mat(const mat& other);
		mat();
		mat(const T& m00,const T& m01, const T& m02,
				const T& m10,const T& m11,const T& m12,
				const T& m20,const T& m21,const T& m22);

		mat<2,2,T> minor(uint32 column,uint32 row) const;
		mat comatrix() const;
		mat operator+(const mat& rhs) const;
		mat operator-(const mat& rhs) const;
		mat operator*(const T& scalar) const;
		mat operator*(const mat& rhs) const;

		mat& operator=(const mat& rhs);
		mat& operator+=(const mat& rhs);
		mat& operator-=(const mat& rhs);
		mat& operator*=(const T& scalar);
		mat& operator*=(const mat& rhs);

		vec<3,T> transform(const vec<3,T>& vector) const;

		T* data() { return &m00; }
		const T* data() const { return &m00; }

		mat transpose() const;
		T determinant() const;
		T det() const;
		mat inverse() const;
		mat& invert();

		T& get(uint32 column,uint32 row);
		const T& get(uint32 column,uint32 row) const;
		vec<3,T> get_column(uint32 index) const;
		vec<3,T> get_row(uint32 index) const;
		mat& set_column(uint32 column,const vec<3,T>& val);
		mat& set_row(uint32 row,const vec<3,T>& val);
	};

	template <typename T>
	vec<3,T> operator*(const vec<3,T>& vector,const mat<3,3,T>& matrix);
	template <typename T>
	mat<3,3,T> operator*(const T& scalar,const mat<3,3,T>& matrix);
}
#include "dggt_math_mat3.inl"

namespace dggt
{
	template <typename T>
	static const mat<3,3,T> MAT3_IDENTITY=mat<3,3,T>(T(1));

	template <typename T>
	using mat3=mat<3,3,T>;

	typedef mat3<real32> mat3f;
}
#define _DGGT_MATH_MAT3_H_
#endif
