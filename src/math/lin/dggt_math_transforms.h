
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

	/*!
	 * @brief Creates a translation matrix.
	 * @param translation A vector representing a 3-dimensional translation.
	 * @return The translation matrix.
	 * */
	template <typename T>
	mat<4,4,T> translation_mat(const vec<3,T>& translation);

	/*!
	 * @brief Creates a translation matrix.
	 * @param translation A vector representing a 2-dimensional translation.
	 * @return The translation matrix.
	 * */
	template <typename T>
	mat<4,4,T> translation_mat(const vec<2,T>& translation);

	/*!
	 * @brief Creates a scale matrix.
	 * @param scale A vector representing the scaling factors in 3 dimensions.
	 * @return The scale matrix.
	 * */
	template <typename T>
	mat<4,4,T> scale_mat(const vec<3,T>& scale);

	/*!
	 * @brief Creates a scale matrix.
	 * @param scale A vector representing the scaling factors in 2 dimensions.
	 * @return The scale matrix.
	 * */
	template <typename T>
	mat<4,4,T> scale_mat(const vec<2,T>& scale);

	/*!
	 * @brief Creates a scale matrix.
	 * @param scalar The amount to scale along all axis.
	 * @return The scale matrix.
	 * */
	template <typename T>
	mat<4,4,T> scale_mat(const T& scalar);

	/*!
	 * @brief Creates a rotation matrix.
	 * @param axis The axis about which rotation will take place.
	 * @param angle The amount, in radians, to rotate in a counter clockwise direction
	 * (negative values for clockwise rotations.).
	 * @return The rotation matrix.
	 * */
	template <typename T>
	mat<4,4,T> axis_angle_mat(const vec<3,T>& axis,const T& angle);

	/*!
	 * @brief Creates a view matrix. (ie. camera or look-at matrix).
	 *
	 * In graphics, instead of moving a camera, we transform the world to
	 * move in the opposite direction.  This gives the illusion of camera
	 * work.  The parameters have a few restrictions:  If they aren't unit
	 * vectors they'll be normalized so they must be non-zero and they have
	 * to all be at right angles to each other.
	 * @param cameraPos The position of the camera.
	 * @param cameraForward The direction the camera is pointed.
	 * @param cameraUp The direction representing which way up the camera is by passing it's local 'up' coordinate.
	 * @param cameraRight The direction pointing to the camera's right
	 * @return The view matrix.
	 * */
	template <typename T>
	mat<4,4,T> view_mat(const vec<3,T>& cameraPos,
			const vec<3,T>& cameraForward,
			const vec<3,T>& cameraUp,
			const vec<3,T>& cameraRight);

	/*!
	 * @brief Creates an orthographic projection matrix.
	 *
	 * Orthographic projection is like normal projection except objects don't
	 * get smaller as they get further away from the camera.  Because of this
	 * they're often used in 2D games.  All the parameters represent the
	 * extents of the 'camera box' (ie. A box within which, everything is
	 * visible to the camera).
	 * @param left The left plane coordinate.
	 * @param right The right plane coordinate.
	 * @param bottom The bottom plane coordinate.
	 * @param top The top plane coordinate.
	 * @param near The near plane coordinate (nearest to the camera.).
	 * @param far The far plane coordinate (furthest from the camera.).
	 * @return The ortho matrix.
	 * */
	template <typename T>
	mat<4,4,T> ortho_mat(const T& left,const T& right,
			const T& bottom,const T& top,
			const T& near,const T& far);

	/*!
	 * @brief Creates an orthographic projection matrix.
	 *
	 * Orthographic projection is like normal projection except objects don't
	 * get smaller as they get further away from the camera.  Because of this
	 * they're often used in 2D games.  All the parameters represent the
	 * extents of the 'camera box' (ie. A box within which, everything is
	 * visible to the camera).
	 * @param width The camera box's width.
	 * @param height The camera box's height.
	 * @param near The near plane coordinate (nearest to the camera.).
	 * @param far The far plane coordinate (furthest from the camera.).
	 * @return The ortho matrix.
	 * */
	template <typename T>
	mat<4,4,T> ortho_mat(const T& width,const T& height,
			const T& near,const T& far);

	/*!
	 * @brief Creates a projection matrix.
	 *
	 * The main difference between normal projection and orthographic
	 * projection is in the ortho case a box is used and in the normal case
	 * a fustrum (a square-base pyramid with it's tip cut off.).  All the
	 * parameters represent the extents of the part of the fustrum closest
	 * to the camera.
	 * @param left The left fustrum coordinate.
	 * @param right The right fustrum coordinate.
	 * @param bottom The bottom fustrum coordinate.
	 * @param top The top fustrum coordinate.
	 * @param near The near plane.
	 * @param far The far plane.
	 * */
	template <typename T>
	mat<4,4,T> proj_mat(const T& left,const T& right,
			const T& bottom,const T& top,
			const T& near,const T& far);

	/*!
	 * @brief Creates a projection matrix.
	 *
	 * The main difference between normal projection and orthographic
	 * projection is in the ortho case a box is used and in the normal case
	 * a fustrum (a square-base pyramid with it's tip cut off.).  All the
	 * parameters represent the extents of the part of the fustrum closest
	 * to the camera.
	 * @param width The fustrum width.
	 * @param height The fustrum height.
	 * @param near The near plane.
	 * @param far The far plane.
	 * */
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
