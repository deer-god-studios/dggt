#ifndef _DGGT_MEM_STACK_ALLOC_H_

#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	struct stack_alloc
		:allocator<stack_alloc>
	{
		lin_alloc linAlloc;
		stack_state prevState;
		msize stateCount;

		stack_alloc(void* ptr,msize size)
			: allocator<stack_alloc>(this),
			linAlloc(lin_alloc(ptr,size)),
			prevState(0),stateCount(0) { }
		stack_alloc(vpage pge) : stack_alloc(pge.ptr,pge.size) { }
		stack_alloc() : stack_alloc(0,0) { }
	};

	void* malloc(stack_alloc* a,msize size);

	b32 free(stack_alloc* a,void* ptr,msize size);
	
	b32 clear(stack_alloc* a);

	stack_state save_stack(stack_alloc* a);

	b32 restore_stack(stack_alloc* a);

	b32 is_stack_balanced(stack_alloc* a);

	void* get_buff_ptr(stack_alloc* a);

	const void* get_buff_ptr(const stack_alloc* a);

	msize get_used(const stack_alloc* a);

	msize get_available(const stack_alloc* a);

}

#define _DGGT_MEM_STACK_ALLOC_H_
#endif
