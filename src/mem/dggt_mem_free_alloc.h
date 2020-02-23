#ifndef _DGGT_MEM_FREE_LIST_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct free_block
	{
		msize size;
		free_block* next;
	};

	struct free_alloc
	{
		allocator baseAlloc;
		void* buff;
		msize buffSize
		msize used;
		free_block* freeList;
		free_alloc();
		free_alloc(void* ptr,msize size);
	};

	void* alloc(free_alloc* a,msize size=4);

	template <typename T>
	T* alloc(free_alloc* a,u32 count=1);

	b32 free(free_alloc* a,void* ptr,msize size);
	
	template <typename T>
	b32 free(free_alloc* a,T* ptr,u32 count);

	b32 clear(free_alloc* a);

	b32 owns(const free_alloc* a,const void* ptr,msize size);

	template <typename T>
	b32 owns(const free_alloc* a,const T* ptr,u32 count);

	msize available_mem(const free_alloc* a);
	
	msize used_mem(const free_alloc* a);
	
	stack_state save_stack(free_alloc* a);
	
	b32 restore_stack(free_alloc* a,stack_state state);

	b32 is_stack_balanced(free_alloc* a);
}

#include "dggt_mem_free_alloc.inl"

#define _DGGT_MEM_FREE_LIST_ALLOC_H_
#endif
