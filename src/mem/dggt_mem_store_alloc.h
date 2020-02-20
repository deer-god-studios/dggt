#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	struct store_block
	{
		store_block* next;
	};

	template <u32 BLOCKSIZE=NO_BLOCKSIZE>
	struct allocator<ALLOC_T_STORE,BLOCKSIZE>
	: member_val_or<BLOCKSIZE>
	{
		static const u32 TYPE=ALLOC_T_STORE;
		store_block* head;
		u32 blockCount;

		allocator();
		allocator(msize blockSize);
	};

	template <u32 BLOCKSIZE>
	using store_alloc=allocator<ALLOC_T_STORE,BLOCKSIZE>;

	template <u32 BLOCKSIZE>
	void* alloc(store_alloc<BLOCKSIZE>* a,msize* size=0);

	template <u32 BLOCKSIZE>
	blkv alloc(store_alloc<BLOCKSIZE>* a,msize size=4);

	template <typename T,u32 BLOCKSIZE>
	T* alloc(store_alloc<BLOCKSIZE>* a,u32* count=0);

	template <typename T,u32 BLOCKSIZE>
	blk<T> alloc(store_alloc<BLOCKSIZE>* a,u32 count=1);

	template <u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,void* ptr,msize size);

	template <u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,blkv block);

	template <typename T,u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,blk<T> block);

	template <u32 BLOCKSIZE>
	b32 clear(store_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const void* ptr,msize size);

	template <u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const blkv block);

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const blk<T> block);

	template <u32 BLOCKSIZE>
	msize available_mem(const store_alloc<BLOCKSIZE>* a);
	
	template <u32 BLOCKSIZE>
	msize used_mem(const store_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	stack_state save_stack(store_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	b32 restore_stack(store_alloc<BLOCKSIZE>* a,stack_state state);

	template <u32 BLOCKSIZE>
	b32 is_stack_balanced(store_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	u32 get_block_size(store_alloc<BLOCKSIZE>* a);
}
#include "dggt_mem_store_alloc.inl"

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
