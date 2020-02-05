
/*! @cond IncludeGuard */
#ifndef _DGGT_MATH_TRANSFORMS_H_
/*! @endcond */

#include "dggt_math_mat4.h"

namespace dggt
{
	/*!
	 * @addtogroup lin
	 * @{
	 * */

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

	/*!
	 * @}
	 * */
}

#include "dggt_math_transforms.inl"

/*! @cond IncludeGuard */
#define _DGGT_MATH_TRANSFORMS_H_
#endif
/*! @endcond */
