#ifndef _DGGT_MEM_LIN_ALLOC_H_

#include "dggt_mem_utils.h"
#include "dggt_mem_allocator.h"

namespace dggt
{
	struct lin_alloc:
		allocator<>
	{
		lin_alloc(void* ptr,msize buffSize) : 
			allocator(alloc_buff(vpage(ptr,buffSize),0)) { }
		lin_alloc() : allocator() { }
	};

	void* malloc(lin_alloc* alloc,msize size);

	b32 free(lin_alloc* a,void* ptr,msize size);
	
	b32 clear(lin_alloc* a);
}

#define _DGGT_MEM_LIN_ALLOC_H_
#endif
