
namespace dggt
{
	template <typename T,msize S>
	page<T,S>::page()
	{
		for (msize b=0;b<S*sizeof(T);++b)
		{
			*((ubyte*)mem+b)=0;
		}
	}

	template <typename T,msize S>
	page<T,S>::page(const T& val)
	{
		for (msize i=0;i<S;++i)
		{
			mem[i]=val;
		}
	}

	template <typename T,msize S>
	page<T,S>::page(T[S] initMem)
	{
		for (msize b=0;b<S*sizeof(T);++b)
		{
			*((ubyte*)mem+b)=*((ubyte*)initMem+b);
		}
	}

	template <typename T,msize S>
	T& page<T,S>::operator[](msize offset)
	{
		return mem[offset];
	}

	template <typename T,msize S>
	const T& page<T,S>::operator[](msize offset) const
	{
		return mem[offset];
	}

	template <typename T,msize T>
	b32 page<T,S>::operator==(const page<T,S>& rhs) const
	{
		return mem==rhs.mem;
	}

	template <typename T,msize T>
	b32 page<T,S>::operator!=(const page<T,S>& rhs) const
	{
		return mem!=rhs.mem;
	}

	template <typename T,msize T>
	T* page<T,S>::get_ptr(msize offset)
	{
		return (T*)mem+offset;
	}

	template <typename T,msize T>
	const T* page<T,S>::get_ptr(offset) const
	{
		return (T*)mem+offset;
	}

	template <typename T,msize T>
	void* get_data(msize byteOffset)
	{
		return (void*)((ubyte*)mem+byteOffset);
	}

	template <typename T,msize T>
	const void* get_data(msize byteOffset) const
	{
		return (void*)((ubyte*)mem+byteOffset);
	}
}
