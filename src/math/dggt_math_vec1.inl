
template <typename T>
vec<1,T>::vec(const T element[1])
{
	x=element[0];
}

template <typename T>
vec<1,T>::vec(const T& val)
{
	x=val;
}
template <typename T>
vec<1,T>::vec()
	:vec(T(0)) { }

template <typename T>
vec<1,T>::vec(const vec<1,T>& other)
{
	x=other.x;
}

template <typename T>
template <uint32 D>
vec<1,T>::vec(const vec<D,T>& other)
{
	x=other.e[0];
}

template <typename T>
vec<1,T> vec<1,T>::operator+(const vec<1,T>& rhs) const
{
	return vec<1,T>(x+rhs.x);
}

template <typename T>
vec<1,T> vec<1,T>::operator-(const vec<1,T>& rhs) const
{
	return vec<1,T>(x-rhs.x);
}

template <typename T>
vec<1,T> vec<1,T>::operator-() const
{
	return vec<1,T>(-x);
}

template <typename T>
vec<1,T> vec<1,T>::operator*(const T& scalar) const
{
	return vec<1,T>(x*scalar);
}

template <typename T>
vec<1,T> vec<1,T>::operator/(const T& scalar) const
{
	return vec<1,T>(x/scalar);
}

template <typename T>
bool32 vec<1,T>::operator==(const vec<1,T>& rhs) const
{
	return this==&rhs||
		x==rhs.x;
}

template <typename T>
bool32 vec<1,T>::operator!=(const vec<1,T>& rhs) const
{
	return !(*this==rhs);
}

template <typename T>
vec<1,T>& vec<1,T>::operator=(const vec<1,T>& rhs)
{

	if (this!=&rhs)
	{
		x=rhs.x;
	}
	return *this;
}

template <typename T>
vec<1,T>& vec<1,T>::operator-=(const vec<1,T>& rhs)
{

	if (this!=&rhs)
	{
		x=x-rhs.x;
	}
	return *this;
}

template <typename T>
vec<1,T>& vec<1,T>::operator+=(const vec<1,T>& rhs)
{

	if (this!=&rhs)
	{
		x=x+rhs.x;
	}
	return *this;
}

template <typename T>
vec<1,T>& vec<1,T>::operator*=(const T& scalar)
{
	x=x*scalar;
	return *this;
}

template <typename T>
vec<1,T>& vec<1,T>::operator/=(const T& scalar)
{
	x=x/scalar;
	return *this;
}

template <typename T>
vec<1,T>::operator T() const
{
	return x;
}
template <typename T>
vec<1,T>::operator T&()
{
	return x;
}

template <typename T>
T& vec<1,T>::operator[](uint32 index)
{
	ASSERT(index==0);
	return x;
}

template <typename T>
const T& vec<1,T>::operator[](uint32 index) const
{
	ASSERT(index==0);
	return x;
}


template <typename T>
T vec<1,T>::dot(const vec<1,T>& rhs) const
{
	return x*rhs.x;
}

template <typename T>
vec<1,T> operator*(const T& scalar,const vec<1,T>& vector)
{
	return vec<1,T>(scalar*vector.x);
}

template <typename T>
T dot(const vec<1,T>& lhs,const vec<1,T>& rhs)
{
	return lhs.dot(rhs);
}
