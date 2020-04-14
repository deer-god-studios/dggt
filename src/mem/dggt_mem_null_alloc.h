#ifndef _DGGT_MEM_NULL_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct null_alloc:
		allocator<u32,false>
	{
		null_alloc():allocator() { }
	};
}

#define _DGGT_MEM_NULL_ALLOC_H_
#endif
