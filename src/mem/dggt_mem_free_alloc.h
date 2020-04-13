#ifndef _DGGT_MEM_FREE_ALLOC_H_

#include "dggt_mem_allocator.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	typedef smblock free_block;

	struct free_alloc
	{
		void* buff;
		msize buffSize;
		free_block* freeList;
		msize used;

		free_alloc();
		free_alloc(void* ptr,msize size);
	};

	void* malloc(free_alloc* a,msize size);

	b32 free(free_alloc* a,void* ptr,msize size);
	
	b32 clear(free_alloc* a);

	b32 owns(const free_alloc* a,const void* ptr,msize size);

	stack_state save_stack(free_alloc* a);

	b32 restore_stack(free_alloc* a,stack_state state);

	b32 is_stack_balanced(const free_alloc* a);

	msize used_mem(const free_alloc* a);

	msize available_mem(const free_alloc* a);

	template <typename T>
	T* malloc(free_alloc* a,msize size=1);

	template <typename T>
	b32 free(free_alloc* a,T* ptr,msize size=1);

	template <typename T>
	b32 owns(const free_alloc* a,const T* ptr,msize size=1);
}

#include "dggt_mem_free_alloc.inl"

#define _DGGT_MEM_FREE_ALLOC_H_
#endif
