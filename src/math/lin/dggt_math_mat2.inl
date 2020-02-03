
namespace dggt
{
	template <typename T>
	mat<2,2,T>::mat(const T e[4])
	{
		m00=e[0];
		m01=e[1];
		m10=e[2];
		m11=e[3];
	}

	template <typename T>
	mat<2,2,T>::mat(const T& diagonal)
	{
		m00=diagonal;
		m01=T(0);
		m10=T(0);
		m11=diagonal;
	}

	template <typename T>
	mat<2,2,T>::mat()
		: mat(T(1)) { }

	template <typename T>
	mat<2,2,T>::mat(const T& m00,const T& m01,const T& m10,const T& m11)
	{
		this->m00=m00;
		this->m01=m01;
		this->m10=m10;
		this->m11=m11;
	}

	template <typename T>
	mat<2,2,T>::mat(const mat<2,2,T>& other)
	{
		m00=other.m00;
		m01=other.m01;
		m10=other.m10;
		m11=other.m11;
	}

	template <typename T>
	mat<2,2,T> mat<2,2,T>::operator+(const mat<2,2,T>& rhs) const
	{
		mat<2,2,T> result;
		result.m00=m00+rhs.m00;
		result.m01=m01+rhs.m01;
		result.m10=m10+rhs.m10;
		result.m11=m11+rhs.m11;
		return result;
	}

	template <typename T>
	mat<2,2,T> mat<2,2,T>::operator-(const mat<2,2,T>& rhs) const
	{
		mat<2,2,T> result;
		result.m00=m00-rhs.m00;
		result.m01=m01-rhs.m01;
		result.m10=m10-rhs.m10;
		result.m11=m11-rhs.m11;
		return result;
	}

	template <typename T>
	mat<2,2,T> mat<2,2,T>::operator*(const T& scalar) const
	{
		mat<2,2,T> result;
		result.m00=m00*scalar;
		result.m01=m01*scalar;
		result.m10=m10*scalar;
		result.m11=m11*scalar;
		return result;
	}

	template <typename T>
	mat<2,2,T> mat<2,2,T>::operator*(const mat<2,2,T>& rhs) const
	{
		mat<2,2,T> result;
		result.m00=get_row(0).dot(rhs.get_column(0));
		result.m01=get_row(1).dot(rhs.get_column(0));
		result.m10=get_row(0).dot(rhs.get_column(1));
		result.m11=get_row(1).dot(rhs.get_column(1));
		return result;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::operator=(const mat<2,2,T>& rhs)
	{
		if (this!=&rhs)
		{
			m00=rhs.m00;
			m01=rhs.m01;
			m10=rhs.m10;
			m11=rhs.m11;
		}
		return *this;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::operator+=(const mat<2,2,T>& rhs)
	{
		if (this!=&rhs)
		{
			m00+=rhs.m00;
			m01+=rhs.m01;
			m10+=rhs.m10;
			m11+=rhs.m11;
		}
		return *this;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::operator-=(const mat<2,2,T>& rhs)
	{
		if (this!=&rhs)
		{
			m00-=rhs.m00;
			m01-=rhs.m01;
			m10-=rhs.m10;
			m11-=rhs.m11;
		}
		return *this;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::operator*=(const mat<2,2,T>& rhs)
	{
		mat<2,2,T>& lhs=*this;
		m00=get_row(0).dot(rhs.get_column(0));
		m01=get_row(1).dot(rhs.get_column(0));
		m10=get_row(0).dot(rhs.get_column(1));
		m11=get_row(1).dot(rhs.get_column(1));
		return lhs;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::operator*=(const T& scalar)
	{
		mat<2,2,T>& lhs=*this;
		m00*=scalar;
		m01*=scalar;
		m10*=scalar;
		m11*=scalar;
		return lhs;
	}


	template <typename T>
	vec<2,T> mat<2,2,T>::transform(const vec<2,T>& vector) const
	{
		return vector[0]*get_column(0)+vector[1]*get_column(1);
	}

	template <typename T>
	mat<2,2,T> mat<2,2,T>::transpose() const
	{
		mat<2,2,T> result;
		result.set_column(0)=get_row(0);
		result.set_column(1)=get_row(1);
		return result;
	}

	template <typename T>
	T mat<2,2,T>::determinant() const
	{
		return m00*m11-m10*m01;
	}

	template <typename T>
	T mat<2,2,T>::det() const
	{
		return m00*m11-m10*m01;
	}


	template <typename T>
	T& mat<2,2,T>::get(uint32 c,uint32 r)
	{
		ASSERT(intvl_0n<uint32>(c,DIM)&&
				intvl_0n<uint32>(r,DIM));
		return data()[r+c*DIM];
	}

	template <typename T>
	const T& mat<2,2,T>::get(uint32 c,uint32 r) const
	{
		ASSERT(intvl_0n<uint32>(c,DIM)&&
				intvl_0n<uint32>(r,DIM));
		return data()[r+c*DIM];
	}


	template <typename T>
	vec<2,T> mat<2,2,T>::get_column(uint32 c) const
	{
		ASSERT(intvl_0n<uint32>(c,DIM));
		vec<2,T> result;
		if (c==0)
		{
			result[0]=m00;
			result[1]=m01;
		}
		else
		{
			result[0]=m10;
			result[1]=m11;
		}
		return result;
	}

	template <typename T>
	vec<2,T> mat<2,2,T>::get_row(uint32 r) const
	{
		ASSERT(intvl_0n<uint32>(r,DIM));
		vec<2,T> result;
		if (r==0)
		{
			result[0]=m00;
			result[1]=m10;
		}
		else
		{
			result[0]=m01;
			result[1]=m11;
		}
		return result;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::set_column(uint32 c,const vec<2,T>& val)
	{
		ASSERT(intvl_0n<uint32>(c,DIM));
		if (c==0)
		{
			m00=val[0];
			m01=val[1];
		}
		else
		{
			m10=val[0];
			m11=val[1];
		}
		return *this;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::set_row(uint32 r,const vec<2,T>& val)
	{
		ASSERT(intvl_0n<uint32>(r,DIM));
		if (r==0)
		{
			m00=val[0];
			m10=val[1];
		}
		else
		{
			m01=val[0];
			m11=val[1];
		}
		return *this;
	}

	template <typename T>
	mat<2,2,T> mat<2,2,T>::inverse() const
	{
		T det=determinant();
		ASSERT(det!=T(0));
		T invDet=T(1)/det;
		T a=get(0,0);
		T b=get(1,0);
		T c=get(0,1);
		T d=get(1,1);
		mat<2,2,T> result=mat<2,2,T>(d,-c,-b,a);
		result*=invDet;
		return result;
	}

	template <typename T>
	mat<2,2,T>& mat<2,2,T>::invert()
	{
		*this=inverse();
		return *this;
	}

	template <typename T>
	vec<2,T> operator*(const vec<2,T>& vector,const mat<2,2,T>& matrix)
	{
		return matrix.transform(vector);
	}

	template <typename T>
	mat<2,2,T> operator*(const T& scalar,const mat<2,2,T>& matrix)
	{
		return matrix*scalar;
	}
}
