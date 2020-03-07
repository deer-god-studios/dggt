
namespace dggt
{
	template <typename T>
	T& array_iter<T>::operator*()
	{
		return get(*this);
	}

	template <typename T>
	const T& array_iter<T>::operator*() const
	{
		return get(*this);
	}

	template <typename T>
	array_iter<T>& array_iter<T>::operator++()
	{
		if (!is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}
	
	template <typename T>
	array_iter<T> array_iter<T>::operator++(int)
	{
		array_iter<T>& result=*this;
		if (!is_end(*this))
		{
			advance(*this);
		}
		return result;
	}

	template <typename T>
	b32 is_end(const array_iter<T>& it)
	{
		return it.current<it.table.count;
	}

	template <typename T>
	b32 advance(array_iter<T>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			++it.current;
		}
		return result;
	}

	template <typename T>
	T& get(array_iter<T>& it)
	{
		return *(it.table);
	}

	template <typename T>
	const T& get(const array_iter<T>& it)
	{
		return *(it.table);
	}

	template <typename T>
	T* get_ptr(array_iter<T>& it)
	{
		return it.table.ptr;
	}

	template <typename T>
	const T* get_ptr(const array_iter<T>& it)
	{
		return it.table.ptr;
	}
	
	template <typename T>
	blk<T> get_mem(array_iter<T>& it)
	{
		return it.table;
	}

	template <typename T>
	const blk<T> get_mem(const array_iter<T>& it)
	{
		return it.table;
	}

	template <typename T>
	b32 is_coll_valid(const array_iter<T>& it)
	{
		return it.arr!=0;
	}

	template <typename T>
	b32 is_mem_valid(const array_iter<T>& it)
	{
		return is_coll_valid(it)&&it.table.ptr==it.arr->table.ptr&&
			it.table.count==it.arr->table.count;
	}

	template <typename T>
	b32 vindicate_mem(array_iter<T>& it)
	{
		b32 result=false;
		if (is_coll_valid(it))
		{
			it.table.ptr=it.arr->table.ptr;
			it.table.count=it.arr->table.count;
		}
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,array_iter<T>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it))
		{
			result=free(a,it.table.ptr,it.table.count);
			vindicate_mem(it);
		}
		return result;
	}
}
