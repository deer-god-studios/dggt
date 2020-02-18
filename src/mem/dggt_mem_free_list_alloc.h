#ifndef _DGGT_MEM_FREE_LIST_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	struct free_block
	{
		msize size;
		free_block* next;
	};

	template <>
	struct allocator<ALLOC_T_FREE>
	{
		static const u32 TYPE=ALLOC_T_FREE;
		blkv buff;
		msize used;
		free_block* freeList;
		allocator();
		allocator(void* ptr,msize size);
		explicit allocator(blkv block);
	};

	typedef allocator<ALLOC_T_FREE> free_list_alloc;

	template <u32 BUFFSIZE=DEF_BUFFSIZE>
	struct allocator<ALLOC_T_FREE,BUFFSIZE>
	{
		static const u32 TYPE=ALLOC_T_FREE;
		free_list_alloc a_;
		ubyte buff[BUFFSIZE];
		allocator(msize blockSize=DEF_BLOCKSIZE);
	};

	template <u32 BUFFSIZE=DEF_BUFFSIZE>
	using free_list_stalloc=allocator<ALLOC_T_FREE,BUFFSIZE>;

	void* alloc(free_list_alloc* a,msize* size=0);

	blkv alloc(free_list_alloc* a,msize size=4);

	template <typename T>
	T* alloc(free_list_alloc* a,u32* count=0);

	template <typename T>
	blk<T> alloc(free_list_alloc* a,u32 count=1);
	
	b32 free(free_list_alloc* a,void* ptr,msize size);
	
	b32 free(free_list_alloc* a,blkv block);

	template <typename T>
	b32 free(free_list_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 free(free_list_alloc* a,blk<T> block);
	
	b32 clear(free_list_alloc* a);

	b32 owns(const free_list_alloc* a,const void* ptr,msize size);

	b32 owns(const free_list_alloc* a,const blkv block);

	template <typename T>
	b32 owns(const free_list_alloc* a,const T* ptr,u32 count);

	template <typename T>
	b32 owns(const free_list_alloc* a,const blk<T> block);
	
	msize available_mem(const free_list_alloc* a);
	
	msize used_mem(const free_list_alloc* a);
	
	stack_state save_stack(free_list_alloc* a);
	
	b32 restore_stack(free_list_alloc* a,stack_state state);

	b32 is_stack_balanced(free_list_alloc* a);

	// pool_stalloc<SIZE>

	template <u32 BUFFSIZE>
	void* alloc(free_list_stalloc<BUFFSIZE>* a,msize* size=0);
	
	template <u32 BUFFSIZE>
	blkv alloc(free_list_stalloc<BUFFSIZE>* a,msize size=4);

	template <typename T,u32 BUFFSIZE>
	T* alloc(free_list_stalloc<BUFFSIZE>* a,u32* count=0);
	
	template <typename T,u32 BUFFSIZE>
	blk<T> alloc(free_list_stalloc<BUFFSIZE>* a,u32 count=1);

	template <u32 BUFFSIZE>
	b32 free(free_list_stalloc<BUFFSIZE>* a,void* ptr,msize size);
	
	template <u32 BUFFSIZE>
	b32 free(free_list_stalloc<BUFFSIZE>* a,blkv block);

	template <typename T,u32 BUFFSIZE>
	b32 free(free_list_stalloc<BUFFSIZE>* a,T* ptr,u32 count);

	template <typename T,u32 BUFFSIZE>
	b32 free(free_list_stalloc<BUFFSIZE>* a,blk<T> block);

	template <u32 BUFFSIZE>
	b32 clear(free_list_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const void* ptr,msize size);

	template <u32 BUFFSIZE>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const blkv block);

	template <typename T,u32 BUFFSIZE>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const T* ptr,u32 count);

	template <typename T,u32 BUFFSIZE>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const blk<T> block);

	template <u32 BUFFSIZE>
	msize available_mem(const free_list_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	msize used_mem(const free_list_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	stack_state save_stack(free_list_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	b32 restore_stack(free_list_stalloc<BUFFSIZE>* a,stack_state state);

	template <u32 BUFFSIZE>
	b32 is_stack_balanced(free_list_stalloc<BUFFSIZE>* a);
}

#include "dggt_mem_free_list_alloc.inl"

#define _DGGT_MEM_FREE_LIST_ALLOC_H_
#endif
