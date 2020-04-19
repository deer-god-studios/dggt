#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct store_block
	{
		store_block* next;
	};

	struct store_alloc
		: allocator
	{
		store_block* store;
		msize bCount;
		msize bSize;

		store_alloc();
		store_alloc(alloc_func_table* tbl,msize blockSize);
		store_alloc(msize blockSize);
	};

	namespace internal_
	{
		void* store_alloc_malloc(allocator* a,msize size);
		vpage store_alloc_malloc_vpage(allocator* a,msize size);
		b32 store_alloc_free(allocator* a,void* ptr,msize size);
		b32 store_alloc_free(allocator* a,vpage& pge);
		b32 store_alloc_clear(allocator* a);
		b32 store_alloc_owns(const allocator* a,const void* ptr,msize size);
		b32 store_alloc_owns(const allocator* a,const vpage& pge);
		msize store_alloc_get_used(const allocator* a);
		msize store_alloc_get_available(const allocator* a);
		msize store_alloc_get_capacity(const allocator* a);
	}
}

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
