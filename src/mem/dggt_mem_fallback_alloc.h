#ifndef _DGGT_MEM_FALLBACK_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct fallback_alloc
	{
		allocator baseAlloc;

		allocator* p;
		allocator* f;

		fallback_alloc();
		fallback_alloc(allocator* primary,allocator* fallback);
	};

	void* alloc(fallback_alloc* a,msize size=4);

	template <typename T>
	T* alloc(fallback_alloc* a,u32 count=1);

	b32 free(fallback_alloc* a,void* ptr,msize size=4);

	template <typename T>
	b32 free(fallback_alloc* a,T* ptr,u32 count=1);

	b32 clear(fallback_alloc* a);

	b32 owns(const fallback_alloc* a,const void* ptr,msize size=4);

	template <typename T>
	b32 owns(const fallback_alloc* a,const T* ptr,u32 count=1);

	msize available_mem(const fallback_alloc* a);

	msize used_mem(const fallback_alloc* a);

	stack_state save_stack(fallback_alloc* a);

	b32 restore_stack(fallback_alloc* a,stack_state state);

	b32 is_stack_balanced(fallback_alloc* a);

}

#include "dggt_mem_fallback_alloc.inl"

#define _DGGT_MEM_FALLBACK_ALLOC_H_
#endif
