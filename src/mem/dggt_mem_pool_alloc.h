#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_lin_alloc.h"
#include "dggt_mem_store_alloc.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	typedef store_block pool_block;

	struct pool_alloc
		:lin_alloc
	{
		store_alloc store;

		pool_alloc();
		pool_alloc(alloc_func_table* tbl,vpage buff,msize blockSize);
		pool_alloc(vpage buff,msize blockSize);
		pool_alloc(void* buff,msize size,msize blockSize);
	};

	namespace internal_
	{
		void* pool_alloc_malloc(allocator* a,msize size);
		vpage pool_alloc_malloc_vpage(allocator* a,msize size);
		b32 pool_alloc_free(allocator* a,void* ptr,msize size);
		b32 pool_alloc_free(allocator* a,vpage& pge);
		b32 pool_alloc_clear(allocator* a);
		msize pool_alloc_get_available(const allocator* a);
	}
}

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
