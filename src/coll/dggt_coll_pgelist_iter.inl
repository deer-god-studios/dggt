
namespace dggt
{
	template <typename T,u32 S>
	b32 pgelist_iter<S,T>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <typename T,u32 S>
	T& pgelist_iter<S,T>::operator*()
	{
		return get(*this);
	}

	template <typename T,u32 S>
	const T& pgelist_iter<S,T>::operator*() const
	{
		return get(*this);
	}

	template <typename T,u32 S>
	pgelist_iter<S,T>& pgelist_iter<S,T>::operator++()
	{
		if (!dggt::is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}

	template <typename T,u32 S>
	pgelist_iter<S,T> pgelist_iter<S,T>::operator++(int)
	{
		pgelist_iter<S,T> result=*this;
		this->operator++();
		return result;
	}

	template <typename T,u32 S>
	b32 is_end(const pgelist_iter<S,T>& it)
	{
		is_end(it.pgeMemIter)&&
			is_end(it.pgelistMemIter);
	}

	template <typename T,u32 S>
	b32 advance(pgelist_iter<S,T>& it)
	{
		b32 result=false;
		if (!it.is_end())
		{
			++it.pgeMemIter;
			if (it.pgeMemIter.is_end())
			{
				++it.pgelistMemIter;
				if (!it.pgelistMemIter.is_end())
				{
					it.pgeMemIter=get_iter(*it.pgelistMemIter);
					result=true;
				}
			}
		}
		return result;
	}

	template <typename T,u32 S>
	T& get(pgelist_iter<S,T>& it)
	{
		return *it.pgeMemIter;
	}

	template <typename T,u32 S>
	const T& get(const pgelist_iter<S,T>& it)
	{
		return *it.pgeMemIter;
	}

	template <typename T,u32 S>
	T* get_ptr(pgelist_iter<S,T>& it)
	{
		return get_ptr(it.pgeMemIter);
	}

	template <typename T,u32 S>
	const T* get_ptr(const pgelist_iter<S,T>& it)
	{
		return get_ptr(it.pgeMemIter);
	}
	
	template <typename T,u32 S>
	pgelist_mem<S,T> get_mem(pgelist_iter<S,T>& it)
	{
		return it.pgeListMem;
	}

	template <typename T,u32 S>
	const pgelist_mem<S,T> get_mem(const pgelist_iter<S,T>& it)
	{
		return it.pgeListMem;
	}

	template <typename T,u32 S>
	b32 is_coll_valid(const pgelist_iter<S,T>& it)
	{
		return it.pgeList!=0;
	}

	template <typename T,u32 S>
	b32 is_mem_valid(const pgelist_iter<S,T>& it)
	{
		return is_coll_valid(it)&&
			it.pgelistMem==it.pgeList->list;
	}

	template <typename T,u32 S>
	b32 vindicate_mem(pgelist_iter<S,T>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it)&&
				is_coll_valid(it))
		{
			it.pgelistMem=it.pgelistMem->list;
		}
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,pgelist_iter<S,T>& it)
	{
		return !is_coll_valid(destroy_sllist(it.pgeList,a));
	}
}
