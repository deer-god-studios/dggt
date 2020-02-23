#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct pool_block
	{
		pool_block* next;
	};

	struct pool_alloc
	{
		allocator baseAlloc;
		void* buff;
		msize bSize;
		msize buffSize;
		msize used;
		u32 blockCount;
		pool_block* pool;
		pool_alloc(msize blockSize=4);
		pool_alloc(void* ptr,msize size,msize blockSize=DEF_BLOCKSIZE);
	};

	void* alloc(pool_alloc* a,msize size=4);

	template <typename T>
	T* alloc(pool_alloc* a,u32 count=1);

	b32 free(pool_alloc* a,void* ptr,msize size=4);

	template <typename T>
	b32 free(pool_alloc* a,T* ptr,u32 count=1);

	b32 clear(pool_alloc* a);

	b32 owns(const pool_alloc* a,const void* ptr,msize size=4);

	template <typename T>
	b32 owns(const pool_alloc* a,const T* ptr,u32 count=1);

	msize available_mem(const pool_alloc* a);
	
	msize used_mem(const pool_alloc* a);

	stack_state save_stack(pool_alloc* a);

	b32 restore_stack(pool_alloc* a,stack_state state);

	b32 is_stack_balanced(pool_alloc* a);
}

#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
