
template <typename T>
vec<3,T>::vec(const T elements[3])
{
	x=elements[0];
	y=elements[1];
	z=elements[2];
}

template <typename T>
vec<3,T>::vec(const T& val)
{
	x=val;
	y=val;
	z=val;
}

template <typename T>
vec<3,T>::vec()
	: vec(T(0)) { }

template <typename T>
vec<3,T>::vec(const vec<3,T>& other)
{
	x=other.x;
	y=other.y;
	z=other.z;
}

template <typename T>
vec<3,T>::vec(const T& x,const T& y,const T& z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}

template <typename T>
template <uint32 D>
vec<3,T>::vec(const vec<D,T>& other)
{
	if (D>=3)
	{
		x=other[0];
		y=other[1];
		z=other[2];
	}
	else if (D==2)
	{
		x=other[0];
		y=other[1];
		z=T(1);
	}
	else if (D==1)
	{
		x=other[0];
		y=T(0);
		z=T(1);
	}
}

template <typename T>
vec<3,T> vec<3,T>::operator+(const vec<3,T>& rhs) const
{
	return vec<3,T>(x+rhs.x,y+rhs.y,z+rhs.z);
}

template <typename T>
vec<3,T> vec<3,T>::operator-(const vec<3,T>& rhs) const
{
	return vec<3,T>(x-rhs.x,y-rhs.y,z-rhs.z);
}

template <typename T>
vec<3,T> vec<3,T>::operator-() const
{
	return vec<3,T>(-x,-y,-z);
}

template <typename T>
vec<3,T> vec<3,T>::operator*(const T& scalar) const
{
	return vec<3,T>(x*scalar,y*scalar,z*scalar);
}

template <typename T>
vec<3,T> vec<3,T>::operator/(const T& scalar) const
{
	return vec<3,T>(x/scalar,y/scalar,z/scalar);
}

template <typename T>
bool32 vec<3,T>::operator==(const vec<3,T>& rhs) const
{
	return this==&rhs||
		(x==rhs.x&&y==rhs.y&&z==rhs.z);
}

template <typename T>
bool32 vec<3,T>::operator!=(const vec<3,T>& rhs) const
{
	return !(*this==rhs);
}

template <typename T>
vec<3,T>& vec<3,T>::operator=(const vec<3,T>& rhs)
{

	if (this!=&rhs)
	{
		x=rhs.x;
		y=rhs.y;
		z=rhs.z;
	}
	return *this;
}

template <typename T>
vec<3,T>& vec<3,T>::operator-=(const vec<3,T>& rhs)
{

	if (this!=&rhs)
	{
		x=x-rhs.x;
		y=y-rhs.y;
		z=z-rhs.z;
	}
	return *this;
}

template <typename T>
vec<3,T>& vec<3,T>::operator+=(const vec<3,T>& rhs)
{

	if (this!=&rhs)
	{
		x=x+rhs.x;
		y=y+rhs.y;
		z=z+rhs.z;
	}
	return *this;
}

template <typename T>
vec<3,T>& vec<3,T>::operator*=(const T& scalar)
{
	x=x*scalar;
	y=y*scalar;
	z=z*scalar;
	return *this;
}

template <typename T>
vec<3,T>& vec<3,T>::operator/=(const T& scalar)
{
	x=x/scalar;
	y=y/scalar;
	z=z/scalar;
	return *this;
}

template <typename T>
T& vec<3,T>::operator[](uint32 index)
{
	ASSERT(index==0||index==1||index==2);
	if (index==0)
	{
		return x;
	}
	else if (index==1)
	{
		return y;
	}
	else
	{
		return z;
	}
}

template <typename T>
const T& vec<3,T>::operator[](uint32 index) const
{
	ASSERT(index==0||index==1||index==2);
	if (index==0)
	{
		return x;
	}
	else if (index==1)
	{
		return y;
	}
	else
	{
		return z;
	}
}


template <typename T>
T vec<3,T>::dot(const vec<3,T>& rhs) const
{
	return x*rhs.x+y*rhs.y+z*rhs.z;
}

template <typename T>
T vec<3,T>::len_sq() const
{
	return dot(*this);
}

template <typename T>
T vec<3,T>::len() const
{
	return sqrt(len_sq());
}

template <typename T>
vec<3,T> vec<3,T>::normal() const
{
	T l=len();
	return vec<3,T>(x/l,y/l,z/l);
}

template <typename T>
vec<3,T>& vec<3,T>::normalize()
{
	T l=len();
	x/=l;
	y/=l;
	z/=l;
	return *this;
}

template <typename T>
vec<3,T> vec<3,T>::hadamard(const vec<3,T>& rhs) const
{
	return vec<3,T>(x*rhs.x,y*rhs.y,z*rhs.z);
}

template <typename T>
vec<3,T> vec<3,T>::lerp(const T& t,const vec<3,T>& b) const
{
	vec<3,T> a=*this;
	return t*(b-a)+a;
}

template <typename T>
vec<3,T> vec<3,T>::cross(const vec<3,T>& rhs) const
{
	return vec<3,T>(
			y*rhs.z-z*rhs.y,
			x*rhs.z-z*rhs.x,
			x*rhs.y-y*rhs.x);
}

template <typename T>
vec<3,T> operator*(const T& scalar,const vec<3,T>& vector)
{
	return vec<3,T>(scalar*vector.x,scalar*vector.y,scalar*vector.z);
}

template <typename T>
T dot(const vec<3,T>& lhs,const vec<3,T>& rhs)
{
	return lhs.dot(rhs);
}

template <typename T>
vec<3,T> cross(const vec<3,T>& lhs,const vec<3,T>& rhs)
{
	return lhs.cross(rhs);
}

template <typename T>
T len_sq(const vec<3,T>& vector)
{
	return vector.len_sq();
}

template <typename T>
T len(const vec<3,T>& vector)
{
	return vector.len();
}

template <typename T>
vec<3,T> normal(const vec<3,T>& vector)
{
	return vector.normal();
}

template <typename T>
vec<3,T>& normalize(vec<3,T>& vector)
{
	return vector.normalize();
}

template <typename T>
vec<3,T> lerp(const vec<3,T>& a,const T& t,const vec<3,T>& b)
{
	return a.lerp(t,b);
}
