#ifndef _DGGT_MEM_FREE_LIST_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{

	template <u32 SIZE=0>
	struct free_list_alloc_:allocator<free_list_alloc_<SIZE>>
	{
		free_list_alloc_<0> a_;
		ubyte buff[SIZE];
		free_list_alloc_();
	};

	template <>
	struct free_list_alloc_<0>
	{
		vblk buff;
		msize used;
		free_block* freeList;
		free_list_alloc_();
		free_list_alloc_(void* ptr,msize size);
		explicit free_list_alloc_(vblk block);
	};

	typedef free_list_alloc_<0> free_list_alloc;

	void* alloc(free_list_alloc* a,msize* size=0);

	vblk alloc(free_list_alloc* a,msize size=4);

	template <typename T>
	T* alloc(free_list_alloc* a,u32* count=0);

	template <typename T>
	blk<T> alloc(free_list_alloc* a,u32 count=1);

	b32 free(free_list_alloc* a,void* ptr,msize size);

	b32 free(free_list_alloc* a,vblk block);

	template <typename T>
	b32 free(free_list_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 free(free_list_alloc* a,blk<T> block);

	b32 clear(free_list_alloc* a);

	b32 owns(const free_list_alloc* a,const void* ptr,msize size);

	b32 owns(const free_list_alloc* a,const vblk block);

	template <typename T>
	b32 owns(const free_list_alloc* a,const T* ptr,u32 count);

	template <typename T>
	b32 owns(const free_list_alloc* a,const blk<T> block);

	msize available_mem(const free_list_alloc* a);
	
	msize used_mem(const free_list_alloc* a);

	stack_state save_stack(free_list_alloc* a);

	b32 restore_stack(free_list_alloc* a,stack_state state);

	b32 is_stack_balanced(free_list_alloc* a);

	// free_list_stalloc<SIZE>

	template <u32 SIZE>
	using free_list_stalloc=free_list_alloc_<SIZE>;

	template <u32 SIZE>
	void* alloc(free_list_stalloc<SIZE>* a,msize* size=0);
	
	template <u32 SIZE>
	vblk alloc(free_list_stalloc<SIZE>* a,msize size=4);

	template <u32 SIZE,typename T>
	T* alloc(free_list_stalloc<SIZE>* a,u32* count=0);
	
	template <u32 SIZE,typename T>
	blk<T> alloc(free_list_stalloc<SIZE>* a,u32 count=1);

	template <u32 SIZE>
	b32 free(free_list_stalloc<SIZE>* a,void* ptr,msize size);
	
	template <u32 SIZE>
	b32 free(free_list_stalloc<SIZE>* a,vblk block);

	template <u32 SIZE,typename T>
	b32 free(free_list_stalloc<SIZE>* a,T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 free(free_list_stalloc<SIZE>* a,blk<T> block);

	template <u32 SIZE>
	b32 clear(free_list_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 owns(const free_list_stalloc<SIZE>* a,const void* ptr,msize size);

	template <u32 SIZE>
	b32 owns(const free_list_stalloc<SIZE>* a,const vblk block);

	template <u32 SIZE,typename T>
	b32 owns(const free_list_stalloc<SIZE>* a,const T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 owns(const free_list_stalloc<SIZE>* a,const blk<T> block);

	template <u32 SIZE>
	msize available_mem(const free_list_stalloc<SIZE>* a);

	template <u32 SIZE>
	msize used_mem(const free_list_stalloc<SIZE>* a);

	template <u32 SIZE>
	stack_state save_stack(free_list_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 restore_stack(free_list_stalloc<SIZE>* a,stack_state state);

	template <u32 SIZE>
	b32 is_stack_balanced(free_list_stalloc<SIZE>* a);
}

#include "dggt_mem_free_list_alloc.inl"

#define _DGGT_MEM_FREE_LIST_ALLOC_H_
#endif
