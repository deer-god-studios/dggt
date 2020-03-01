#ifndef _DGGT_MEM_STACK_ALLOC_H_

#include "dggt_mem_utils.h"
#include "dggt_mem_allocator.h"

namespace dggt
{
	struct stack_alloc
	{
		allocator<> baseAlloc;
		void* buff;
		msize buffSize;
		msize used;
		stack_state prevState;
		u32 stateCount;

		stack_alloc();
		stack_alloc(void* ptr,msize size);
	};

	void* alloc(stack_alloc* a,msize size);

	b32 free(stack_alloc* a,void* ptr,msize size);
	
	b32 clear(stack_alloc* a);

	b32 owns(const stack_alloc* a,const void* ptr,msize size);

	stack_state save_stack(stack_alloc* a);

	b32 restore_stack(stack_alloc* a,stack_state state);

	b32 is_stack_balanced(const stack_alloc* a);

	msize used_mem(const stack_alloc* a);

	msize available_mem(const stack_alloc* a);

	template <typename T>
	T* alloc(stack_alloc* a,u32 count);

	template <typename T>
	b32 free(stack_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 owns(const stack_alloc* a,const T* ptr,u32 count);
}

#include "dggt_mem_stack_alloc.inl"

#define _DGGT_MEM_STACK_ALLOC_H_
#endif
