
namespace dggt
{
	template <typename T>
	b32 idx_table_iter<T>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <typename T>
	T& idx_table_iter<T>::operator*()
	{
		return get(*this);
	}

	template <typename T>
	const T& idx_table_iter<T>::operator*() const
	{
		return get(*this);
	}

	template <typename T>
	idx_table_iter<T>& operator++()
	{
		if (!dggt::is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}

	template <typename T>
	idx_table_iter<T> operator++(int)
	{
		idx_table_iter<T> result=*this;
		this->operator++();
		return result;
	}

	template <typename T>
	b32 is_end(const idx_table_iter<T>& it)
	{
		return currentHandle>=get_capacity(&tableMem);
	}

	template <typename T>
	b32 advance(idx_table_iter<T>& it)
	{
		if (!is_end(it))
		{
			while (it.flagMem[currentHandle]==IDX_EMPTY&&
					!it.is_end())
			{
				++it.currentHandle;
			}
		}
	}

	template <typename T>
	T& get(idx_table_iter<T>& it)
	{
		return it.tableMem[it.currentHandle];
	}

	template <typename T>
	const T& get(const idx_table_iter<T>& it)
	{
		return it.tableMem[it.currentHandle];
	}

	template <typename T>
	T* get_ptr(idx_table_iter<T>& it)
	{
		return it.tableMem+it.currentHandle;
	}

	template <typename T>
	const T* get_ptr(const idx_table_iter<T>& it)
	{
		return it.tableMem+it.currentHandle;
	}
	
	template <typename T>
	idx_table_mem get_mem(idx_table_iter<T>& it)
	{
		return it.tableMem;
	}

	template <typename T>
	const idx_table_mem get_mem(const idx_table_iter<T>& it)
	{
		return it.tableMem;
	}

	template <typename T>
	b32 is_coll_valid(const idx_table_iter<T>& it)
	{
		return it.table!=0;
	}

	template <typename T>
	b32 is_mem_valid(const idx_table_iter<T>& it)
	{
		return is_coll_valid(it)&&
			it.tableMem==it.table->table&&
			it.flagMem==it.table->flags;
	}

	template <typename T>
	b32 vindicate_mem(idx_table_iter<T>& it)
	{
		b32 result=false;
		if (is_coll_valid(it))
		{
			it.tableMem=it.table->table;
			it.flagMem=it.table->flags;
			result=true;
		}
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,idx_table_iter<T>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it))
		{
			if (is_coll_valid(it))
			{
				b32 destroyTable=
					!is_coll_valid(destroy_array(it.tableMem,a));
				b32 destroyFlags=
					!is_coll_valid(destroy_array(it.flagMem,a));
				result=destroyTable&&destroyFlags;
			}
		}
		return result;
	}

	template <typename T>
	u32 get_current(const idx_table_iter<T>& it)
	{
		return it.currentHandle;
	}
}
