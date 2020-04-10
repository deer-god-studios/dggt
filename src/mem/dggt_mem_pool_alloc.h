#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_allocator.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	typedef mblock pool_block;

	template <msize BLOCKSIZE=0>
	struct pool_alloc
	{
		static_assert(BLOCKSIZE>=sizeof(pool_block));
		void* buff;
		msize buffSize;
		msize used;
		u32 blockCount;
		pool_block* pool;

		pool_alloc();
		pool_alloc(void* ptr,msize size);
	};

	template <>
	struct pool_alloc<>
	{
		void* buff;
		msize buffSize;
		msize used;
		u32 blockCount;
		msize blockSize;
		pool_block* pool;

		pool_alloc();
		pool_alloc(void* ptr,msize size,msize blockSize);
	};

	template <msize BLOCKSIZE>
	void* malloc(pool_alloc<BLOCKSIZE>* a,msize size=8);

	template <msize BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,void* ptr,msize size=8);
	
	template <msize BLOCKSIZE>
	b32 clear(pool_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const void* ptr,msize size);

	template <msize BLOCKSIZE>
	stack_state save_stack(pool_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	b32 restore_stack(pool_alloc<BLOCKSIZE>* a,stack_state state);

	template <msize BLOCKSIZE>
	b32 is_stack_balanced(const pool_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	msize used_mem(const pool_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	msize available_mem(const pool_alloc<BLOCKSIZE>* a);

	template <typename T,msize BLOCKSIZE>
	T* malloc(pool_alloc<BLOCKSIZE>* a,msize size=1);

	template <typename T,msize BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,T* ptr,msize size=1);

	template <typename T,msize BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const T* ptr,msize size=1);

	void* malloc(pool_alloc<>* a,msize size);

	b32 free(pool_alloc<>* a,void* ptr,msize size);
	
	b32 clear(pool_alloc<>* a);

	b32 owns(const pool_alloc<>* a,const void* ptr,msize size);

	stack_state save_stack(pool_alloc<>* a);

	b32 restore_stack(pool_alloc<>* a,stack_state state);

	b32 is_stack_balanced(const pool_alloc<>* a);
	
	msize used_mem(const pool_alloc<>* a);

	msize available_mem(const pool_alloc<>* a);

	template <typename T>
	T* malloc(pool_alloc<>* a,msize size=1);

	template <typename T>
	b32 free(pool_alloc<>* a,T* ptr,msize size=1);

	template <typename T>
	b32 owns(const pool_alloc<>* a,const T* ptr,msize size=1);
}

#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
