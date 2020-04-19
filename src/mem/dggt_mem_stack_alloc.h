#ifndef _DGGT_MEM_STACK_ALLOC_H_

#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	struct stack_alloc
		:lin_alloc
	{
		stack_state prevState;
		msize stateCount;

		stack_alloc();
		stack_alloc(alloc_func_table* tbl,vpage buff);
		stack_alloc(vpage buff);
		stack_alloc(void* buff,msize size);
	};

	namespace internal_
	{
		b32 stack_alloc_free(allocator* a,void* ptr,msize size);
		b32 stack_alloc_free(allocator* a,vpage& pge);
		stack_state stack_alloc_save_state(allocator* a);
		b32 stack_alloc_restore_state(allocator* a,stack_state state);
		b32 stack_alloc_is_stack_balanced(const allocator* a);
	}
}

#define _DGGT_MEM_STACK_ALLOC_H_
#endif
