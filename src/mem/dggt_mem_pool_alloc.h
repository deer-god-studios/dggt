#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_utils.h"
#include "dggt_mem_allocator.h"
#include "dggt_mem_block.h"

namespace dggt
{
	typedef mem_block pool_block;

	template <msize BLOCKSIZE=0>
	struct pool_alloc
	{
		static_assert(BLOCKSIZE>=sizeof(pool_block));
		allocator<BLOCKSIZE> baseAlloc;
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
		allocator<> baseAlloc;
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
	void* alloc(pool_alloc<BLOCKSIZE>* a,msize size);

	template <msize BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,void* ptr,msize size);
	
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
	T* alloc(pool_alloc<BLOCKSIZE>* a,u32 count);

	template <typename T,msize BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,T* ptr,u32 count);

	template <typename T,msize BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const T* ptr,u32 count);

	void* alloc(pool_alloc<>* a,msize size);

	b32 free(pool_alloc<>* a,void* ptr,msize size);
	
	b32 clear(pool_alloc<>* a);

	b32 owns(const pool_alloc<>* a,const void* ptr,msize size);

	stack_state save_stack(pool_alloc<>* a);

	b32 restore_stack(pool_alloc<>* a,stack_state state);

	b32 is_stack_balanced(const pool_alloc<>* a);
	
	msize used_mem(const pool_alloc<>* a);

	msize available_mem(const pool_alloc<>* a);

	template <typename T>
	T* alloc(pool_alloc<>* a,u32 count);

	template <typename T>
	b32 free(pool_alloc<>* a,T* ptr,u32 count);

	template <typename T>
	b32 owns(const pool_alloc<>* a,const T* ptr,u32 count);
}

#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
