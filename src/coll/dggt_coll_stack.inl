
namespace dggt
{

	namespace dggt_internal_
	{
		template <typename T>
		inline stack_iter<T> default_iter(stack<T>* stk)
		{
			return stack_iter<T>{0,blk<T>(),stk};
		}
	}

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
			--current;
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
		return stk!=0;
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
		return table[get_head(this)-index];
	}

	template <typename T>
	const T& stack<T>::operator[](u32 index) const
	{
		return table[get_head(this)-index];
	}

	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,A* alloc)
	{
		stack_iter<T> result=dggt_internal_::default_iter(stk);
		if (stk)
		{
			u32 count=get_count(stk);
			u32 capacity=get_capacity(stk);
			if (count+1>capacity) // needs resizing.
			{
				result=resize(stk,2*capacity,alloc);
				capacity=get_capacity(stk);
			}
			else if (stk)
			{
				result.table=stk->table;
			}
			else if (is_coll_valid(result))
			{
				result.table=stk->table;
			}
			capacity=get_capacity(stk);
			if (is_coll_valid(result))
			{
				zero_struct<T>(stk->table.mem+count);
				++stk->count;
				result.current=get_head(stk);
				if (is_mem_valid(result))
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
		if (stk)
		{
			stk->table.mem[get_head(stk)]=val;
		}
		return result;
	}

	template <typename T,typename A>
	stack_iter<T> pop(stack<T>* stk,A* alloc)
	{
		stack_iter<T> result=dggt_internal_::default_iter(stk);
		u32 count=get_count(stk);
		if (stk&&count)
		{
			--stk->count;
			count=get_count(stk);
			u32 capacity=get_capacity(stk);
			if (count&&get_load_factor<real32>(stk)<0.25f)
			{
				result=resize(stk,capacity/2,alloc);
			}
			else if (is_coll_valid(result))
			{
				result.table=stk->table;
			}
			if (is_mem_valid(result))
			{
				result=get_iter(stk);
			}
		}
		return result;
	}

	template <typename T>
	stack_iter<T> peek(stack<T>* stk)
	{
		return get(stk,0);
	}

	template <typename T>
	stack_iter<T> get(stack<T>* stk,u32 index)
	{
		return get_iter(stk,index);
	}

	template <typename T>
	stack_iter<T> get_iter(stack<T>* stk,u32 index)
	{
		stack_iter<T> result=dggt_internal_::default_iter(stk);
		if (stk)
		{
			result.current=get_head(stk)-index;
			result.table=stk->table;
			result.stk=stk;
		}
		return result;
	}

	template <typename T>
	u32 get_count(const stack<T>* stk)
	{
		return stk?stk->count:0;
	}

	template <typename T,typename A>
	stack_iter<T> clear(stack<T>* stk,A* alloc)
	{
		stack_iter<T> result=dggt_internal_::default_iter(stk);
		if (stk)
		{
			blk<T> table=stk->table;
			result.table=table;
			stk->table=blk<T>();
			stk->count=0;
			if (alloc->free(table))
			{
				result.table=blk<T>();
			}
		}
		return result;
	}

	template <typename T>
	u32 get_capacity(const stack<T>* stk)
	{
		return stk?stk->table.count:0;
	}

	template <typename T,typename F>
	F get_load_factor(const stack<T>* stk)
	{
		return stk?F(get_count(stk))/F(get_capacity(stk)):F(0);
	}

	template <typename T,typename A>
	stack_iter<T> resize(stack<T>* stk,u32 newCapacity,A* alloc)
	{
		stack_iter<T> result={0,blk<T>(),stk};
		if (stk&&alloc)
		{
			result.table=stk->table;
			u32 oldCapacity=get_capacity(stk);
			blk<T> newTable=alloc->template alloc<T>(newCapacity);
			if (newTable.mem)
			{
				blk<T> oldTable=stk->table;
				u32 copyCount=min<u32>(oldCapacity,newCapacity);
				blk_cpy(newTable,oldTable,copyCount);
				stk->table=newTable;
				if (alloc->free(oldTable))
				{
					result.table=newTable;
				}
			}
		}
		return result;
	}

	template <typename T>
	u32 get_head(const stack<T>* stk)
	{
		return stk?(get_count(stk)==0?0:get_count(stk)-1):0;
	}
}
