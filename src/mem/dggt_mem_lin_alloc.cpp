#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	lin_alloc::lin_alloc()
	{
		baseAlloc=allocator(ALLOC_T_LIN);
		buff=0;
		buffSize=0;
		used=0;
	}

	lin_alloc::lin_alloc(void* ptr,msize size)
		:lin_alloc()
	{
		buff=ptr;
		buffSize=size;
	}

	void* alloc(lin_alloc* a,msize size)
	{
		void* result=0;

		if (size)
		{
			if (a->used+size<=a->buffSize)
			{
				result=ptr_add(a->buff,a->used);
				a->used+=size;
			}
		}
		return result;
	}

	b32 free(lin_alloc* a,void* ptr,msize size)
	{
		return 0;
	}

	b32 clear(lin_alloc* a)
	{
		a->used=0;
		return 1;
	}

	b32 owns(const lin_alloc* a,const void* ptr,msize size)
	{
		return ptr>=a->buff&&
			ptr_add(ptr,size)<=ptr_add(a->buff,a->buffSize);
	}

	msize available_mem(const lin_alloc* a)
	{
		return a->buffSize-a->used;
	}

	msize used_mem(const lin_alloc* a)
	{
		return a->used;
	}

	stack_state save_stack(lin_alloc* a)
	{
		return SAVE_STACK_FAIL;
	}

	b32 restore_stack(lin_alloc* a,stack_state state)
	{
		return false;
	}

	b32 is_stack_balanced(const lin_alloc* a)
	{
		return true;
	}
}
