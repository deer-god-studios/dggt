namespace dggt
{
	template <typename T>
	mat<4,4,T> translation_mat(const vec<3,T>& translation)
	{
		mat<4,4,T> result=MAT_IDENTITY<4,T>;

		vec<4,T> translation4=vec4f(translation.x,translation.y,
				translation.z,1.0f);
		result.set_column(3,translation4);

		return result;
	}

	template <typename T>
	mat<4,4,T> translation_mat(const vec<2,T>& translation)
	{
		vec<3,T> translation3=vec<3,T>(translation.x,translation.y,T(0));
		return translation_mat(translation3);
	}

	template <typename T>
	mat<4,4,T> scale_mat(const vec<3,T>& scale)
	{
		mat<4,4,T> result=MAT_IDENTITY<4,T>;
		vec4f scale4=vec4f(scale.x,scale.y,scale.z,T(1));

		result.set_column(0,scale4.x*result.get_column(0));
		result.set_column(1,scale4.y*result.get_column(1));
		result.set_column(2,scale4.z*result.get_column(2));
		result.set_column(3,scale4.w*result.get_column(3));
		return result;
	}

	template <typename T>
	mat<4,4,T> scale_mat(const vec<2,T>& scale)
	{
		vec<3,T> scale3=vec<3,T>(scale.x,scale.y,T(1));
		return scale_mat(scale3);
	}

	template <typename T>
	mat<4,4,T> scale_mat(const T& scalar)
	{
		vec<4,T> scale=vec<4,T>(scalar,scalar,scalar,scalar);
		return scale_mat(scale);
	}

	template <typename T>
	mat<4,4,T> axis_angle_mat(const vec<3,T>& axis,const T& angle)
	{
		mat<4,4,T> result;
		if (len_sq(axis)!=T(0))
		{
			if (len_sq(axis)!=T(1))
			{
				vec<3,T> nAxis=axis.normal();
				T cosAngle=cosine(angle);
				T sinAngle=sine(angle);
				T axisX=axis.x;
				T axisY=axis.y;
				T axisZ=axis.z;
				T one=T(1);
				T zero=T(0);
				T oneMinusCos=one-cosAngle;

				result.m00=cosAngle+sq(axisX)*oneMinusCos;
				result.m01=axisY*axisX*oneMinusCos+axisZ*sinAngle;
				result.m02=axisZ*axisX*oneMinusCos-axisY*sinAngle;
				result.m03=zero;

				result.m10=axisX*axisY*oneMinusCos-axisZ*sinAngle;
				result.m11=cosAngle+sq(axisY)*oneMinusCos;
				result.m12=axisZ*axisY*oneMinusCos+axisX*sinAngle;
				result.m13=zero;

				result.m20=axisX*axisZ*oneMinusCos+axisY*sinAngle;
				result.m21=axisY*axisZ*oneMinusCos-axisX*sinAngle;
				result.m22=cosAngle+sq(axisZ)*oneMinusCos;
				result.m23=zero;

				result.m30=zero;
				result.m31=zero;
				result.m32=zero;
				result.m33=one;
			}
		}
		return result;
	}

	template <typename T>
	mat<4,4,T> view_mat(const vec<3,T>& cameraPos,
			const vec<3,T>& cameraForward,
			const vec<3,T>& cameraUp,
			const vec<3,T>& cameraRight)
	{

		mat<4,4,T> result;
		vec<3,T> pos=cameraPos;
		vec<3,T> fwd=cameraForward;
		vec<3,T> right=cameraRight;
		vec<3,T> up=cameraUp;

		if (fwd.len_sq())
		{
			fwd.normalize();
		}
		if (right.len_sq())
		{
			fwd.normalize();
		}
		if (up.len_sq())
		{
			up.normalize();
		}
		vec<4,T> pos4=vec<4,T>(pos.x,pos.y,pos.z,T(1));
		vec<4,T> fwd4=vec<4,T>(fwd.x,fwd.y,fwd.z,T(0));
		vec<4,T> up4=vec<4,T>(up.z,up.y,up.z,T(0));
		vec<4,T> right4=vec<4,T>(right.x,right.y,right.z,T(0));
		result.set_column(0,right4);
		result.set_column(1,up4);
		result.set_column(2,fwd4);
		result.set_column(3,pos4);

		return result;
	}

	template <typename T>
	mat<4,4,T> ortho_mat(const T& left,const T& right,
			const T& bottom,const T& top,
			const T& near,const T& far)
	{
		mat<4,4,T> result;
		const T& m00=T(2)/(right-left);
		const T& m11=T(2)/(top-bottom);
		const T& m22=-T(2)/(far-near);

		vec<4,T> c0=vec<4,T>(m00,T(0),T(0),T(0));
		vec<4,T> c1=vec<4,T>(T(0),m11,T(0),T(0));
		vec<4,T> c2=vec<4,T>(T(0),T(0),m22,T(0));
		vec<4,T> c3=vec<4,T>(
				-(right+left)/(right-left),
				-(top+bottom)/(top-bottom),
				-(far+near)/(far-near),
				T(1));
		result.set_column(0,c0);
		result.set_column(1,c1);
		result.set_column(2,c2);
		result.set_column(3,c3);
		return result;
	}

	template <typename T>
	mat<4,4,T> ortho_mat(const T& width,const T& height,
			const T& near,const T& far)
	{
		const T& left=-width/T(2);
		const T& right=width/T(2);
		const T& bottom=-height/T(2);
		const T& top=height/T(2);
		return ortho_mat(left,right,bottom,top,near,far);
	}

	template <typename T>
	mat<4,4,T> proj_mat(const T& left,const T& right,
			const T& bottom,const T& top,
			const T& near,const T& far)
	{

		mat<4,4,T> result;
		const T& twonear=T(2)*near;
		const T& m00=twonear/(right-left);
		const T& m11=twonear/(top-bottom);
		const T& m20=(right+left)/(right-left);
		const T& m21=(top+bottom)/(top-bottom);
		const T& m22=-(far+near)/(far-near);
		const T& m23=-T(1);
		const T& m33=T(0);
		vec<4,T> c0=vec<4,T>(m00,T(0),T(0),T(0));
		vec<4,T> c1=vec<4,T>(T(0),m11,T(0),T(0));
		vec<4,T> c2=vec<4,T>(m20,m21,m22,m23);
		vec<4,T> c3=vec<4,T>(T(0),T(0),-(twonear*far)/(far-near),T(0));

		result.set_column(0,c0);
		result.set_column(1,c1);
		result.set_column(2,c2);
		result.set_column(3,c3);
		return result;
	}

	template <typename T>
	mat<4,4,T> proj_mat(const T& width,const T& height,
			const T& near,const T& far)
	{
		const T& left=-width/T(2);
		const T& right=width/T(2);
		const T& bottom=-height/T(2);
		const T& top=height/T(2);
		return proj_mat(left,right,bottom,top,near,far);
	}
}
