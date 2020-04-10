
namespace dggt
{
	template <typename T,msize S>
	b32 starray_iter<T,S>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <typename T,msize S>
	T& starray_iter<T,S>::operator*()
	{
		return get(*this);
	}

	template <typename T,msize S>
	const T& starray_iter<T,S>::operator*() const
	{
		return get(*this);
	}

	template <typename T,msize S>
	starray_iter<T>& starray_iter<T,S>::operator++()
	{
		if (!dggt::is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}
	
	template <typename T,msize S>
	starray_iter<T> starray_iter<T,S>::operator++(int)
	{
		starray_iter<T> result=*this;
		this->operator++();
		return result;
	}

	template <typename T,msize S>
	b32 is_end(const starray_iter<T,S>& it)
	{
		return it.current>=S;
	}

	template <typename T,msize S>
	b32 advance(starray_iter<T,S>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			++it.current;
			result=true;
		}
		return result;
	}

	template <typename T,msize S>
	T& get(starray_iter<T,S>& it)
	{
		return it.mem[it.current];
	}

	template <typename T,msize S>
	const T& get(const starray_iter<T,S>& it)
	{
		return it.mem[it.current];
	}

	template <typename T,msize S>
	T* get_ptr(starray_iter<T,S>& it)
	{
		return it.mem.mem+it.current;
	}

	template <typename T,msize S>
	const T* get_ptr(const starray_iter<T,S>& it)
	{
		return it.mem.mem+it.current;
	}
	
	template <typename T,msize S>
	starray<T,S>::mem_type get_mem(starray_iter<T,S>& it)
	{
		return it.mem;
	}

	template <typename T,msize S>
	const starray<T,S>::mem_type get_mem(const starray_iter<T,S>& it)
	{
		return it.mem;
	}
}
