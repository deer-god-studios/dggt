#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	// TODO: use blocksize instead of next pointer.
	template <u32 BLOCKSIZE=NO_BLOCKSIZE>
	struct pool_block
	:member_val_or<BLOCKSIZE>
	{
		pool_block* next;
		pool_block();
	};

	template <u32 BLOCKSIZE=NO_BLOCKSIZE>
	struct allocator<ALLOC_T_POOL,BLOCKSIZE>
	:member_val_or<BLOCKSIZE>
	{
		static const u32 TYPE=ALLOC_T_POOL;
		blkv buff;
		msize used;
		pool_block<BLOCKSIZE>* pool;
		allocator();
		allocator(msize blockSize=DEF_BLOCKSIZE);
		allocator(void* ptr,msize size,msize blockSize=DEF_BLOCKSIZE);
		explicit allocator(blkv block,msize blockSize=DEF_BLOCKSIZE);
	};

	template <u32 BLOCKSIZE=NO_BLOCKSIZE>
	using pool_alloc=allocator<ALLOC_T_POOL,BLOCKSIZE>;

	template <u32 BUFFSIZE=DEF_BUFFSIZE,u32 BLOCKSIZE=NO_BLOCKSIZE>
	struct allocator<ALLOC_T_POOL,BUFFSIZE,BLOCKSIZE>
	{
		static const u32 TYPE=ALLOC_T_POOL;
		pool_alloc<BLOCKSIZE> a_;
		ubyte buff[BUFFSIZE];
		allocator(msize blockSize=DEF_BLOCKSIZE);
	};

	template <u32 BUFFSIZE=DEF_BUFFSIZE,u32 BLOCKSIZE=0>
	using pool_stalloc=allocator<ALLOC_T_POOL,BUFFSIZE,BLOCKSIZE>;

	template <u32 BLOCKSIZE>
	void* alloc(pool_alloc<BLOCKSIZE>* a,msize* size=0);

	template <u32 BLOCKSIZE>
	blkv alloc(pool_alloc<BLOCKSIZE>* a,msize size=4);

	template <typename T,u32 BLOCKSIZE>
	T* alloc(pool_alloc<BLOCKSIZE>* a,u32* count=0);

	template <typename T,u32 BLOCKSIZE>
	blk<T> alloc(pool_alloc<BLOCKSIZE>* a,u32 count=1);

	template <u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,void* ptr,msize size);

	template <u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,blkv block);

	template <typename T,u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,blk<T> block);

	template <u32 BLOCKSIZE>
	b32 clear(pool_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const void* ptr,msize size);

	template <u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const blkv block);

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const blk<T> block);

	template <u32 BLOCKSIZE>
	msize available_mem(const pool_alloc<BLOCKSIZE>* a);
	
	template <u32 BLOCKSIZE>
	msize used_mem(const pool_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	stack_state save_stack(pool_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	b32 restore_stack(pool_alloc<BLOCKSIZE>* a,stack_state state);

	template <u32 BLOCKSIZE>
	b32 is_stack_balanced(pool_alloc<BLOCKSIZE>* a);

	template <u32 BLOCKSIZE>
	u32 get_block_size(pool_alloc<BLOCKSIZE>* a);

	// pool_stalloc<SIZE>


	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	void* alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,msize* size=0);
	
	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	blkv alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,msize size=4);

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	T* alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,u32* count=0);
	
	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	blk<T> alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,u32 count=1);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,void* ptr,msize size);
	
	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,blkv block);

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,blk<T> block);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 clear(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,const void* ptr,msize size);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,const blkv block);

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,const T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,const blk<T> block);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	msize available_mem(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	msize used_mem(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	stack_state save_stack(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 restore_stack(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,stack_state state);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 is_stack_balanced(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a);

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	u32 get_block_size(pool_alloc<BLOCKSIZE,BUFFSIZE>* a);


}

#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
