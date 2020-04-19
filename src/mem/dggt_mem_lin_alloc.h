#ifndef _DGGT_MEM_LIN_ALLOC_H_

#include "dggt_mem_buff_alloc.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	struct lin_alloc:
		buff_alloc
	{
		msize used;

		lin_alloc();
		lin_alloc(alloc_func_table* tbl,vpage buff);
		lin_alloc(vpage buff);
		lin_alloc(void* ptr,msize size);
	};

	namespace internal_
	{
		void* lin_alloc_malloc(allocator* a,msize size);
		vpage lin_alloc_malloc_vpage(allocator* a,msize size);
		b32 lin_alloc_clear(allocator* a);
		msize lin_alloc_get_used(const allocator* a);
		msize lin_alloc_get_available(const allocator* a);
	}
}

#define _DGGT_MEM_LIN_ALLOC_H_
#endif
