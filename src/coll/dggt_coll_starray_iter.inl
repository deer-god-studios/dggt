
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
		return it.currentOffset>=S;
	}

	template <typename T,msize S>
	b32 advance(starray_iter<T,S>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			++it.currentOffset;
			result=true;
		}
		return result;
	}

	template <typename T,msize S>
	T& get(starray_iter<T,S>& it)
	{
		return it.starrayMem[it.currentOffset];
	}

	template <typename T,msize S>
	const T& get(const starray_iter<T,S>& it)
	{
		return it.starrayMem[it.currentOffset];
	}

	template <typename T,msize S>
	T* get_ptr(starray_iter<T,S>& it)
	{
		return it.starrayMem+it.currentOffset;
	}

	template <typename T,msize S>
	const T* get_ptr(const starray_iter<T,S>& it)
	{
		return it.starrayMem+it.currentOffset;
	}
	
	template <typename T,msize S>
	starray_mem<T,S> get_mem(starray_iter<T,S>& it)
	{
		return it.starrayMem;
	}

	template <typename T,msize S>
	const starray_mem<T,S> get_mem(const starray_iter<T,S>& it)
	{
		return it.starrayMem;
	}

	template <typename T,msize S>
	b32 is_coll_valid(const starray_iter<T,S>& it)
	{
		return it.starr!=0;
	}

	template <typename T,msize S>
	b32 is_mem_valid(const starray_iter<T,S>& it)
	{
		return is_coll_valid(it)&&
			it.starrayMem==it.starr->mem;
	}

	template <typename T,msize S>
	b32 vindicate_mem(starray_iter<T,S>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it)&&is_coll_valid(it))
		{
			it.starrayMem=it.starr->mem;
			result=true;
		}
		return result;
	}
}
