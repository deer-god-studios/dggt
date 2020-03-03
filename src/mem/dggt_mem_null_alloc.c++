#include "dggt_mem_null_alloc.h"

namespace dggt
{
	null_alloc::null_alloc() { }

	void* alloc(null_alloc* a,msize size)
	{
		return 0;
	}

	b32 free(null_alloc* a,void* ptr,msize size)
	{
		return owns(a,ptr,size);
	}
	
	b32 clear(null_alloc* a)
	{
		return true;
	}

	b32 owns(const null_alloc* a,const void* ptr,msize size)
	{
		return ptr==0&&size==0;
	}

	stack_state save_stack(null_alloc* a)
	{
		return SAVE_STACK_FAIL;
	}

	b32 restore_stack(null_alloc* a,stack_state state)
	{
		return false;
	}

	b32 is_stack_balanced(const null_alloc* a)
	{
		return true;
	}

	msize used_mem(const null_alloc* a)
	{
		return MAX_MSIZE;
	}

	msize available_mem(const null_alloc* a)
	{
		return 0;
	}
}
