#ifndef _DGGT_MEM_BUFF_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct buff_alloc
		:allocator
	{
		vpage buff;

		buff_alloc();
		buff_alloc(alloc_func_table* tbl,vpage buffer);
		buff_alloc(vpage buffer);
		buff_alloc(void* buffer,msize size);
	};

	namespace internal_
	{
		b32 buff_alloc_owns(const allocator* a,const void* ptr,msize size);
		b32 buff_alloc_owns(const allocator* a,const vpage& pge);
		msize buff_alloc_get_capacity(const allocator* a);
		msize buff_alloc_get_available(const allocator* a);
		vpage buff_alloc_get_buff(allocator* a);
		const vpage buff_alloc_get_buff(const allocator* a);
		void* buff_alloc_get_buff_ptr(allocator* a);
		const void* buff_alloc_get_buff_ptr(const allocator* a);
	}
}

#define _DGGT_MEM_BUFF_ALLOC_H_
#endif
