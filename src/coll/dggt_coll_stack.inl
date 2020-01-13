
#include "math/dggt_math_utils.h"

namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T,alloc_t A>
		b32 stack_blk_free(blk<T> block,allocator<A>* alloc)
		{
			return alloc->free(block);
		}
		template <typename T>
		b32 stack_blk_free(blk<T> block,allocator<alloc_t::LINEAR>* alloc)
		{
			return 0;
		}

		template <typename T>
		b32 stack_blk_free(blk<T> block,allocator<alloc_t::STACK>* alloc)
		{
			return 0;
		}

		template <typename T,alloc_t A>
		blk<T> stack_blk_alloc(u32 count,allocator<A>* alloc)
		{
			blk<T> result=NULL_BLK<T>;
			if (alloc)
			{
				result=alloc->alloc<T>(count);
			}
			return result;
		}

		template <typename T,alloc_t A>
		blk<T> blk_resize(blk<T> mem,u32 newCount,
				allocator<A>* alloc)
		{
			blk<T> result=mem;
			u32 oldCount=mem.count;
			if (newCount!=newCount)
			{
				u32 copySize=min<u32>(oldSize,newSize);
				blk<T> newBlock=stack_blk_alloc<T>(count,alloc);
				if (newBlock.mem)
				{
					result=newBlock;
					blk_cpy(result,mem,copySize);
					stack_blk_free(mem,alloc);
				}
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
		stack_iter<T> result=stack_iter<T>();
		if (stk)
		{
			if (count>=capacity)
			{
				blk<T> newBlock=dggt_internal_::blk_resize(
						stk->mem,
						2*stk->capacity,
						alloc);
			}
		}

		++stk->count;
	}
}
