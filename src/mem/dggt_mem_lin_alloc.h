#ifndef _DGGT_MEM_LINEAR_ALLOCATOR_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct lin_alloc
	{
		allocator baseAlloc;
		void* buff;
		msize buffSize;
		msize used;
		lin_alloc();
		lin_alloc(void* ptr,msize size);
	};

	void* alloc(lin_alloc* a,msize size=4);

	template <typename T>
	T* alloc(lin_alloc* a,u32 count=1);

	b32 free(lin_alloc* a,void* ptr,msize size);

	template <typename T>
	b32 free(lin_alloc* a,T* ptr,u32 count);

	b32 clear(lin_alloc* a);

	b32 owns(const lin_alloc* a,const void* ptr,msize size);

	template <typename T>
	b32 owns(const lin_alloc* a,const T* ptr,u32 count);

	msize available_mem(const lin_alloc* a);
	
	msize used_mem(const lin_alloc* a);

	stack_state save_stack(lin_alloc* a);

	b32 restore_stack(lin_alloc* a,stack_state state);

	b32 is_stack_balanced(const lin_alloc* a);
}

#include "dggt_mem_lin_alloc.inl"

#define _DGGT_MEM_LINEAR_ALLOCATOR_H_
#endif
