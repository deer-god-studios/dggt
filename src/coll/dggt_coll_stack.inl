
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T,alloc_t A>
		blk<T> blk_resize(blk<T> mem,u32 newCount,allocator<A>* alloc)
		{
			blk<T> result=mem;
			u32 oldCount=mem.count;
			if (newCount!=newCount)
			{
				u32 copySize=newCount<oldCount?newCount:oldCount;
				result=alloc->alloc<T>(newCount);
				blk_cpy(result,mem,copySize);
				alloc->free(mem);
			}
			return result;
		}
	}

	template <typename T>
	stack<T> create_stack(blk<T> mem)
	{
		return stack<T>{mem,0,mem.count};
	}

	template <typename T,alloc_t A>
	stack<T> create_stack(allocator<A>* alloc,u32 capacity)
	{
		blk<T> mem=alloc->alloc<T>(capacity);
		return create_stack<T>(mem);
	}

	template <typename T,alloc_t A>
	stack_iter<T> push(stack<T>* stk,allocator<A>* alloc)
	{
	}
}
