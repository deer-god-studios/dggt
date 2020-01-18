
namespace dggt
{

	template <typename T>
	b32 iter<T,stack<T>,blk<T>>::is_end() const
	{
		return !is_coll_valid()||
			(is_coll_valid()&&current>=stk->table.count)||
			(is_coll_valid()&&!is_mem_valid());
	}

	template <typename T>
	b32 iter<T,stack<T>,blk<T>>::next()
	{
		b32 result=0;
		if (!is_end())
		{
			++current;
		}
		return result;
	}

	template <typename T>
	T& iter<T,stack<T>,blk<T>>::get()
	{
		return table[current];
	}

	template <typename T>
	const T& iter<T,stack<T>,blk<T>>::get() const
	{
		return table[current];
	}

	template <typename T>
	T* iter<T,stack<T>,blk<T>>::get_ptr()
	{
		return table.mem+current;
	}

	template <typename T>
	const T* iter<T,stack<T>,blk<T>>::get_ptr() const
	{
		return table.mem+current;
	}

	template <typename T>
	blk<T> iter<T,stack<T>,blk<T>>::get_mem()
	{
		return table;
	}

	template <typename T>
	const blk<T> iter<T,stack<T>,blk<T>>::get_mem() const
	{
		return table;
	}

	template <typename T>
	b32 iter<T,stack<T>,blk<T>>::is_coll_valid() const
	{
		return stk;
	}

	template <typename T>
	b32 iter<T,stack<T>,blk<T>>::is_mem_valid() const
	{
		return is_coll_valid()&&
			table==stk->table;
	}

	template <typename T>
	b32 iter<T,stack<T>,blk<T>>::vindicate_mem()
	{
		b32 result=0;
		if (!is_mem_valid()&&
				is_coll_valid())
		{
			table=stk->table;
			result=1;
		}
		return result;
	}

	template <typename T>
	T& stack<T>::operator[](u32 index)
	{
		return table[index];
	}

	template <typename T>
	const T& stack<T>::operator[](u32 index) const
	{
		return table[index];
	}

	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,A* alloc)
	{
		stack_iter<T> result=stack_iter<T>{0,0,stk};
		if (stk)
		{
			u32 count=get_count(stk);
			b32 resized=0;
			b32 freedOld=0;
			if (count>=get_capacity(stk)) // needs resizing.
			{
				result=resize(stk,2*count,alloc);
				resized=is_coll_valid(result);
				freedOld=is_mem_valid(result);
			}
			if (resized)
			{
				++stk->count;
				if (freedOld)
				{
					result=get_iter(stk);
				}
			}
		}
		return result;
	}
	
	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,const T& val,A* alloc)
	{
		stack_iter<T> result=push(stk,alloc);
		if (result.stk&&
				result.table==result.stk->table) // yeesh
		{
			result.get()=val;
		}
		return result;
	}

	template <typename T,typename A>
	stack_iter<T> pop(stack<T>* stk,A* alloc)
	{
		stack_iter<T> result=stack_iter<T>{0,0,stk};
		u32 count=get_count(stk);
		if (stk&&count)
		{
			--stk->count;
			count=get_count(stk);
			b32 resized=0;
			b32 freedOld=0;
			if (get_load_factor<real32>(stk)<0.25f)
			{
				result=resize(stk,count/2,alloc);
				resized=is_coll_valid(result);
				freedOld=is_mem_valid(result);
			}
			if (freedOld)
			{
				result=get_iter(stk);
			}
		}
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
		if (stk)
		{
			result.current=0;
			result.table=stk->table;
		}
		return result;
	}

	template <typename T>
	u32 get_count(const stack<T>* stk)
	{
		return stk?stk->count:0;
	}

	template <typename T>
	u32 get_capacity(const stack<T>* stk)
	{
		return stk?stk->table.count:0;
	}

	template <typename T,typename F>
	F get_load_factor(const stack<T>* stk)
	{
		return stk?F(get_count(stk))/F(get_capacity):F(0);
	}

	template <typename T,typename A>
	stack_iter<T> resize(stack<T>* stk,u32 newCapacity,A* alloc)
	{
		stack_iter<T> result={0,0,stk};
		if (stk&&alloc)
		{
			result.table=stk->table;
			u32 oldCapacity=get_capacity(stk);
			blk<T> newTable=alloc->alloc(newCapacity);
			if (newTable.mem)
			{
				blk<T> oldTable=stk->table;
				u32 copyCount=min<u32>(oldCapacity,newCapacity);
				blk_cpy(newTable,oldTable,copyCount);
				if (alloc->free(oldTable))
				{
					result.table=newTable;
				}
			}
		}
		return result;
	}
}
