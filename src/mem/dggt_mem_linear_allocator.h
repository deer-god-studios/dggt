#ifndef _DGGT_MEM_LINEAR_ALLOCATOR_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	template <u32 SIZE=0>
	struct linear_allocator:allocator<linear_allocator<SIZE>>
	{
		linear_allocator<0> a_; 
		ubyte buff[SIZE];
		linear_allocator();
	};

	template <>
	struct linear_allocator<0>
	{
		vblk buff;
		msize used;
		linear_allocator();
		linear_allocator(void* ptr,msize size);
		explicit linear_allocator(vblk block);
	};

	// lin_alloc

	typedef linear_allocator<0> lin_alloc;

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

	// lin_stalloc<SIZE>

	template <u32 SIZE>
	using lin_stalloc=linear_allocator<SIZE>;

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
}

#include "dggt_mem_linear_allocator.inl"

#define _DGGT_MEM_LINEAR_ALLOCATOR_H_
#endif
