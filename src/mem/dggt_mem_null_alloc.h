#ifndef _DGGT_MEM_NULL_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct null_alloc
	{
		null_alloc();
	};

	void* malloc(null_alloc* a,msize size=0);

	b32 free(null_alloc* a,void* ptr,msize size=0);
	
	b32 clear(null_alloc* a);

	b32 owns(const null_alloc* a,const void* ptr,msize size=0);

	stack_state save_stack(null_alloc* a);

	b32 restore_stack(null_alloc* a,stack_state state);

	b32 is_stack_balanced(const null_alloc* a);

	msize used_mem(const null_alloc* a);

	msize available_mem(const null_alloc* a);

	template <typename T>
	T* malloc(null_alloc* a,msize size=0);

	template <typename T>
	b32 free(null_alloc* a,T* ptr,msize size=0);

	template <typename T>
	b32 owns(const null_alloc* a,const T* ptr,msize size=0);
}

#include "dggt_mem_null_alloc.inl"

#define _DGGT_MEM_NULL_ALLOC_H_
#endif
