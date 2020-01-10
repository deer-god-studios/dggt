

template <typename T>
mat<3,3,T>::mat(const T e[9])
{
	m00=e[0];
	m01=e[1];
	m02=e[2];
	m10=e[3];
	m11=e[4];
	m12=e[5];
	m20=e[6];
	m21=e[7];
	m22=e[8];
}

template <typename T>
mat<3,3,T>::mat(const T& diagonal)
{
	m00=diagonal;
	m01=T(0);
	m02=T(0);
	m10=T(0);
	m11=diagonal;
	m12=T(0);
	m20=T(0);
	m21=T(0);
	m22=diagonal;
}

template <typename T>
mat<3,3,T>::mat(const mat<3,3,T>& other)
{
	m00=other.m00;
	m01=other.m01;
	m02=other.m02;
	m10=other.m10;
	m11=other.m11;
	m12=other.m12;
	m20=other.m20;
	m21=other.m21;
	m22=other.m22;
}

template <typename T>
mat<3,3,T>::mat()
	:mat(T(0)) { }

template <typename T>
mat<3,3,T>::mat(const T& m00,const T& m01,const T& m02,
		const T& m10,const T& m11,const T& m12,
		const T& m20,const T& m21,const T& m22)
{
	this->m00=m00;
	this->m01=m01;
	this->m02=m02;
	this->m10=m10;
	this->m11=m11;
	this->m12=m12;
	this->m20=m20;
	this->m21=m21;
	this->m22=m22;
}

template <typename T>
mat<3,3,T> mat<3,3,T>::operator+(const mat<3,3,T>& rhs) const
{
	mat<3,3,T> result;
	result.m00=m00+rhs.m00;
	result.m01=m01+rhs.m01;
	result.m02=m02+rhs.m02;
	result.m10=m10+rhs.m10;
	result.m11=m11+rhs.m11;
	result.m12=m12+rhs.m12;
	result.m20=m20+rhs.m20;
	result.m21=m21+rhs.m21;
	result.m22=m22+rhs.m22;
	return result;
}

template <typename T>
mat<3,3,T> mat<3,3,T>::operator-(const mat<3,3,T>& rhs) const
{
	mat<3,3,T> result;
	result.m00=m00-rhs.m00;
	result.m01=m01-rhs.m01;
	result.m02=m02-rhs.m02;
	result.m10=m10-rhs.m10;
	result.m11=m11-rhs.m11;
	result.m12=m12-rhs.m12;
	result.m20=m20-rhs.m20;
	result.m21=m21-rhs.m21;
	result.m22=m22-rhs.m22;
	return result;
}

template <typename T>
mat<3,3,T> mat<3,3,T>::operator*(const T& scalar) const
{
	mat<3,3,T> result;
	result.m00=m00*scalar;
	result.m01=m01*scalar;
	result.m02=m02*scalar;
	result.m10=m10*scalar;
	result.m11=m11*scalar;
	result.m12=m12*scalar;
	result.m20=m20*scalar;
	result.m21=m21*scalar;
	result.m22=m22*scalar;
	return result;
}

template <typename T>
mat<3,3,T> mat<3,3,T>::operator*(const mat<3,3,T>& rhs) const
{
	mat<3,3,T> result;
	result.m00=get_row(0).dot(rhs.get_column(0));
	result.m01=get_row(1).dot(rhs.get_column(0));
	result.m02=get_row(2).dot(rhs.get_column(0));

	result.m10=get_row(0).dot(rhs.get_column(1));
	result.m11=get_row(1).dot(rhs.get_column(1));
	result.m12=get_row(2).dot(rhs.get_column(1));

	result.m20=get_row(0).dot(rhs.get_column(2));
	result.m21=get_row(1).dot(rhs.get_column(2));
	result.m22=get_row(2).dot(rhs.get_column(2));

	return result;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::operator=(const mat<3,3,T>& rhs)
{
	if (this!=&rhs)
	{
		m00=rhs.m00;
		m01=rhs.m01;
		m02=rhs.m02;

		m10=rhs.m10;
		m11=rhs.m11;
		m12=rhs.m12;

		m20=rhs.m20;
		m21=rhs.m21;
		m22=rhs.m22;
	}
	return *this;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::operator+=(const mat<3,3,T>& rhs)
{
	if (this!=&rhs)
	{
		m00+=rhs.m00;
		m01+=rhs.m01;
		m02+=rhs.m02;

		m10+=rhs.m10;
		m11+=rhs.m11;
		m12+=rhs.m12;

		m20+=rhs.m20;
		m21+=rhs.m21;
		m22+=rhs.m22;
	}
	return *this;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::operator-=(const mat<3,3,T>& rhs)
{
	if (this!=&rhs)
	{
		m00-=rhs.m00;
		m01-=rhs.m01;
		m02-=rhs.m02;

		m10-=rhs.m10;
		m11-=rhs.m11;
		m12-=rhs.m12;

		m20-=rhs.m20;
		m21-=rhs.m21;
		m22-=rhs.m22;
	}
	return *this;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::operator*=(const mat<3,3,T>& rhs)
{
	mat<3,3,T>& lhs=*this;
	m00=get_row(0).dot(rhs.get_column(0));
	m01=get_row(1).dot(rhs.get_column(0));
	m02=get_row(2).dot(rhs.get_column(0));
	m10=get_row(0).dot(rhs.get_column(1));
	m11=get_row(1).dot(rhs.get_column(1));
	m12=get_row(2).dot(rhs.get_column(1));
	m20=get_row(0).dot(rhs.get_column(2));
	m21=get_row(1).dot(rhs.get_column(2));
	m22=get_row(2).dot(rhs.get_column(2));
	return lhs;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::operator*=(const T& scalar)
{
	mat<3,3,T>& lhs=*this;
	m00*=scalar;
	m01*=scalar;
	m02*=scalar;
	m10*=scalar;
	m11*=scalar;
	m12*=scalar;
	m20*=scalar;
	m21*=scalar;
	m22*=scalar;
	return lhs;
}


template <typename T>
vec<3,T> mat<3,3,T>::transform(const vec<3,T>& vector) const
{
	return vector[0]*get_column(0)+
		vector[1]*get_column(1)+
		vector[2]*get_column(2);
}

template <typename T>
mat<3,3,T> mat<3,3,T>::transpose() const
{
	mat<3,3,T> result;
	result.set_column(0,get_row(0));
	result.set_column(1,get_row(1));
	result.set_column(2,get_row(2));
	return result;
}

template <typename T>
T mat<3,3,T>::determinant() const
{
	T sign=T(1);
	vec<3,T> row=get_row(0);
	T result=0;
	for (uint32 i=0;i<3;++i)
	{
		mat<2,2,T> minm=minor(i,0);
		T factor=row[i];
		result+=sign*factor*minm.determinant();
		sign=-sign;
	}
	return result;
}

template <typename T>
T mat<3,3,T>::det() const
{
	return determinant();
}

template <typename T>
mat<3,3,T> mat<3,3,T>::comatrix() const
{
	mat<3,3,T> result;
	for (uint32 c=0;c<3;++c)
	{
		for (uint32 r=0;r<3;++r)
		{
			mat<2,2,T> min=minor(c,r);
			T det=min.determinant();
			result.get(c,r)=det;
		}
	}
	return result;
}


// TODO: FIX
template <typename T>
mat<2,2,T> mat<3,3,T>::minor(uint32 dc,uint32 dr) const
{
	mat<2,2,T> result;
	bool32 cSkip=0;
	bool32 rSkip=0;
	for (uint32 c=0;c<3;++c)
	{
		rSkip=0;
		if (c==dc)
		{
			cSkip=1;
			continue;
		}
		for (uint32 r=0;r<3;++r)
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
T& mat<3,3,T>::get(uint32 c,uint32 r)
{
	ASSERT(intvl_0n<uint32>(c,DIM)&&intvl_0n<uint32>(r,DIM));
	
	return data()[r+c*DIM];
}

template <typename T>
const T& mat<3,3,T>::get(uint32 c,uint32 r) const
{
	ASSERT(intvl_0n(c,DIM)&&
			intvl_0n(r,DIM));
	
	return data()[r+c*DIM];

}


template <typename T>
vec<3,T> mat<3,3,T>::get_column(uint32 c) const
{
	ASSERT(intvl_0n<uint32>(c,DIM));
	vec<3,T> result;
	if (c==0)
	{
		result[0]=m00;
		result[1]=m01;
		result[2]=m02;
	}
	else if (c==1)
	{
		result[0]=m10;
		result[1]=m11;
		result[2]=m12;
	}
	else
	{
		result[0]=m20;
		result[1]=m21;
		result[2]=m22;
	}
	return result;
}

template <typename T>
vec<3,T> mat<3,3,T>::get_row(uint32 r) const
{
	ASSERT(intvl_0n<uint32>(r,DIM));
	vec<3,T> result;
	if (r==0)
	{
		result[0]=m00;
		result[1]=m10;
		result[2]=m20;
	}
	else if (r==1)
	{
		result[0]=m01;
		result[1]=m11;
		result[2]=m21;
	}
	else
	{
		result[0]=m02;
		result[1]=m12;
		result[2]=m22;
	}
	return result;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::set_column(uint32 c,const vec<3,T>& val)
{
	ASSERT(intvl_0n(c,DIM));
	if (c==0)
	{
		m00=val[0];
		m01=val[1];
		m02=val[2];
	}
	else if (c==1)
	{
		m10=val[0];
		m11=val[1];
		m12=val[2];
	}
	else
	{
		m20=val[0];
		m21=val[1];
		m22=val[2];
	}
	return *this;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::set_row(uint32 r,const vec<3,T>& val)
{
	ASSERT(intvl_0n(r,DIM));
	if (r==0)
	{
		m00=val[0];
		m10=val[1];
		m20=val[2];
	}
	else if (r==1)
	{
		m01=val[0];
		m11=val[1];
		m21=val[2];
	}
	else
	{
		m02=val[0];
		m12=val[1];
		m22=val[2];
	}
	return *this;
}

/*
 A = [ a b c ]
 	 [ d e f ]
	 [ g h i ]
*/
template <typename T>
mat<3,3,T> mat<3,3,T>::inverse() const
{
	T det=determinant();
	ASSERT(det!=T(0));
	T invDet=T(1)/det;
	T a=get(0,0);
	T b=get(1,0);
	T c=get(2,0);
	T d=get(0,1);
	T e=get(1,1);
	T f=get(1,2);
	T g=get(0,2);
	T h=get(1,2);
	T i=get(2,2);
	T r00=e*i-f*h;
	T r01=-(d*i-f*g);
	T r02=d*h-e*g;
	T r10=-(b*i-c*h);
	T r11=a*i-c*g;
	T r12=-(a*h-b*g);
	T r20=b*f-c*e;
	T r21=-(a*f-c*d);
	T r22=a*e-b*d;
	mat<3,3,T> result=mat<3,3,T>(r00,r01,r02,
			r10,r11,r12,
			r20,r21,r22);
	result*=invDet;
	return result;
}

template <typename T>
mat<3,3,T>& mat<3,3,T>::invert()
{
	*this=inverse();
	return *this;
}

template <typename T>
vec<3,T> operator*(const vec<3,T>& vector,const mat<3,3,T>& matrix)
{
	return matrix.transform(vector);
}

template <typename T>
mat<3,3,T> operator*(const T& scalar,const mat<3,3,T>& matrix)
{
	return matrix*scalar;
}
