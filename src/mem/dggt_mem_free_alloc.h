#ifndef _DGGT_MEM_FREE_ALLOC_H_

#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	struct free_block
	{
		free_block* next;
		msize size;
	};

	struct free_alloc:
		lin_alloc
	{
		free_block* freeList;

		free_alloc();
		free_alloc(alloc_func_table* tbl,vpage buff);
		free_alloc(void* ptr,msize size);
		free_alloc(vpage buff);
	};

	namespace internal_
	{
		void* free_alloc_malloc(allocator* a,msize size);
		vpage free_alloc_malloc_vpage(allocator* a,msize size);
		b32 free_alloc_free(allocator* a,void* ptr,msize size);
		b32 free_alloc_free(allocator* a,vpage& pge);
		b32 free_alloc_clear(allocator* a);
	}
}

#define _DGGT_MEM_FREE_ALLOC_H_
#endif
