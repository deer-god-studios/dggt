#ifndef _DGGT_MEM_AUTOSTACK_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	struct autostack_alloc
		:allocator
	{
		stack_alloc& a;
		stack_state prevState;

		autostack_alloc(autostack_alloc& other);
		autostack_alloc(stack_alloc& other);

		autostack_alloc& operator=(const autostack_alloc& rhs);
		autostack_alloc& operator=(const stack_alloc& rhs);
		~autostack_alloc();
	};

	namespace internal_
	{
		b32 stack_alloc_free(allocator* a,void* ptr,msize size);
		b32 stack_alloc_free(allocator* a,vpage& pge);
		stack_state stack_alloc_save_state(allocator* a);
		b32 stack_alloc_restore_state(allocator* a,stack_state state);
		b32 stack_alloc_is_stack_balanced(allocator* a);
	}
}

#define _DGGT_MEM_AUTOSTACK_H_
#endif
