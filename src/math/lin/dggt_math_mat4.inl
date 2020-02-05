namespace dggt 
{
	template <typename T>
	mat<4,4,T>::mat(const T e[16])
	{
		m00=e[0];
		m01=e[1];
		m02=e[2];
		m03=e[3];

		m10=e[4];
		m11=e[5];
		m12=e[6];
		m13=e[7];

		m20=e[8];
		m21=e[9];
		m22=e[10];
		m23=e[11];

		m30=e[12];
		m31=e[13];
		m32=e[14];
		m33=e[15];
	}

	template <typename T>
	mat<4,4,T>::mat(const T& diagonal)
	{
		get(0,0)=diagonal;
		m01=T(0);
		m02=T(0);
		m03=T(0);

		m10=T(0);
		get(1,1)=diagonal;
		m12=T(0);
		m13=T(0);

		m20=T(0);
		m21=T(0);
		get(2,2)=diagonal;
		m23=T(0);

		m30=T(0);
		m31=T(0);
		m32=T(0);
		get(3,3)=diagonal;
	}

	template <typename T>
	mat<4,4,T>::mat(const mat<4,4,T>& other)
	{
		m00=other.m00;
		m01=other.m01;
		m02=other.m02;
		m03=other.m03;

		m10=other.m10;
		m11=other.m11;
		m12=other.m12;
		m13=other.m13;

		m20=other.m20;
		m21=other.m21;
		m22=other.m22;
		m23=other.m23;

		m30=other.m30;
		m31=other.m31;
		m32=other.m32;
		m33=other.m33;
	}

	template <typename T>
	mat<4,4,T>::mat()
		:mat(T(0)) { }

	template <typename T>
	mat<4,4,T>::mat(const T& m00,const T& m01,const T& m02,const T& m03,
			const T& m10,const T& m11,const T& m12,const T& m13,
			const T& m20,const T& m21,const T& m22,const T& m23,
			const T& m30,const T& m31,const T& m32,const T& m33)
	{
		this->m00=m00;
		this->m01=m01;
		this->m02=m02;
		this->m03=m03;

		this->m10=m10;
		this->m11=m11;
		this->m12=m12;
		this->m13=m13;

		this->m20=m20;
		this->m21=m21;
		this->m22=m22;
		this->m23=m23;

		this->m30=m30;
		this->m31=m31;
		this->m32=m32;
		this->m33=m33;
	}
	template <typename T>
	mat<4,4,T> mat<4,4,T>::comatrix() const
	{
		mat<4,4,T> result;
		T sign=T(1);
		for (uint32 c=0;c<4;++c)
		{
			for (uint32 r=0;r<4;++r)
			{
				mat<3,3,T> min=minor(c,r);
				T det=min.determinant();
				result.get(c,r)=sign*det;
				sign*=-T(1);
			}
			sign*=-T(1);
		}
		return result;
	}


	// TODO: FIX
	template <typename T>
	mat<3,3,T> mat<4,4,T>::minor(uint32 dc,uint32 dr) const
	{
		mat<3,3,T> result;
		bool32 cSkip=0;
		bool32 rSkip=0;
		for (uint32 c=0;c<DIM;++c)
		{
			rSkip=0;
			if (c==dc)
			{
				cSkip=1;
				continue;
			}
			for (uint32 r=0;r<DIM;++r)
			{
				if (r==dr)
				{
					rSkip=1;
					continue;
				}
				uint32 ci=cSkip?c-1:c;
				uint32 ri=rSkip?r-1:r;
				result.get(ci,ri)=get(c,r);
			}
		}
		return result;
	}

	template <typename T>
	mat<4,4,T> mat<4,4,T>::operator+(const mat<4,4,T>& rhs) const
	{
		mat<4,4,T> result;
		result.m00=m00+rhs.m00;
		result.m01=m01+rhs.m01;
		result.m02=m02+rhs.m02;
		result.m03=m03+rhs.m03;

		result.m10=m10+rhs.m10;
		result.m11=m11+rhs.m11;
		result.m12=m12+rhs.m12;
		result.m13=m13+rhs.m13;

		result.m20=m20+rhs.m20;
		result.m21=m21+rhs.m21;
		result.m22=m22+rhs.m22;
		result.m23=m23+rhs.m23;

		result.m30=m30+rhs.m30;
		result.m31=m31+rhs.m31;
		result.m32=m32+rhs.m32;
		result.m33=m33+rhs.m33;

		return result;
	}

	template <typename T>
	mat<4,4,T> mat<4,4,T>::operator-(const mat<4,4,T>& rhs) const
	{
		mat<4,4,T> result;
		result.m00=m00-rhs.m00;
		result.m01=m01-rhs.m01;
		result.m02=m02-rhs.m02;
		result.m03=m03-rhs.m03;

		result.m10=m10-rhs.m10;
		result.m11=m11-rhs.m11;
		result.m12=m12-rhs.m12;
		result.m13=m13-rhs.m13;

		result.m20=m20-rhs.m20;
		result.m21=m21-rhs.m21;
		result.m22=m22-rhs.m22;
		result.m23=m23-rhs.m23;

		result.m30=m30-rhs.m30;
		result.m31=m31-rhs.m31;
		result.m32=m32-rhs.m32;
		result.m33=m33-rhs.m33;

		return result;
	}

	template <typename T>
	mat<4,4,T> mat<4,4,T>::operator*(const T& scalar) const
	{
		mat<4,4,T> result;
		result.m00=m00*scalar;
		result.m01=m01*scalar;
		result.m02=m02*scalar;
		result.m03=m03*scalar;

		result.m10=m10*scalar;
		result.m11=m11*scalar;
		result.m12=m12*scalar;
		result.m13=m13*scalar;

		result.m20=m20*scalar;
		result.m21=m21*scalar;
		result.m22=m22*scalar;
		result.m23=m23*scalar;
		
		result.m30=m30*scalar;
		result.m31=m31*scalar;
		result.m32=m32*scalar;
		result.m33=m33*scalar;
		return result;
	}

	template <typename T>
	mat<4,4,T> mat<4,4,T>::operator*(const mat<4,4,T>& rhs) const
	{
		mat<4,4,T> result;
		result.m00=get_row(0).dot(rhs.get_column(0));
		result.m01=get_row(1).dot(rhs.get_column(0));
		result.m02=get_row(2).dot(rhs.get_column(0));
		result.m03=get_row(3).dot(rhs.get_column(0));

		result.m10=get_row(0).dot(rhs.get_column(1));
		result.m11=get_row(1).dot(rhs.get_column(1));
		result.m12=get_row(2).dot(rhs.get_column(1));
		result.m13=get_row(3).dot(rhs.get_column(1));

		result.m20=get_row(0).dot(rhs.get_column(2));
		result.m21=get_row(1).dot(rhs.get_column(2));
		result.m22=get_row(2).dot(rhs.get_column(2));
		result.m23=get_row(3).dot(rhs.get_column(2));

		result.m30=get_row(0).dot(rhs.get_column(3));
		result.m31=get_row(1).dot(rhs.get_column(3));
		result.m32=get_row(2).dot(rhs.get_column(3));
		result.m33=get_row(3).dot(rhs.get_column(3));
		return result;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::operator=(const mat<4,4,T>& rhs)
	{
		if (this!=&rhs)
		{
			m00=rhs.m00;
			m01=rhs.m01;
			m02=rhs.m02;
			m03=rhs.m03;

			m10=rhs.m10;
			m11=rhs.m11;
			m12=rhs.m12;
			m13=rhs.m13;

			m20=rhs.m20;
			m21=rhs.m21;
			m22=rhs.m22;
			m23=rhs.m23;

			m30=rhs.m30;
			m31=rhs.m31;
			m32=rhs.m32;
			m33=rhs.m33;
			
		}
		return *this;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::operator+=(const mat<4,4,T>& rhs)
	{
		if (this!=&rhs)
		{
			m00+=rhs.m00;
			m01+=rhs.m01;
			m02+=rhs.m02;
			m03+=rhs.m03;

			m10+=rhs.m10;
			m11+=rhs.m11;
			m12+=rhs.m12;
			m13+=rhs.m13;

			m20+=rhs.m20;
			m21+=rhs.m21;
			m22+=rhs.m22;
			m23+=rhs.m23;

			m30+=rhs.m30;
			m31+=rhs.m31;
			m32+=rhs.m32;
			m33+=rhs.m33;
		}
		return *this;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::operator-=(const mat<4,4,T>& rhs)
	{
		if (this!=&rhs)
		{
			m00-=rhs.m00;
			m01-=rhs.m01;
			m02-=rhs.m02;
			m03-=rhs.m03;

			m10-=rhs.m10;
			m11-=rhs.m11;
			m12-=rhs.m12;
			m13-=rhs.m13;

			m20-=rhs.m20;
			m21-=rhs.m21;
			m22-=rhs.m22;
			m23-=rhs.m23;

			m30-=rhs.m30;
			m31-=rhs.m31;
			m32-=rhs.m32;
			m33-=rhs.m33;
		}
		return *this;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::operator*=(const mat<4,4,T>& rhs)
	{
		mat<4,4,T>& lhs=*this;
		m00=get_row(0).dot(rhs.get_column(0));
		m01=get_row(1).dot(rhs.get_column(0));
		m02=get_row(2).dot(rhs.get_column(0));
		m03=get_row(3).dot(rhs.get_coliumn(0));

		m10=get_row(0).dot(rhs.get_column(1));
		m11=get_row(1).dot(rhs.get_column(1));
		m12=get_row(2).dot(rhs.get_column(1));
		m13=get_row(3).dot(rhs.get_column(3));

		m20=get_row(0).dot(rhs.get_column(2));
		m21=get_row(1).dot(rhs.get_column(2));
		m22=get_row(2).dot(rhs.get_column(2));
		m23=get_row(3).dot(rhs.get_column(2));

		m30=get_row(0).dot(rhs.get_column(3));
		m31=get_row(1).dot(rhs.get_column(3));
		m32=get_row(2).dot(rhs.get_column(3));
		m33=get_row(3).dot(rhs.get_column(3));
		return lhs;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::operator*=(const T& scalar)
	{
		mat<4,4,T>& lhs=*this;
		m00*=scalar;
		m01*=scalar;
		m02*=scalar;
		m03*=scalar;

		m10*=scalar;
		m11*=scalar;
		m12*=scalar;
		m13*=scalar;

		m20*=scalar;
		m21*=scalar;
		m22*=scalar;
		m23*=scalar;
		m30*=scalar;
		m31*=scalar;
		m32*=scalar;
		m33*=scalar;
		return lhs;
	}


	template <typename T>
	vec<4,T> mat<4,4,T>::transform(const vec<4,T>& vector) const
	{
		return vector[0]*get_column(0)+
			vector[1]*get_column(1)+
			vector[2]*get_column(2)+vector[3]*get_column(3);
	}

	template <typename T>
	mat<4,4,T> mat<4,4,T>::transpose() const
	{
		mat<4,4,T> result;
		result.set_column(0,get_row(0));
		result.set_column(1,get_row(1));
		result.set_column(2,get_row(2));
		result.set_column(3,get_row(3));
		return result;
	}

	template <typename T>
	T mat<4,4,T>::determinant() const
	{
		T sign=T(1);
		vec<4,T> row=get_row(0);
		T result=0;
		for (uint32 i=0;i<4;++i)
		{
			mat<3,3,T> minm=minor(i,0);
			T factor=row[i];
			result+=sign*factor*minm.determinant();
			sign=-sign;
		}
		return result;
	}

	template <typename T>
	T mat<4,4,T>::det() const
	{
		return determinant();
	}

	template <typename T>
	T& mat<4,4,T>::get(uint32 c,uint32 r)
	{
		ASSERT(intvl_0n<uint32>(c,DIM)&&
				intvl_0n<uint32>(r,DIM));
		return data()[r+4*c];
	}

	template <typename T>
	const T& mat<4,4,T>::get(uint32 c,uint32 r) const
	{
		ASSERT(intvl_0n<uint32>(c,DIM)&&
				intvl_0n<uint32>(r,DIM));
		return data()[r+4*c];
	}


	template <typename T>
	vec<4,T> mat<4,4,T>::get_column(uint32 c) const
	{
		ASSERT(intvl_0n<uint32>(c,DIM));
		vec<4,T> result;
		if (c==0)
		{
			result[0]=m00;
			result[1]=m01;
			result[2]=m02;
			result[3]=m03;
		}
		else if (c==1)
		{
			result[0]=m10;
			result[1]=m11;
			result[2]=m12;
			result[3]=m13;
		}
		else if (c==2)
		{
			result[0]=m20;
			result[1]=m21;
			result[2]=m22;
			result[3]=m23;
		}
		else
		{
			result[0]=m30;
			result[1]=m31;
			result[2]=m32;
			result[3]=m33;
		}
		return result;
	}

	template <typename T>
	vec<4,T> mat<4,4,T>::get_row(uint32 r) const
	{
		ASSERT(intvl_0n<uint32>(r,DIM));
		vec<4,T> result;
		if (r==0)
		{
			result[0]=m00;
			result[1]=m10;
			result[2]=m20;
			result[3]=m30;
		}
		else if (r==1)
		{
			result[0]=m01;
			result[1]=m11;
			result[2]=m21;
			result[3]=m31;
		}
		else if (r==2)
		{
			result[0]=m02;
			result[1]=m12;
			result[2]=m22;
			result[3]=m32;
		}
		else
		{
			result[0]=m03;
			result[1]=m13;
			result[2]=m23;
			result[3]=m33;
		}
		return result;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::set_column(uint32 c,const vec<4,T>& val)
	{
		ASSERT(intvl_0n<uint32>(c,DIM));
		if (c==0)
		{
			m00=val[0];
			m01=val[1];
			m02=val[2];
			m03=val[3];
		}
		else if (c==1)
		{
			m10=val[0];
			m11=val[1];
			m12=val[2];
			m13=val[3];
		}
		else if (c==2)
		{
			m20=val[0];
			m21=val[1];
			m22=val[2];
			m23=val[3];
		}
		else
		{
			m30=val[0];
			m31=val[1];
			m32=val[2];
			m33=val[3];
		}
		return *this;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::set_row(uint32 r,const vec<4,T>& val)
	{
		ASSERT(intvl_0n<uint32>(r,DIM));
		if (r==0)
		{
			m00=val[0];
			m10=val[1];
			m20=val[2];
			m30=val[3];
		}
		else if (r==1)
		{
			m01=val[0];
			m11=val[1];
			m21=val[2];
			m31=val[3];
		}
		else if (r==2)
		{
			m02=val[0];
			m12=val[1];
			m22=val[2];
			m23=val[2];
		}
		else
		{
			m03=val[0];
			m13=val[1];
			m23=val[2];
			m33=val[2];
		}
		return *this;
	}

	/*
	 A = [ a b c ]
		 [ d e f ]
		 [ g h i ]
	*/
	template <typename T>
	mat<4,4,T> mat<4,4,T>::inverse() const
	{
		mat<4,4,T> result;
		T det=determinant();
		T invDet=T(1)/det;
		mat<4,4,T> transComatrix=comatrix().transpose();
		result=invDet*transComatrix;
		return result;
	}

	template <typename T>
	mat<4,4,T>& mat<4,4,T>::invert()
	{
		*this=inverse();
		return *this;
	}

	template <typename T>
	vec<4,T> operator*(const vec<4,T>& vector,const mat<4,4,T>& matrix)
	{
		return matrix.transform(vector);
	}

	template <typename T>
	mat<4,4,T> operator*(const T& scalar,const mat<4,4,T>& matrix)
	{
		return matrix*scalar;
	}
}
