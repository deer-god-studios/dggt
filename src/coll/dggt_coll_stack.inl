
namespace dggt
{

	template <typename T>
	b32 iter<T,stack<T>>::is_end() const
	{
		return current<capacity;
	}

	template <typename T>
	b32 iter<T,stack<T>>::next()
	{
		b32 result=0;
		if (!is_end())
		{
			++current;
		}
		return result;
	}

	template <typename T>
	T& iter<T,stack<T>>::get()
	{
		return stk->table[current];
	}

	template <typename T>
	const T& iter<T,stack<T>>::get() const
	{
		return stk->table[current];
	}

	template <typename T>
	T* iter<T,stack<T>>::get_ptr()
	{
		return stk->table.mem+current;
	}

	template <typename T>
	const T* iter<T,stack<T>>::get_ptr() const
	{
		return stk->table.mem+current;
	}

	template <typename T>
	blk<T> iter<T,stack<T>>::get_table()
	{
		return stk->table;
	}

	template <typename T>
	const blk<T> iter<T,stack<T>>::get_table() const
	{
		return stk->table;
	}

	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,A* alloc)
	{
		stack_iter<T> result=stack_iter<T>{0,0,stk};
		return result;
	}
	
	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,const T& val,A* alloc)
	{
		stack_iter<T> result=stack_iter<T>{0,0,stk};
		return result;
	}

	template <typename T>
	stack_iter<T> get(stack<T>* stk,u32 index)
	{
		stack_iter<T> result=stack_iter<T>{0,0,stk};
		return result;
	}

	template <typename T>
	stack_iter<T> get_iter(stack<T>* stk)
	{
		stack_iter<T> result=stack_iter<T>{0,0,stk};
		return result;
	}

	template <typename T>
	u32 get_count(const stack<T>* stk)
	{
		return 0;
	}

	template <typename T>
	u32 get_capacity(const stack<T>* stk)
	{
		return 0;
	}

	template <typename T,typename F>
	F get_load_factor(const stack<T>* stk)
	{
		return F(0);
	}

	template <typename T,typename A>
	b32 resize(const stack<T>* stk,u32 newCapacity,A* alloc)
	{
		return 0;
	}
}
