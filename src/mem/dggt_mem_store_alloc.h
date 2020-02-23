#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct store_block
	{
		store_block* next;
	};

	struct store_alloc
	{
		allocator baseAlloc;
		store_block* head;
		u32 blockCount;
		msize blockSize;

		allocator(msize blockSize=DEF_BLOCKSIZE);
	};

	void* alloc(store_alloc* a,msize size=4);

	template <typename T>
	T* alloc(store_alloc* a,u32 count=1);

	b32 free(store_alloc* a,void* ptr,msize size=4);

	template <typename T>
	b32 free(store_alloc* a,T* ptr,u32 count=1);

	b32 clear(store_alloc* a);

	b32 owns(const store_alloc* a,const void* ptr,msize size=4);

	template <typename T>
	b32 owns(const store_alloc* a,const T* ptr,u32 count=1);

	msize available_mem(const store_alloc* a);
	
	msize used_mem(const store_alloc* a);

	stack_state save_stack(store_alloc* a);

	b32 restore_stack(store_alloc* a,stack_state state);

	b32 is_stack_balanced(store_alloc* a);

	u32 get_block_size(store_alloc* a);
}

#include "dggt_mem_store_alloc.inl"

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
