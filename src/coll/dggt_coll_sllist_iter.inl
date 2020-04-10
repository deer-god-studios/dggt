
namespace dggt
{
	template <typename T>
	b32 vindicate_mem(sllist_iter<T>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&!is_mem_valid(it))
		{
			it.mem=it.coll->mem;
			it.current=it.coll->mem.head;
			result=true;
		}
		return result;
	}

	template <typename T>
	b32 is_end(const sllist_iter<T>& it)
	{
		return it.current==0;
	}

	template <typename T>
	b32 advance(sllist_iter<T>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			it.current=it.current->next;
			result=true;
		}
		return result;
	}

	template <typename T>
	T& get(sllist_iter<T>& it)
	{
		return it.current->val;
	}

	template <typename T>
	const T& get(const sllist_iter<T>& it)
	{
		return it.current->val;
	}

	template <typename T>
	T* get_ptr(sllist_iter<T>& it)
	{
		return &it.current->val;
	}

	template <typename T>
	const T* get_ptr(const sllist_iter<T>& it)
	{
		return &it.current->val;
	}

	template <typename T>
	b32 is_mem_valid(const sllist_iter<T>& it)
	{
		return is_mem_valid((iterator<T,sllist_mem<T>,sllist<T>>&)it)&&
			it.mem.valid;
	}
}
