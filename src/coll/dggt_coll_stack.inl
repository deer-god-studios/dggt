#include "mem/dggt_mem.h"

namespace dggt
{
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
	stack<T>::iter destroy_stack(stack<T>& stk,A* allocator)
	{
		stack<T>::iter result=stack<T>::iter(stk);
		result.mem=stk.mem;
		stk.count=0;
		if (free(allocator,stk.mem))
		{
			result=stack<T>::iter();
		}
		return result;
	}

	template <typename T,typename A>
	stack<T>::iter push(stack<T>& stk,A* alloc)
	{
		stack<T>::iter result=stack<T>::iter(stk);
		u32 count=get_count(stk);
		u32 capacity=get_capacity(stk);
		if (count+1>capacity) // needs resizing.
		{
			result=resize(stk,2*capacity,alloc);
			capacity=get_capacity(stk);
		}
		else
		{
			result.table=stk.table;
		}
		capacity=get_capacity(stk);
		if (result.is_coll_valid())
		{
			zero_struct<T>(stk.table.mem+count);
			++stk.count;
			result.current=get_head(stk);
			if (result.is_mem_valid())
			{
				result=get_iter(stk);
			}
		}
		return result;
	}
	
	template <typename T,typename A>
	stack<T>::iter push(stack<T>& stk,const T& val,A* alloc)
	{
		stack<T>::iter result=push(stk,alloc);
		stk.table.mem[get_head(stk)]=val;
		return result;
	}

	template <typename T,typename A>
	stack<T>::iter pop(stack<T>& stk,A* alloc)
	{
		stack<T>::iter result=stack<T>::iter(stk);
		u32 count=get_count(stk);
		if (count)
		{
			--stk.count;
			count=get_count(stk);
			u32 capacity=get_capacity(stk);
			if (count&&get_load_factor<real32>(stk)<0.25f)
			{
				result=resize(stk,capacity/2,alloc);
			}
			else if (result.is_coll_valid())
			{
				result.table=stk.table;
			}
			if (result.is_mem_valid())
			{
				result=get_iter(stk);
			}
		}
		return result;
	}

	template <typename T>
	stack<T>::iter peek(stack<T>& stk)
	{
		return get(stk,0);
	}

	template <typename T>
	stack<T>::iter get(stack<T>& stk,u32 index)
	{
		stack<T>::iter result=stack<T>::iter(stk);
		result=stack<T>::iter(stk,
				stack_key<T>((T*)stk.mem,get_count(stk),get_head(stk)-index);
		return result;
	}

	template <typename T>
	stack<T>::iter get_iter(stack<T>& stk,u32 index)
	{
		return get(stk,0);
	}

	template <typename T>
	u32 get_count(const stack<T>& stk)
	{
		return stk.count;
	}

	template <typename T,typename A>
	stack<T>::iter clear(stack<T>& stk,A* alloc)
	{
		stack<T>::iter result=stack<T>::iter(stk);
		blk<T> table=stk.table;
		result.table=table;
		stk.table=blk<T>();
		stk.count=0;
		if (alloc->free(table))
		{
			result.table=blk<T>();
		}
		return result;
	}

	template <typename T>
	u32 get_capacity(const stack<T>& stk)
	{
		return stk.table.count;
	}

	template <typename T,typename F>
	F get_load_factor(const stack<T>& stk)
	{
		return get_capacity(stk)?F(get_count(stk))/F(get_capacity(stk)):F(0);
	}

	template <typename T,typename A>
	stack<T>::iter resize(stack<T>& stk,u32 newCapacity,A* alloc)
	{
		stack<T>::iter result={0,blk<T>(),stk};
		if (alloc)
		{
			result.table=stk.table;
			u32 oldCapacity=get_capacity(stk);
			blk<T> newTable=alloc->template alloc<T>(newCapacity);
			if (newTable.mem)
			{
				blk<T> oldTable=stk.table;
				u32 copyCount=min<u32>(oldCapacity,newCapacity);
				blk_cpy(newTable,oldTable,copyCount);
				stk.table=newTable;
				if (alloc->free(oldTable))
				{
					result.table=newTable;
				}
			}
		}
		return result;
	}

	template <typename T>
	u32 get_head(const stack<T>& stk)
	{
		return get_count(stk)==0?0:get_count(stk)-1;
	}
}
