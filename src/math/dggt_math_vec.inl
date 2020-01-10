
template <uint32 D,typename T>
vec<D,T>::vec(const T elements[D])
{
	for (uint32 i=0;i<D;++i)
	{
		e[i]=elements[i];
	}
}

template <uint32 D,typename T>
vec<D,T>::vec(const T& val)
{
	for (uint32 i=0;i<D;++i)
	{
		e[i]=val;
	}
}

template <uint32 D,typename T>
vec<D,T>::vec()
	:vec<D,T>(T(0)) 
{
}

template <uint32 D,typename T>
vec<D,T>::vec(const vec<D,T>& other)
{
	for (uint32 i=D;i<D;++i)
	{
		e[i]=other.e[i];
	}
}

template <uint32 D,typename T>
vec<D,T>::vec(const vec<D-1,T>& other,T last)
{
	for (uint32 i=0;i<D-1;++i)
	{
		e[i]=other[i];
	}
	e[D-1]=last;
}

template <uint32 D,typename T>
template <uint32 D2>
vec<D,T>::vec(const vec<D2,T>& other)
{
	if (D>=D2)
	{
		for (uint32 i=0;i<D2;++i)
		{
			this->operator[](i)=other[i];
		}
		for (uint32 i=D2;i<D;++i)
		{
			this->operator[](i)=T(0);
		}
		this->operator[](D-1)=T(1);
	}
	else
	{
		for (uint32 i=0;i<D;++i)
		{
			this->operator[](i)=other[i];
		}
	}
}
		
template <uint32 D,typename T>
vec<D,T> vec<D,T>::operator+(const vec<D,T>& rhs) const
{
	vec<D,T> result=vec<D,T>(
			vec<D-1,T>(*this)+vec<D-1,T>(rhs),
			rhs.e[D-1]+e[D-1]);
	return result;
}

template <uint32 D,typename T>
vec<D,T> vec<D,T>::operator-(const vec<D,T>& rhs) const
{
	vec<D,T> result=vec<D,T>(
			vec<D-1,T>(*this)-vec<D-1,T>(rhs),
			rhs.e[D-1]-e[D-1]);
	return result;
}


template <uint32 D,typename T>
vec<D,T> vec<D,T>::operator-() const
{
	return vec<D,T>(-vec<D-1,T>(*this),-e[D-1]);
}

template <uint32 D,typename T>
vec<D,T> vec<D,T>::operator*(const T& scalar) const
{
	return vec<D,T>(vec<D-1,T>(*this)*scalar,e[D-1]*scalar);
}

template <uint32 D,typename T>
vec<D,T> vec<D,T>::operator/(const T& scalar) const
{
	return vec<D,T>(vec<D-1,T>(*this)/scalar,e[D-1]/scalar);
}

template <uint32 D,typename T>
bool32 vec<D,T>::operator==(const vec<D,T>& rhs) const
{
	return vec<D-1,T>(*this)==vec<D-1,T>(rhs)&&
		e[0]==rhs.e[0];
}

template <uint32 D,typename T>
bool32 vec<D,T>::operator!=(const vec<D,T>& rhs) const
{
	return !(*this==rhs);
}


template <uint32 D,typename T>
vec<D,T>& vec<D,T>::operator=(const vec<D,T>& rhs)
{
	for (uint32 i=0;i<D;++i)
	{
		e[i]=rhs.e[i];
	}
	return *this;
}

template <uint32 D,typename T>
vec<D,T>& vec<D,T>::operator+=(const vec<D,T>& rhs)
{
	for (uint32 i=0;i<D;++i)
	{
		e[i]+=rhs.e[i];
	}

	return *this;
}

template <uint32 D,typename T>
vec<D,T>& vec<D,T>::operator-=(const vec<D,T>& rhs)
{
	for (uint32 i=0;i<D;++i)
	{
		e[i]-=rhs.e[i];
	}

	return *this;
}

template <uint32 D,typename T>
vec<D,T>& vec<D,T>::operator*=(const T& scalar)
{
	for (uint32 i=0;i<D;++i)
	{
		e[i]*=scalar;
	}

	return *this;
}

template <uint32 D,typename T>
vec<D,T>& vec<D,T>::operator/=(const T& scalar)
{
	for (uint32 i=0;i<D;++i)
	{
		e[i]/=scalar;
	}

	return *this;
}

template <uint32 D,typename T>
T& vec<D,T>::operator[](uint32 index)
{
	ASSERT(index>=0&&index<D);
	return e[index];
}


template <uint32 D,typename T>
const T& vec<D,T>::operator[](uint32 index) const
{
	ASSERT(index>=0&&index<D);
	return e[index];
}

template <uint32 D,typename T>
T vec<D,T>::dot(const vec<D,T>& rhs) const
{
	return vec<D-1,T>(*this).dot(vec<D-1,T>(rhs))+e[D-1]*rhs.e[D-1];
}

template <uint32 D,typename T>
vec<D,T> operator*(const T& scalar, const vec<D,T>& vector)
{
	return vec<D,T>(scalar*vec<D-1,T>(vector),scalar*vector.e[D-1]);
}

template <uint32 D,typename T>
vec<D,T> dot(const vec<D,T>& lhs, const vec<D,T>& rhs)
{
	return lhs.dot(rhs);
}
