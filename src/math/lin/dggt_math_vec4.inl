namespace dggt
{
	template <typename T>
	vec<4,T>::vec(const T elements[4])
	{
		x=elements[0];
		y=elements[1];
		z=elements[2];
		w=elements[4];
	}

	template <typename T>
	vec<4,T>::vec(const T& val)
	{
		x=val;
		y=val;
		z=val;
		w=val;
	}

	template <typename T>
	vec<4,T>::vec()
		: vec(T(0)) { }

	template <typename T>
	vec<4,T>::vec(const vec<4,T>& other)
	{
		x=other.x;
		y=other.y;
		z=other.z;
		w=other.w;
	}

	template <typename T>
	vec<4,T>::vec(const T& x,const T& y,const T& z,const T& w)
	{
		this->x=x;
		this->y=y;
		this->z=z;
		this->w=w;
	}

	template <typename T>
	template <uint32 D>
	vec<4,T>::vec(const vec<D,T>& other)
	{
		if (D>=4)
		{
			x=other[0];
			y=other[1];
			z=other[2];
			w=other[3];
		}
		else if (D==3)
		{
			x=other[0];
			y=other[1];
			z=other[2];
			w=T(1);
		}
		else if (D==2)
		{
			x=other[0];
			y=other[1];
			z=T(0);
			w=T(1);
		}
		else if (D==1)
		{
			x=other[0];
			y=T(0);
			z=T(0);
			w=T(1);
		}
	}

	template <typename T>
	vec<4,T> vec<4,T>::operator+(const vec<4,T>& rhs) const
	{
		return vec<4,T>(x+rhs.x,y+rhs.y,z+rhs.z,w+rhs.w);
	}

	template <typename T>
	vec<4,T> vec<4,T>::operator-(const vec<4,T>& rhs) const
	{
		return vec<4,T>(x-rhs.x,y-rhs.y,z-rhs.z,w-rhs.w);
	}

	template <typename T>
	vec<4,T> vec<4,T>::operator-() const
	{
		return vec<4,T>(-x,-y,-z,-w);
	}

	template <typename T>
	vec<4,T> vec<4,T>::operator*(const T& scalar) const
	{
		return vec<4,T>(x*scalar,y*scalar,z*scalar,w*scalar);
	}

	template <typename T>
	vec<4,T> vec<4,T>::operator/(const T& scalar) const
	{
		return vec<4,T>(x/scalar,y/scalar,z/scalar,w/scalar);
	}

	template <typename T>
	bool32 vec<4,T>::operator==(const vec<4,T>& rhs) const
	{
		return this==&rhs||
			(x==rhs.x&&y==rhs.y&&z==rhs.z&&w==rhs.w);
	}

	template <typename T>
	bool32 vec<4,T>::operator!=(const vec<4,T>& rhs) const
	{
		return !(*this==rhs);
	}

	template <typename T>
	vec<4,T>& vec<4,T>::operator=(const vec<4,T>& rhs)
	{

		if (this!=&rhs)
		{
			x=rhs.x;
			y=rhs.y;
			z=rhs.z;
			w=rhs.w;
		}
		return *this;
	}

	template <typename T>
	vec<4,T>& vec<4,T>::operator-=(const vec<4,T>& rhs)
	{

		if (this!=&rhs)
		{
			x=x-rhs.x;
			y=y-rhs.y;
			z=z-rhs.z;
			w=w-rhs.w;
		}
		return *this;
	}

	template <typename T>
	vec<4,T>& vec<4,T>::operator+=(const vec<4,T>& rhs)
	{

		if (this!=&rhs)
		{
			x=x+rhs.x;
			y=y+rhs.y;
			z=z+rhs.z;
			w=w+rhs.w;
		}
		return *this;
	}

	template <typename T>
	vec<4,T>& vec<4,T>::operator*=(const T& scalar)
	{
		x=x*scalar;
		y=y*scalar;
		z=z*scalar;
		w=w*scalar;
		return *this;
	}

	template <typename T>
	vec<4,T>& vec<4,T>::operator/=(const T& scalar)
	{
		x=x/scalar;
		y=y/scalar;
		z=z/scalar;
		w=w/scalar;
		return *this;
	}

	template <typename T>
	T& vec<4,T>::operator[](uint32 index)
	{
		ASSERT(index==0||index==1||index==2||index==3);
		if (index==0)
		{
			return x;
		}
		else if (index==1)
		{
			return y;
		}
		else if (index==2)
		{
			return z;
		}
		else
		{
			return w;
		}
	}

	template <typename T>
	const T& vec<4,T>::operator[](uint32 index) const
	{
		ASSERT(index==0||index==1||index==2||index==3);
		if (index==0)
		{
			return x;
		}
		else if (index==1)
		{
			return y;
		}
		else if (index==2)
		{
			return z;
		}
		else
		{
			return w;
		}
	}


	template <typename T>
	T vec<4,T>::dot(const vec<4,T>& rhs) const
	{
		return x*rhs.x+y*rhs.y+z*rhs.z+w*rhs.w;
	}

	template <typename T>
	T vec<4,T>::len_sq() const
	{
		return dot(*this);
	}

	template <typename T>
	T vec<4,T>::len() const
	{
		return sqrt(len_sq());
	}

	template <typename T>
	vec<4,T> vec<4,T>::normal() const
	{
		T l=len();
		return vec<4,T>(x/l,y/l,z/l,w/l);
	}

	template <typename T>
	vec<4,T>& vec<4,T>::normalize()
	{
		T l=len();
		x/=l;
		y/=l;
		z/=l;
		w/=l;
		return *this;
	}

	template <typename T>
	vec<4,T> vec<4,T>::hadamard(const vec<4,T>& rhs) const
	{
		return vec<4,T>(x*rhs.x,y*rhs.y,z*rhs.z,w*rhs.w);
	}

	template <typename T>
	vec<4,T> vec<4,T>::lerp(const T& t,const vec<4,T>& b) const
	{
		vec<4,T> a=*this;
		return t*(b-a)+a;
	}

	template <typename T>
	vec<4,T> operator*(const T& scalar,const vec<4,T>& vector)
	{
		return vec<4,T>(scalar*vector.x,scalar*vector.y,
				scalar*vector.z,scalar*vector.w);
	}

	template <typename T>
	T dot(const vec<4,T>& lhs,const vec<4,T>& rhs)
	{
		return lhs.dot(rhs);
	}

	template <typename T>
	T len_sq(const vec<4,T>& vector)
	{
		return vector.len_sq();
	}
	template <typename T>
	T len(const vec<4,T>& vector)
	{
		return vector.len();
	}

	template <typename T>
	vec<4,T> hadamard(const vec<4,T>& lhs,const vec<4,T>& rhs)
	{
		return lhs.hadamard(rhs);
	}

	template <typename T>
	vec<4,T> lerp(const vec<4,T>& a,const T& t,const vec<4,T>& b)
	{
		return a.lerp(t,b);
	}
}
