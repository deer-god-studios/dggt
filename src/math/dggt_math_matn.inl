
template <uint32 N,typename T>
mat<N,N,T>::mat(const T elements[N*N])
{
	for (uint32 i=0;i<N*N;++i)
	{
		e[i]=elements[i];
	}
}

template <uint32 N,typename T>
mat<N,N,T>::mat(const T& val)
{
	for (uint32 c=0;c<N;++c)
	{
		for (uint32 r=0;r<N;++r)
		{
			e[r+c*N]=c==r?val:T(0);
		}
	}
}

template <uint32 N,typename T>
mat<N,N,T>::mat(const mat<N,N,T>& other)
{
	for (uint32 i=0;i<N*N;++i)
	{
		e[i]=other.e[i];
	}
}

template <uint32 N,typename T>
mat<N,N,T>::mat()
	:mat(T(1)) { }

template <uint32 N,typename T>
mat<N,N,T> mat<N,N,T>::operator+(const mat<N,N,T>& rhs) const
{
	mat<N,N,T> result;
	for (uint32 i=0;i<N*N;++i)
	{
		result.e[i]=e[i]+rhs.e[i];
	}
	return result;
}

template <uint32 N,typename T>
mat<N,N,T> mat<N,N,T>::operator-(const mat<N,N,T>& rhs) const
{
	mat<N,N,T> result;
	for (uint32 i=0;i<N*N;++i)
	{
		result.e[i]=e[i]-rhs.e[i];
	}
	return result;
}

template <uint32 N,typename T>
mat<N,N,T> mat<N,N,T>::operator*(const T& scalar) const
{
	mat<N,N,T> result;
	for (uint32 i=0;i<N*N;++i)
	{
		result.e[i]=e[i]*scalar;
	}
	return result;
}

template <uint32 N,typename T>
mat<N,N,T> mat<N,N,T>::operator*(const mat<N,N,T>& rhs) const
{
	mat<N,N,T> result;
	for (uint32 c=0;c<N;++c)
	{
		for (uint32 r=0;r<N;++r)
		{
			vec<N,T> rowVec=get_row(r);
			vec<N,T> columnVec=rhs.get_column(c);
			T val=rowVec.dot(columnVec);
			result.get(c,r)=val;
		}
	}
	return result;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::operator=(const mat<N,N,T>& rhs)
{
	if (this!=&rhs)
	{
		for (uint32 i=0;i<N*N;++i)
		{
			e[i]=rhs.e[i];
		}
	}
	return *this;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::operator+=(const mat<N,N,T>& rhs)
{
	for (uint32 i=0;i<N*N;++i)
	{
		e[i]+=rhs.e[i];
	}
	return *this;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::operator-=(const mat<N,N,T>& rhs)
{
	for (uint32 i=0;i<N*N;++i)
	{
		e[i]-=rhs.e[i];
	}
	return *this;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::operator*=(const mat<N,N,T>& rhs)
{
	mat<N,N,T>& lhs=*this;
	for (uint32 c=0;c<N;++c)
	{
		for (uint32 r=0;r<N;++r)
		{
			vec<N,T> rowVec=get_row(r);
			vec<N,T> columnVec=rhs.get_column(c);
			T val=columnVec.dot(rowVec);
			get(c,r)=val;
		}
	}
	return lhs;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::operator*=(const T& scalar)
{
	for (uint32 i=0;i<N*N;++i)
	{
		e[i]=e[i]*scalar;
	}
}

template <uint32 N,typename T>
vec<N,T> mat<N,N,T>::transform(const vec<N,T>& vector) const
{
	vec<N,T> result;
	for (uint32 c=0;c<N;++c)
	{
		vec<N,T> columnVec=get_column(c);
		result+=vector[c]*columnVec;
	}
	return result;
}

template <uint32 N,typename T>
mat<N-1,N-1,T> mat<N,N,T>::minor(uint32 dc,uint32 dr) const
{
	mat<N-1,N-1,T> result;
	bool32 cSkip=0;
	bool32 rSkip=0;
	for (uint32 c=0;c<N;++c)
	{
		rSkip=0;
		if (c==dc)
		{
			cSkip=1;
			continue;
		}
		for (uint32 r=0;r<N;++r)
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

template <uint32 N,typename T>
T mat<N,N,T>::determinant() const
{
	T sign=T(1);
	vec<N,T> row=get_row(0);
	T result=0;
	for (uint32 i=0;i<N;++i)
	{
		mat<N-1,N-1,T> min=minor(i,0);
		T factor=row[i];
		result+=sign*factor*min.determinant();
		sign=-sign;
	}
	return result;
}

template <uint32 N,typename T>
T mat<N,N,T>::det() const
{
	return determinant();
}

template <uint32 N,typename T>
mat<N,N,T> mat<N,N,T>::comatrix() const
{
	mat<N,N,T> result;
	T sign=T(1);
	for (uint32 c=0;c<N;++c)
	{
		for (uint32 r=0;r<N;++r)
		{
			mat<N-1,N-1,T> min=minor(c,r);
			T det=min.determinant();
			result.get(c,r)=det;
			sign*=-T(1);
		}
		sign*=-T(1);
	}
	return result;
}

template <uint32 N,typename T>
mat<N,N,T> mat<N,N,T>::inverse() const
{
	mat<N,N,T> result;
	T det=determinant();
	T invDet=T(1)/det;
	mat<N,N,T> transComatrix=comatrix().transpose();
	result=invDet*transComatrix;
	return result;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::invert()
{
	mat<N,N,T> invMat=inverse();
	*this=invMat;
	return invMat;
}

template <uint32 N,typename T>
mat<N,N,T> mat<N,N,T>::transpose() const
{
	mat<N,N,T> result;
	for (uint32 c=0;c<N;++c)
	{
		vec<N,T> columnVec=get_column(c);
		result.set_column(c,columnVec);
	}
	return result;
}

template <uint32 N,typename T>
T& mat<N,N,T>::get(uint32 column,uint32 row)
{
	return e[row+column*N];
}

template <uint32 N,typename T>
const T& mat<N,N,T>::get(uint32 column,uint32 row) const
{
	return e[row+column*N];
}

template <uint32 N,typename T>
vec<N,T> mat<N,N,T>::get_column(uint32 column) const
{
	vec<N,T> result;
	for (uint32 r=0;r<N;++r)
	{
		result[r]=get(column,r);
	}
	return result;
}

template <uint32 N,typename T>
vec<N,T> mat<N,N,T>::get_row(uint32 row) const
{
	vec<N,T> result;
	for (uint32 c=0;c<N;++c)
	{
		result[c]=get(c,row);
	}
	return result;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::set_column(uint32 column,const vec<N,T>& val)
{
	for (uint32 r=0;r<N;++r)
	{
		get(column,r)=val[r];
	}
	return *this;
}

template <uint32 N,typename T>
mat<N,N,T>& mat<N,N,T>::set_row(uint32 row,const vec<N,T>& val)
{
	for (uint32 c=0;c<N;++c)
	{
		get(c,row)=val[c];
	}
	return *this;
}

template <uint32 N,typename T>
vec<N,T> operator*(const vec<N,T>& vector,const mat<N,N,T>& matrix)
{
	return matrix.transform(vector);
}

template <uint32 N,typename T>
mat<N,N,T> operator*(const T& scalar,const mat<N,N,T>& matrix)
{
	return matrix*scalar;
}
