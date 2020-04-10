#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	typedef mblock store_block;

	template <msize BLOCKSIZE=0>
	struct store_alloc
	{
		static_assert(BLOCKSIZE>=sizeof(store_block));
		store_block* head;
		u32 blockCount;

		store_alloc();
	};

	template <>
	struct store_alloc<0>
	{
		store_block* head;
		u32 blockCount;
		msize blockSize;

		store_alloc();
		store_alloc(msize blockSize);
	};

	template <msize BLOCKSIZE>
	void* malloc(store_alloc<BLOCKSIZE>* a,msize size);

	template <msize BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,void* ptr,msize size);

	template <msize BLOCKSIZE>
	b32 clear(store_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const void* ptr,msize size);

	template <msize BLOCKSIZE>
	stack_state save_stack(store_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	b32 restore_stack(store_alloc<BLOCKSIZE>* a,stack_state state);

	template <msize BLOCKSIZE>
	b32 is_stack_balanced(const store_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	msize used_mem(const store_alloc<BLOCKSIZE>* a);

	template <msize BLOCKSIZE>
	msize available_mem(const store_alloc<BLOCKSIZE>* a);

	template <typename T,msize BLOCKSIZE>
	T* malloc(store_alloc<BLOCKSIZE>* a,msize size=1);

	template <typename T,msize BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,T* ptr,msize size=1);

	template <typename T,msize BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const T* ptr,msize size=1);

	msize available_mem(const store_alloc<>* a);

	msize used_mem(const store_alloc<>* a);

	b32 is_stack_balanced(const store_alloc<>* a);

	b32 restore_stack(store_alloc<>* a,stack_state state);

	stack_state save_stack(store_alloc<>* a);

	b32 owns(const store_alloc<>* a,const void* ptr,msize size);

	b32 clear(store_alloc<>* a);

	b32 free(store_alloc<>* a,void* ptr,msize size);

	void* malloc(store_alloc<>* a,msize size);

	template <typename T>
	b32 owns(const store_alloc<>* a,const T* ptr,msize size=1);

	template <typename T>
	b32 free(store_alloc<>* a,T* ptr,msize size=1);

	template <typename T>
	T* malloc(store_alloc<>* a,msize size=1);
}

#include "dggt_mem_store_alloc.inl"

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
