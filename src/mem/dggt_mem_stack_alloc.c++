#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	namespace internal_
	{
		b32 stack_alloc_free(allocator* a,void* ptr,msize size)
		{
			b32 result=false;
			stack_alloc* stackAlloc=(stack_alloc*)a;
			if (stackAlloc)
			{
				if (ptr_add(get_buff_ptr(stackAlloc),get_used(stackAlloc))==
						ptr_add(ptr,size))
				{
					stackAlloc->used-=size;
					if (stackAlloc->prevState==get_used(stackAlloc))
					{
						restore_stack(stackAlloc,get_used(stackAlloc));
					}
				}
			}
			return result;
		}

		b32 stack_alloc_free(allocator* a,vpage& pge)
		{
			return stack_alloc_free(a,pge.ptr,pge.size);
		}

		stack_state stack_alloc_save_state(allocator* a)
		{
			stack_state result=SAVE_STACK_FAIL;
			stack_alloc* stackAlloc=(stack_alloc*)a;
			if (stackAlloc)
			{
				result=stackAlloc->used;
				stackAlloc->prevState=result;
				++stackAlloc->stateCount;
			}
			return result;
		}

		b32 stack_alloc_restore_state(allocator* a,stack_state state)
		{
			b32 result=false;
			stack_alloc* stackAlloc=(stack_alloc*)a;
			if (stackAlloc)
			{
				if (state!=SAVE_STACK_FAIL&&
						state==stackAlloc->prevState)
				{
					stackAlloc->used=state;
					--stackAlloc->stateCount;
				}
			}
			return result;
		}

		b32 stack_alloc_is_stack_balanced(const allocator* a)
		{
			b32 result=false;
			stack_alloc* stackAlloc=(stack_alloc*)a;
			if (stackAlloc)
			{
				return stackAlloc->stateCount==0;
			}
			return result;
		}

		global alloc_func_table STACK_ALLOC_TABLE=
		{
			lin_alloc_malloc,
			lin_alloc_malloc_vpage,
			stack_alloc_free,
			stack_alloc_free,
			lin_alloc_clear,
			buff_alloc_owns,
			buff_alloc_owns,
			stack_alloc_save_state,
			stack_alloc_restore_state,
			stack_alloc_is_stack_balanced,
			lin_alloc_get_used,
			lin_alloc_get_available,
			buff_alloc_get_capacity,
			buff_alloc_get_buff,
			buff_alloc_get_buff,
			buff_alloc_get_buff_ptr,
			buff_alloc_get_buff_ptr
		};
	}

	stack_alloc::stack_alloc(alloc_func_table* tbl,vpage buff)
		:lin_alloc(tbl,buff),prevState(0),stateCount(0) { }

	stack_alloc::stack_alloc()
		:stack_alloc(&internal_::STACK_ALLOC_TABLE,vpage()) { }

	stack_alloc::stack_alloc(vpage buff)
		:stack_alloc(&internal_::STACK_ALLOC_TABLE,buff) { }

	stack_alloc::stack_alloc(void* buff,msize size)
		:stack_alloc(vpage(buff,size)) { }
}
