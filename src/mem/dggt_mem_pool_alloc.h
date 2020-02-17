#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{

	template <u32 SIZE=0>
	struct pool_block
	{
		pool_block<SIZE>* next;
	};

	template <u32 BLOCKSIZE=0>
	struct allocator<ALLOC_T_POOL,BLOCKSIZE>
	{
		vblk buff;
		msize used;
		pool_block* pool;
		allocator();
		allocator(msize blockSize=4);
		allocator(void* ptr,msize size);
		explicit allocator(vblk block);
	};

	template <u32 BLOCKSIZE>
	using pool_alloc=allocator<ALLOC_T_POOL,BLOCKSIZE>;

	template <u32 BUFFSIZE,u32 BLOCKSIZE=0>
	struct allocator<ALLOC_T_POOL,BLOCKSIZE,BUFFSIZE>
	{
		pool_alloc<BLOCKSIZE> a_;
		ubyte buff[BUFFSIZE];
		allocator();
		allocator(
	};

	template <u32 BLOCKSIZE>
	using pool_alloc=allocator<ALLOC_T_POOL,BLOCKSIZE>;

	template <u32 BLOCKSIZE>
	void* alloc(pool_alloc* a,msize* size=0);

	template <u32 BLOCKSIZE>
	vblk alloc(pool_alloc* a,msize size=4);

	template <typename T,u32 BLOCKSIZE>
	T* alloc(pool_alloc* a,u32* count=0);

	template <typename T,u32 BLOCKSIZE>
	blk<T> alloc(pool_alloc* a,u32 count=1);

	template <u32 BLOCKSIZE>
	b32 free(pool_alloc* a,void* ptr,msize size);

	template <u32 BLOCKSIZE>
	b32 free(pool_alloc* a,vblk block);

	template <typename T,u32 BLOCKSIZE>
	b32 free(pool_alloc* a,T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE>
	b32 free(pool_alloc* a,blk<T> block);

	template <u32 BLOCKSIZE>
	b32 clear(pool_alloc* a);

	template <u32 BLOCKSIZE>
	b32 owns(const pool_alloc* a,const void* ptr,msize size);

	template <u32 BLOCKSIZE>
	b32 owns(const pool_alloc* a,const vblk block);

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const pool_alloc* a,const T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const pool_alloc* a,const blk<T> block);

	template <u32 BLOCKSIZE>
	msize available_mem(const pool_alloc* a);
	
	template <u32 BLOCKSIZE>
	msize used_mem(const pool_alloc* a);

	template <u32 BLOCKSIZE>
	stack_state save_stack(pool_alloc* a);

	template <u32 BLOCKSIZE>
	b32 restore_stack(pool_alloc* a,stack_state state);

	template <u32 BLOCKSIZE>
	b32 is_stack_balanced(pool_alloc* a);

	// free_list_stalloc<SIZE>

	template <u32 BLOCKSIZE,u32 SIZE>
	using pool_stalloc=allocator<ALLOC_T_POOL,BLOCKSIZE,SIZE>;

	template <u32 BLOCKSIZE,u32 SIZE>
	void* alloc(pool_stalloc<BLOCKSIZE,SIZE>* a,msize* size=0);
	
	template <u32 BLOCKSIZE,u32 SIZE>
	vblk alloc(pool_stalloc<BLOCKSIZE,SIZE>* a,msize size=4);

	template <typename T,u32 BLOCKSIZE,u32 SIZE>
	T* alloc(pool_stalloc<BLOCKSIZE,SIZE>* a,u32* count=0);
	
	template <typename T,u32 BLOCKSIZE,u32 SIZE>
	blk<T> alloc(pool_stalloc<BLOCKSIZE,SIZE>* a,u32 count=1);

	template <u32 BLOCKSIZE,u32 SIZE>
	b32 free(pool_stalloc<BLOCKSIZE,SIZE>* a,void* ptr,msize size);
	
	template <u32 BLOCKSIZE,u32 SIZE>
	b32 free(pool_stalloc<BLOCKSIZE,SIZE>* a,vblk block);

	template <typename T,u32 BLOCKSIZE,u32 SIZE>
	b32 free(pool_stalloc<BLOCKSIZE,SIZE>* a,T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE,u32 SIZE>
	b32 free(pool_stalloc<BLOCKSIZE,SIZE>* a,blk<T> block);

	template <u32 BLOCKSIZE,u32 SIZE>
	b32 clear(pool_stalloc<BLOCKSIZE,SIZE>* a);

	template <u32 BLOCKSIZE,u32 SIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,SIZE>* a,const void* ptr,msize size);

	template <u32 BLOCKSIZE,u32 SIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,SIZE>* a,const vblk block);

	template <typename T,u32 BLOCKSIZE,u32 SIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,SIZE>* a,const T* ptr,u32 count);

	template <typename T,u32 BLOCKSIZE,u32 SIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,SIZE>* a,const blk<T> block);

	template <u32 BLOCKSIZE,u32 SIZE>
	msize available_mem(const pool_stalloc<BLOCKSIZE,SIZE>* a);

	template <u32 BLOCKSIZE,u32 SIZE>
	msize used_mem(const pool_stalloc<BLOCKSIZE,SIZE>* a);

	template <u32 BLOCKSIZE,u32 SIZE>
	stack_state save_stack(pool_stalloc<BLOCKSIZE,SIZE>* a);

	template <u32 BLOCKSIZE,u32 SIZE>
	b32 restore_stack(pool_stalloc<BLOCKSIZE,SIZE>* a,stack_state state);

	template <u32 BLOCKSIZE,u32 SIZE>
	b32 is_stack_balanced(pool_stalloc<BLOCKSIZE,SIZE>* a);
}

#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
