#ifndef _DGGT_MATH_MAT4_H_

#include "dggt_math_matn.h"

namespace dggt
{
	template <typename T>
	struct mat<4,4,T>
	{
		static const uint32 DIM=4;
		T m00;
		T m01;
		T m02;
		T m03;

		T m10;
		T m11;
		T m12;
		T m13;

		T m20;
		T m21;
		T m22;
		T m23;

		T m30;
		T m31;
		T m32;
		T m33;

		mat(const T e[16]);
		explicit mat(const T& diagonal);
		mat(const mat& other);
		mat();
		mat(const T& m00,const T& m01,const T& m02,const T& m03,
				const T& m10,const T& m11,const T& m12,const T& m13,
				const T& m20,const T& m21,const T& m22,const T& m23,
				const T& m30,const T& m31,const T& m32,const T& m33);

		mat<3,3,T> minor(uint32 column,uint32 row) const;
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

		vec<4,T> transform(const vec<4,T>& vector) const;

		T* data() { return &m00; }
		const T* data() const { return &m00; }

		mat transpose() const;
		T determinant() const;
		T det() const;
		mat inverse() const;
		mat& invert();

		T& get(uint32 column,uint32 row);
		const T& get(uint32 column,uint32 row) const;
		vec<4,T> get_column(uint32 index) const;
		vec<4,T> get_row(uint32 index) const;
		mat& set_column(uint32 column,const vec<4,T>& val);
		mat& set_row(uint32 row,const vec<4,T>& val);
	};

	template <typename T>
	vec<4,T> operator*(const vec<4,T>& vector,const mat<4,4,T>& matrix);
	template <typename T>
	mat<4,4,T> operator*(const T& scalar,const mat<4,4,T>& matrix);


	template <typename T>
	mat<4,4,T> translation_mat(const vec<3,T>& translation);
	template <typename T>
	mat<4,4,T> translation_mat(const vec<2,T>& translation);
	template <typename T>
	mat<4,4,T> scale_mat(const vec<3,T>& scale);
	template <typename T>
	mat<4,4,T> scale_mat(const vec<2,T>& scale);
	template <typename T>
	mat<4,4,T> scale_mat(const T& scalar);
	template <typename T>
	mat<4,4,T> axis_angle_mat(const vec<3,T>& axis,const T& angle);

	template <typename T>
	mat<4,4,T> view_mat(const vec<3,T>& cameraPos,
			const vec<3,T>& cameraForward,
			const vec<3,T>& cameraUp,
			const vec<3,T>& cameraRight);

	template <typename T>
	mat<4,4,T> ortho_mat(const T& left,const T& right,
			const T& bottom,const T& top,
			const T& near,const T& far);

	template <typename T>
	mat<4,4,T> ortho_mat(const T& width,const T& height,
			const T& near,const T& far);

	template <typename T>
	mat<4,4,T> proj_mat(const T& left,const T& right,
			const T& bottom,const T& top,
			const T& near,const T& far);
	template <typename T>
	mat<4,4,T> proj_mat(const T& width,const T& height,
			const T& near,const T& far);

}

#include "dggt_math_mat4.inl"

namespace dggt
{
	template <typename T>
	static const mat<4,4,T> MAT4_IDENTITY=mat<4,4,T>(T(1));

	template <typename T>
	using mat4=mat<4,4,T>;

	typedef mat4<real32> mat4f;
}

#define _DGGT_MATH_MAT4_H_
#endif
