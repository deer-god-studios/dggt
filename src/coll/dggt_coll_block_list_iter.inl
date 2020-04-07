
namespace dggt
{
	template <u32 BLOCKSIZE,typename T>
	b32 block_list_iter<BLOCKSIZE,T>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <u32 BLOCKSIZE,typename T>
	T& block_list_iter<BLOCKSIZE,T>::operator*()
	{
		return get(*this);
	}

	template <u32 BLOCKSIZE,typename T>
	const T& block_list_iter<BLOCKSIZE,T>::operator*() const
	{
		return get(*this);
	}

	template <u32 BLOCKSIZE,typename T>
	block_list_iter<BLOCKSIZE,T>& block_list_iter<BLOCKSIZE,T>::operator++()
	{
		if (!dggt::is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}

	template <u32 BLOCKSIZE,typename T>
	block_list_iter<BLOCKSIZE,T> block_list_iter<BLOCKSIZE,T>::operator++(int)
	{
		block_list_iter<BLOCKSIZE,T> result=*this;
		this->operator++();
		return result;
	}

	template <u32 BLOCKSIZE,typename T>
	b32 is_end(const block_list_iter<BLOCKSIZE,T>& it)
	{
		is_end(it.lblockListIter)&&
			is_end(it.lblockIter);
	}

	template <u32 BLOCKSIZE,typename T>
	b32 advance(block_list_iter<BLOCKSIZE,T>& it)
	{
		b32 result=false;
		if (!it.is_end())
		{
			++it.lblockIter;
			if (it.lblockIter.is_end())
			{
				++it.lblockListIter;
				if (!it.lblockListIter.is_end())
				{
					it.lblockIter=get_iter(*it.lblockListIter);
					result=true;
				}
			}
		}
		return result;
	}

	template <u32 BLOCKSIZE,typename T>
	T& get(block_list_iter<BLOCKSIZE,T>& it)
	{
		return *it.lblockIter;
	}

	template <u32 BLOCKSIZE,typename T>
	const T& get(const block_list_iter<BLOCKSIZE,T>& it)
	{
		return *it.lblockIter;
	}

	template <u32 BLOCKSIZE,typename T>
	T* get_ptr(block_list_iter<BLOCKSIZE,T>& it)
	{
		return get_ptr(it.lblockIter);
	}

	template <u32 BLOCKSIZE,typename T>
	const T* get_ptr(const block_list_iter<BLOCKSIZE,T>& it)
	{
		return get_ptr(it.lblockIter);
	}
	
	template <u32 BLOCKSIZE,typename T>
	block_list_mem<BLOCKSIZE,T> get_mem(block_list_iter<BLOCKSIZE,T>& it)
	{
		return it.blockListMem;
	}

	template <u32 BLOCKSIZE,typename T>
	const block_list_mem<BLOCKSIZE,T> get_mem(const block_list_iter<BLOCKSIZE,T>& it)
	{
		return it.blockListMem;
	}

	template <u32 BLOCKSIZE,typename T>
	b32 is_coll_valid(const block_list_iter<BLOCKSIZE,T>& it)
	{
		return it.blockList!=0;
	}

	template <u32 BLOCKSIZE,typename T>
	b32 is_mem_valid(const block_list_iter<BLOCKSIZE,T>& it)
	{
		return is_coll_valid(it)&&
			it.blockListMem==it.blockList->list;
	}

	template <u32 BLOCKSIZE,typename T>
	b32 vindicate_mem(block_list_iter<BLOCKSIZE,T>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it)&&
				is_coll_valid(it))
		{
			it.blockListMem=it.blockList->list;
		}
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,block_list_iter<BLOCKSIZE,T>& it)
	{
		return !is_coll_valid(destroy_sllist(it.blockList,a));
	}
}
