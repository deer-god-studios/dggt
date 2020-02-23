#ifndef _DGGT_MEM_NULL_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct null_alloc
	{
		allocator baseAlloc;

		null_alloc()
			: baseAlloc(allocator(ALLOC_T_NULL)) { }
	};

	void* alloc(null_alloc* a,msize size=0) { return 0; }

	template <typename T>
	T* alloc(null_alloc* a,u32 count=0) { return 0; }

	b32 free(null_alloc* a,void* ptr,msize size) { return false; }

	template <typename T>
	b32 free(null_alloc* a,T* ptr,u32 count) { return false; }

	b32 clear(null_alloc* a) { return true; }
	
	b32 owns(const null_alloc* a,const void* ptr,msize size)
	{
		return ptr==0&&size==0;
	}

	template <typename T>
	b32 owns(const null_alloc* a,const T* ptr,u32 count)
	{
		return ptr==0&&count==0;
	}

	stack_state save_stack(null_alloc* a) { return SAVE_STACK_FAIL; }

	b32 restore_stack(null_alloc* a,stack_state state) { return false; }

	b32 is_stack_balanced(null_alloc* a) { return true; }

	msize used_mem(null_alloc* a) { return 0; }

	msize available_mem(null_alloc* a) { return 0; }
}

#define _DGGT_MEM_NULL_ALLOC_H_
#endif
