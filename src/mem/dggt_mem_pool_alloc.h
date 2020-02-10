#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{

	template <u32 BLOCKSIZE,u32 BUFFSIZE=0>
	struct pool_alloc_:allocator<pool_allocator_<BUFFSIZE>>
	{
		pool_alloc_<0> a_;
		ubyte buff[BUFFSIZE];
		pool_alloc_();
	};

	template <u32 BLOCKSIZE>
	struct pool_alloc_<BLOCKSIZE,0>
	{
		vblk buff;
		msize used;
		pool_block* pool;
		pool_alloc_();
		pool_alloc_(void* ptr,msize size);
		explicit pool_alloc(vblk block);
	};

	typedef pool_alloc_<0> pool_alloc;

	void* alloc(pool_alloc* a,msize* size=0);

	vblk alloc(pool_alloc* a,msize size=4);

	template <typename T>
	T* alloc(pool_alloc* a,u32* count=0);

	template <typename T>
	blk<T> alloc(pool_alloc* a,u32 count=1);

	b32 free(pool_alloc* a,void* ptr,msize size);

	b32 free(pool_alloc* a,vblk block);

	template <typename T>
	b32 free(pool_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 free(pool_alloc* a,blk<T> block);

	b32 clear(pool_alloc* a);

	b32 owns(const pool_alloc* a,const void* ptr,msize size);

	b32 owns(const pool_alloc* a,const vblk block);

	template <typename T>
	b32 owns(const pool_alloc* a,const T* ptr,u32 count);

	template <typename T>
	b32 owns(const pool_alloc* a,const blk<T> block);

	msize available_mem(const pool_alloc* a);
	
	msize used_mem(const pool_alloc* a);

	stack_state save_stack(pool_alloc* a);

	b32 restore_stack(pool_alloc* a,stack_state state);

	b32 is_stack_balanced(pool_alloc* a);

	// free_list_stalloc<SIZE>

	template <u32 SIZE>
	using pool_stalloc=pool_alloc_<SIZE>;

	template <u32 SIZE>
	void* alloc(pool_stalloc<SIZE>* a,msize* size=0);
	
	template <u32 SIZE>
	vblk alloc(pool_stalloc<SIZE>* a,msize size=4);

	template <u32 SIZE,typename T>
	T* alloc(pool_stalloc<SIZE>* a,u32* count=0);
	
	template <u32 SIZE,typename T>
	blk<T> alloc(pool_stalloc<SIZE>* a,u32 count=1);

	template <u32 SIZE>
	b32 free(pool_stalloc<SIZE>* a,void* ptr,msize size);
	
	template <u32 SIZE>
	b32 free(pool_stalloc<SIZE>* a,vblk block);

	template <u32 SIZE,typename T>
	b32 free(pool_stalloc<SIZE>* a,T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 free(pool_stalloc<SIZE>* a,blk<T> block);

	template <u32 SIZE>
	b32 clear(pool_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 owns(const pool_stalloc<SIZE>* a,const void* ptr,msize size);

	template <u32 SIZE>
	b32 owns(const pool_stalloc<SIZE>* a,const vblk block);

	template <u32 SIZE,typename T>
	b32 owns(const pool_stalloc<SIZE>* a,const T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 owns(const pool_stalloc<SIZE>* a,const blk<T> block);

	template <u32 SIZE>
	msize available_mem(const pool_stalloc<SIZE>* a);

	template <u32 SIZE>
	msize used_mem(const pool_stalloc<SIZE>* a);

	template <u32 SIZE>
	stack_state save_stack(pool_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 restore_stack(pool_stalloc<SIZE>* a,stack_state state);

	template <u32 SIZE>
	b32 is_stack_balanced(pool_stalloc<SIZE>* a);
}

#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
