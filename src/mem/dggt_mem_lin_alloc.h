#ifndef _DGGT_MEM_LINEAR_ALLOCATOR_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<ALLOC_T_LINEAR>
	{
		static const u32 TYPE=ALLOC_T_LINEAR;
		blkv buff;
		msize used;
		allocator();
		allocator(void* ptr,msize size);
		explicit allocator(blkv block);
	};

	template <u32 BUFFSIZE>
	struct allocator<ALLOC_T_LINEAR,BUFFSIZE>
	{
		static const u32 TYPE=ALLOC_T_LINEAR;
		allocator<ALLOC_T_LINEAR> a_; 
		ubyte buff[BUFFSIZE];
		allocator();
	};

	typedef allocator<ALLOC_T_LINEAR> lin_alloc;

	void* alloc(lin_alloc* a,msize* size=0);

	blkv alloc(lin_alloc* a,msize size=4);

	template <typename T>
	T* alloc(lin_alloc* a,u32* count=0);

	template <typename T>
	blk<T> alloc(lin_alloc* a,u32 count=1);

	b32 free(lin_alloc* a,void* ptr,msize size);

	b32 free(lin_alloc* a,blkv block);

	template <typename T>
	b32 free(lin_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 free(lin_alloc* a,blk<T> block);

	b32 clear(lin_alloc* a);

	b32 owns(const lin_alloc* a,const void* ptr,msize size);

	b32 owns(const lin_alloc* a,const blkv block);

	template <typename T>
	b32 owns(const lin_alloc* a,const T* ptr,u32 count);

	template <typename T>
	b32 owns(const lin_alloc* a,const blk<T> block);

	msize available_mem(const lin_alloc* a);
	
	msize used_mem(const lin_alloc* a);

	stack_state save_stack(lin_alloc* a);

	b32 restore_stack(lin_alloc* a,stack_state state);

	b32 is_stack_balanced(lin_alloc* a);

	// lin_stalloc<BUFFSIZE>

	template <u32 BUFFSIZE>
	using lin_stalloc=allocator<ALLOC_T_LINEAR,BUFFSIZE>;

	template <u32 BUFFSIZE>
	void* alloc(lin_stalloc<BUFFSIZE>* a,msize* size=0);
	
	template <u32 BUFFSIZE>
	blkv alloc(lin_stalloc<BUFFSIZE>* a,msize size=4);

	template <u32 BUFFSIZE,typename T>
	T* alloc(lin_stalloc<BUFFSIZE>* a,u32* count=0);
	
	template <u32 BUFFSIZE,typename T>
	blk<T> alloc(lin_stalloc<BUFFSIZE>* a,u32 count=1);

	template <u32 BUFFSIZE>
	b32 free(lin_stalloc<BUFFSIZE>* a,void* ptr,msize size);
	
	template <u32 BUFFSIZE>
	b32 free(lin_stalloc<BUFFSIZE>* a,blkv block);

	template <u32 BUFFSIZE,typename T>
	b32 free(lin_stalloc<BUFFSIZE>* a,T* ptr,u32 count);

	template <u32 BUFFSIZE,typename T>
	b32 free(lin_stalloc<BUFFSIZE>* a,blk<T> block);

	template <u32 BUFFSIZE>
	b32 clear(lin_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	b32 owns(const lin_stalloc<BUFFSIZE>* a,const void* ptr,msize size);

	template <u32 BUFFSIZE>
	b32 owns(const lin_stalloc<BUFFSIZE>* a,const blkv block);

	template <u32 BUFFSIZE,typename T>
	b32 owns(const lin_stalloc<BUFFSIZE>* a,const T* ptr,u32 count);

	template <u32 BUFFSIZE,typename T>
	b32 owns(const lin_stalloc<BUFFSIZE>* a,const blk<T> block);

	template <u32 BUFFSIZE>
	msize available_mem(const lin_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	msize used_mem(const lin_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	stack_state save_stack(lin_stalloc<BUFFSIZE>* a);

	template <u32 BUFFSIZE>
	b32 restore_stack(lin_stalloc<BUFFSIZE>* a,stack_state state);

	template <u32 BUFFSIZE>
	b32 is_stack_balanced(lin_stalloc<BUFFSIZE>* a);
}

#include "dggt_mem_lin_alloc.inl"

#define _DGGT_MEM_LINEAR_ALLOCATOR_H_
#endif
