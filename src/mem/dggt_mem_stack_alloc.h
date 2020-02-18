#ifndef _DGGT_MEM_STACK_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<ALLOC_T_STACK>
	{
		static const u32 TYPE=ALLOC_T_STACK;
		blkv buff;
		msize used;
		u32 stateCount;
		stack_state prevState;
		allocator();
		allocator(void* ptr,msize size);
		explicit allocator(blkv block);
	};


	template <u32 SIZE>
	struct allocator<ALLOC_T_STACK,SIZE>
	{
		static const u32 TYPE=ALLOC_T_STACK;
		allocator<ALLOC_T_STACK> a_;
		ubyte buff[SIZE];
		allocator();
	};

	// stack_alloc
	typedef allocator<ALLOC_T_STACK> stack_alloc;

	void* alloc(stack_alloc* a,msize* size=0);

	blkv alloc(stack_alloc* a,msize size=4);

	template <typename T>
	T* alloc(stack_alloc* a,u32* count=0);

	template <typename T>
	blk<T> alloc(stack_alloc* a,u32 count=1);

	b32 free(stack_alloc* a,void* ptr,msize size);

	b32 free(stack_alloc* a,blkv block);

	template <typename T>
	b32 free(stack_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 free(stack_alloc* a,blk<T> block);

	b32 clear(stack_alloc* a);

	b32 owns(const stack_alloc* a,const void* ptr,msize size);

	b32 owns(const stack_alloc* a,const blkv block);

	template <typename T>
	b32 owns(const stack_alloc* a,const T* ptr,u32 count);

	template <typename T>
	b32 owns(const stack_alloc* a,const blk<T> block);

	msize available_mem(const stack_alloc* a);
	
	msize used_mem(const stack_alloc* a);

	stack_state save_stack(stack_alloc* a);

	b32 restore_stack(stack_alloc* a,stack_state state);

	b32 is_stack_balanced(stack_alloc* a);

	// stack_stalloc

	template <u32 SIZE>
	using stack_stalloc=allocator<ALLOC_T_STACK,SIZE>;
	
	template <u32 SIZE>
	void* alloc(stack_stalloc<SIZE>* a,msize* size=0);
	
	template <u32 SIZE>
	blkv alloc(stack_stalloc<SIZE>* a,msize size=4);

	template <u32 SIZE,typename T>
	T* alloc(stack_stalloc<SIZE>* a,u32* count=0);
	
	template <u32 SIZE,typename T>
	blk<T> alloc(stack_stalloc<SIZE>* a,u32 count=1);

	template <u32 SIZE>
	b32 free(stack_stalloc<SIZE>* a,void* ptr,msize size);
	
	template <u32 SIZE>
	b32 free(stack_stalloc<SIZE>* a,blkv block);

	template <u32 SIZE,typename T>
	b32 free(stack_stalloc<SIZE>* a,T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 free(stack_stalloc<SIZE>* a,blk<T> block);

	template <u32 SIZE>
	b32 clear(stack_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 owns(const stack_stalloc<SIZE>* a,const void* ptr,msize size);

	template <u32 SIZE>
	b32 owns(const stack_stalloc<SIZE>* a,const blkv block);

	template <u32 SIZE,typename T>
	b32 owns(const stack_stalloc<SIZE>* a,const T* ptr,u32 count);

	template <u32 SIZE,typename T>
	b32 owns(const stack_stalloc<SIZE>* a,const blk<T> block);

	template <u32 SIZE>
	msize available_mem(const stack_stalloc<SIZE>* a);

	template <u32 SIZE>
	msize used_mem(const stack_stalloc<SIZE>* a);

	template <u32 SIZE>
	stack_state save_stack(stack_stalloc<SIZE>* a);

	template <u32 SIZE>
	b32 restore_stack(stack_stalloc<SIZE>* a,stack_state state);

	template <u32 SIZE>
	b32 is_stack_balanced(stack_stalloc<SIZE>* a);
}

#include "dggt_mem_stack_alloc.inl"

#define _DGGT_MEM_STACK_ALLOC_H_
#endif
