
namespace dggt
{
	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>::mat(const T elements[C*R])
	{
		for (uint32 i=0;i<C*R;++i)
		{
			e[i]=elements[i];
		}
	}


	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>::mat(const mat<C,R,T>& other)
	{
		for (uint32 i=0;i<C*R;++i)
		{
			e[i]=other.e[i];
		}
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>::mat()
	{
		for (uint32 i=0;i<C*R;++i)
		{
			e[i]=T(0);
		}
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T> mat<C,R,T>::operator+(const mat<C,R,T>& rhs) const
	{
		mat<C,R,T> result;
		for (uint32 i=0;i<C*R;++i)
		{
			result.e[i]=e[i]+rhs.e[i];
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T> mat<C,R,T>::operator-(const mat<C,R,T>& rhs) const
	{
		mat<C,R,T> result;
		for (uint32 i=0;i<C*R;++i)
		{
			result.e[i]=e[i]-rhs.e[i];
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T> mat<C,R,T>::operator*(const T& scalar) const
	{
		mat<C,R,T> result;
		for (uint32 i=0;i<C*R;++i)
		{
			result.e[i]=e[i]*scalar;
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	template <uint32 M>
	mat<C,M,T> mat<C,R,T>::operator*(const mat<R,M,T>& rhs) const
	{
		mat<C,M,T> result;
		for (uint32 c=0;c<C;++c)
		{
			for (uint32 r=0;r<R;++r)
			{
				vec<C,T> rowVec=get_row(r);
				vec<R,T> columnVec=rhs.get_column(c);
				T val=rowVec.dot(columnVec);
				result.get(c,r)=val;
			}
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>& mat<C,R,T>::operator=(const mat<C,R,T>& rhs)
	{
		if (this!=&rhs)
		{
			for (uint32 i=0;i<C*R;++i)
			{
				e[i]=rhs.e[i];
			}
		}
		return *this;
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>& mat<C,R,T>::operator+=(const mat<C,R,T>& rhs)
	{
		for (uint32 i=0;i<C*R;++i)
		{
			e[i]+=rhs.e[i];
		}
		return *this;
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>& mat<C,R,T>::operator-=(const mat<C,R,T>& rhs)
	{
		for (uint32 i=0;i<C*R;++i)
		{
			e[i]-=rhs.e[i];
		}
		return *this;
	}

	template <uint32 C,uint32 R,typename T>
	template <uint32 M>
	mat<C,M,T>& mat<C,R,T>::operator*=(const mat<R,M,T>& rhs)
	{
		mat<C,R,T>& lhs=*this;
		for (uint32 c=0;c<C;++c)
		{
			for (uint32 r=0;r<R;++r)
			{
				vec<C,T> rowVec=get_row(r);
				vec<R,T> columnVec=rhs.get_column(c);
				T val=columnVec.dot(rowVec);
				get(c,r)=val;
			}
		}
		return lhs;
	}

	template <uint32 C,uint32 R,typename T>
	vec<R,T> mat<C,R,T>::transform(const vec<C,T>& vector) const
	{
		vec<R,T> result;
		for (uint32 c=0;c<C;++c)
		{
			vec<R,T> columnVec=get_column(c);
			result+=vector[c]*columnVec;
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	mat<R,C,T> mat<C,R,T>::transpose() const
	{
		mat<R,C,T> result;
		for (uint32 c=0;c<C;++c)
		{
			vec<R,T> columnVec=get_column(c);
			result.set_column(columnVec);
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	T& mat<C,R,T>::get(uint32 column,uint32 row)
	{
		return e[row+column*R];
	}

	template <uint32 C,uint32 R,typename T>
	const T& mat<C,R,T>::get(uint32 column,uint32 row) const
	{
		return e[row+column*R];
	}

	template <uint32 C,uint32 R,typename T>
	vec<R,T> mat<C,R,T>::get_column(uint32 column) const
	{
		vec<R,T> result;
		for (uint32 r=0;r<R;++r)
		{
			result[r]=get(column,r);
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	vec<C,T> mat<C,R,T>::get_row(uint32 row) const
	{
		vec<R,T> result;
		for (uint32 c=0;c<C;++c)
		{
			result[c]=get(c,row);
		}
		return result;
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>& mat<C,R,T>::set_column(uint32 column,const vec<R,T>& val)
	{
		for (uint32 r=0;r<R;++r)
		{
			get(column,r)=val[r];
		}
		return *this;
	}

	template <uint32 C,uint32 R,typename T>
	mat<C,R,T>& mat<C,R,T>::set_row(uint32 row,const vec<C,T>& val)
	{
		for (uint32 c=0;c<C;++c)
		{
			get(c,row)=val[c];
		}
		return *this;
	}

	template <uint32 C,uint32 R,typename T>
	vec<R,T> operator*(const vec<C,T>& vector,const mat<C,R,T>& matrix)
	{
		return matrix.transform(vector);
	}
	template <uint32 C,uint32 R,typename T>
	mat<C,R,T> operator*(const T& scalar,const mat<C,R,T>& matrix)
	{
		return matrix*scalar;
	}
}
