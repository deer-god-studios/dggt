#ifndef _DGGT_MEM_LINEAR_ALLOCATOR_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<ALLOC_T_LINEAR>
	{
		vblk buff;
		msize used;
		allocator();
		allocator(void* ptr,msize size);
		explicit allocator(vblk block);
	};

	template <u32 SIZE>
	struct allocator<ALLOC_T_LINEAR,SIZE>
	{
		allocator<ALLOC_T_LINEAR> a_; 
		ubyte buff[SIZE];
		allocator();
	};

	typedef allocator<ALLOC_T_LINEAR> lin_alloc;

	void* alloc(lin_alloc* a,msize* size=0);

	vblk alloc(lin_alloc* a,msize size=4);

	template <typename T>
	T* alloc(lin_alloc* a,u32* count=0);

	template <typename T>
	blk<T> alloc(lin_alloc* a,u32 count=1);

	b32 free(lin_alloc* a,void* ptr,msize size);

	b32 free(lin_alloc* a,vblk block);

	template <typename T>
	b32 free(lin_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 free(lin_alloc* a,blk<T> block);

	b32 clear(lin_alloc* a);

	b32 owns(const lin_alloc* a,const void* ptr,msize size);

	b32 owns(const lin_alloc* a,const vblk block);

	template <typename T>
	b32 owns(const lin_alloc* a,const T* ptr,u32 count);

	template <typename T>
	b32 owns(const lin_alloc* a,const blk<T> block);

	msize available_mem(const lin_alloc* a);
	
	msize used_mem(const lin_alloc* a);

	stack_state save_stack(lin_alloc* a);

	b32 restore_stack(lin_alloc* a,stack_state state);

	b32 is_stack_balanced(lin_alloc* a);

	// lin_stalloc<SIZE>

	template <u32 SIZE>
	using lin_stalloc=allocator<ALLOC_T_LINEAR,SIZE>;

	template <u32 SIZE>
	void* alloc(lin_stalloc<SIZE>* a,msize* size=0);
	
	template <u32 SIZE>
	vblk alloc(lin_stalloc<SIZE>* a,msize size=4);

	template <u32 SIZE,typename T>
	T* alloc(lin_stalloc<SIZE>* a,u32* count=0);
	
	template <u32 SIZE,typename T>
	blk<T> alloc(lin_stalloc<SIZE>* a,u32 count=1);

	template <u32 SIZE>
	b32 free(lin_stalloc<SIZE>* a,void* ptr,msize size);
	
	template <u32 SIZE>
	b32 free(lin_stalloc<SIZE>* a,vblk block);

	template <u32 SIZE,typename T>
	b32 free(lin_stalloc<SIZE>* a,T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 free(lin_stalloc<SIZE>* a,blk<T> block);

	template <u32 SIZE>
	b32 clear(lin_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 owns(const lin_stalloc<SIZE>* a,const void* ptr,msize size);

	template <u32 SIZE>
	b32 owns(const lin_stalloc<SIZE>* a,const vblk block);

	template <u32 SIZE,typename T>
	b32 owns(const lin_stalloc<SIZE>* a,const T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 owns(const lin_stalloc<SIZE>* a,const blk<T> block);

	template <u32 SIZE>
	msize available_mem(const lin_stalloc<SIZE>* a);

	template <u32 SIZE>
	msize used_mem(const lin_stalloc<SIZE>* a);

	template <u32 SIZE>
	stack_state save_stack(lin_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 restore_stack(lin_stalloc<SIZE>* a,stack_state state);

	template <u32 SIZE>
	b32 is_stack_balanced(lin_stalloc<SIZE>* a);
}

#include "dggt_mem_lin_alloc.inl"

#define _DGGT_MEM_LINEAR_ALLOCATOR_H_
#endif
