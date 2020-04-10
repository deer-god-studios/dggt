
namespace dggt
{
	template <typename T>
	b32 vindicate_mem(dllist_iter<T>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&!is_mem_valid(it))
		{
			it->mem=it.coll->mem;
			it->current=it->mem->pair.head;
			it->prev=it->current->prev;
			result=true;
		}
		return result;
	}

	template <typename T>
	b32 is_end(const dllist_iter<T>& it)
	{
		return it.current==0;
	}

	template <typename T>
	b32 is_begin(const dllist_iter<T>& it)
	{
		return it.prev==0;
	}

	template <typename T>
	b32 advance(dllist_iter<T>& it)
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
	b32 decrement(dllist_iter<T>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			it.current=it.current->prev;
			result=true;
		}
		return result;
	}

	template <typename T>
	T& get(dllist_iter<T>& it)
	{
		return it.current->val;
	}

	template <typename T>
	const T& get(const dllist_iter<T>& it)
	{
		return it.current->val;
	}

	template <typename T>
	T* get_ptr(dllist_iter<T>& it)
	{
		return &it.current->val;
	}

	template <typename T>
	const T* get_ptr(const dllist_iter<T>& it)
	{
		return &it.current->val;
	}

	template <typename T>
	b32 is_mem_valid(const dllist_iter<T>& it)
	{
		return is_coll_valid(it)&&it.mem.valid;
	}
}
