
namespace dggt
{
	template <typename T>
	b32 is_end(stack_iter<T>& it)
	{
		return current<0;
	}

	template <typename T>
	b32 advance(stack_iter<T>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			--it.current;
		}
		return result;
	}

	template <typename T>
	T& get(stack_iter<T>& it)
	{
		return it.mem[it.current];
	}

	template <typename T>
	const T& get(const stack_iter<T>& it)
	{
		return it.mem[it.current];
	}

	template <typename T>
	T* get_ptr(stack_iter<T>& it)
	{
		return it.mem+it.current;
	}

	template <typename T>
	const T* get_ptr(stack_iter<T>& it)
	{
		return it.mem+it.current;
	}

	template <typename T>
	b32 is_mem_valid(const stack_iter<T>& it)
	{
		return is_coll_valid(it)&&
			it.table==it.stk->table;
	}

	template <typename T>
	b32 vindicate_mem(stack_iter<T>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it)&&
				is_coll_valid(it))
		{
			it.table=it.stk->table;
			result=false;
		}
		return result;
	}
}
