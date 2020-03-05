
namespace dggt
{
	template <typename T>
	T& stack_iter<T>::operator*()
	{
		return *table.ptr;
	}

	template <typename T>
	const T& stack_iter<T>::operator*() const
	{
		return *table.ptr;
	}

	template <typename T>
	stack_iter<T>& stack_iter<T>::operator++()
	{
		if (!is_end(this))
		{
			advance(this);
		}
		return *this;
	}

	template <typename T>
	stack_iter<T> stack_iter<T>::operator++(int)
	{
		stack_iter<T> result=*this;
		if (!is_end(this))
		{
			advance(this);
		}
		return result;
	}


	template <typename T>
	b32 is_end(stack_iter<T>* it)
	{
		return !is_coll_valid(it)||
			(is_coll_valid(it)&&it->current>=it->stk->table.count)||
			(is_coll_valid(it)&&!is_mem_valid(it));
	}

	template <typename T>
	b32 advance(stack_iter<T>* it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			--it->current;
		}
		return result;
	}

	template <typename T>
	T& get(stack_iter<T>* it)
	{
		return it->table[it->current];
	}

	template <typename T>
	const T& get(const stack_iter<T>* it)
	{
		return it->table[it->current];
	}

	template <typename T>
	T* get_ptr(stack_iter<T>* it)
	{
		return it->table.mem+it->current;
	}

	template <typename T>
	const T* get_ptr(stack_iter<T>* it)
	{
		return it->table.mem+it->current;
	}

	template <typename T>
	blk<T> get_mem(stack_iter<T>* it)
	{
		return it->table;
	}

	template <typename T>
	const blk<T> get_mem(const stack_iter<T>* it)
	{
		return it->table;
	}

	template <typename T>
	b32 is_coll_valid(const stack_iter<T>* it)
	{
		return it->stk!=0;
	}

	template <typename T>
	b32 is_mem_valid(const stack_iter<T>* it)
	{
		return is_coll_valid(it)&&
			it->table==it->stk->table;
	}

	template <typename T>
	b32 vindicate_mem(stack_iter<T>* it)
	{
		b32 result=false;
		if (!is_mem_valid(it)&&
				is_coll_valid(it))
		{
			it->table=it->stk->table;
			result=false;
		}
		return result;
	}
}
