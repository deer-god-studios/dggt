#ifndef _DGGT_MEM_STACK_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct stack_alloc:
		allocator<alloc_stack>
	{
		stack_alloc(void* ptr,msize size):
			allocator(alloc_stack(vpage(ptr,size),0)) { }
		stack_alloc() : stack_alloc(0,0) { }
	};

	void* malloc(stack_alloc* a,msize size);

	b32 free(stack_alloc* a,void* ptr,msize size);
	
	b32 clear(stack_alloc* a);
}

#define _DGGT_MEM_STACK_ALLOC_H_
#endif
