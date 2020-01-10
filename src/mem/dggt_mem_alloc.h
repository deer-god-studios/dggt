#ifndef _DGGT_MEM_ALLOC_H_

#include "dggt_mem_blk.h"

enum alloc_t:u32
{
	NONE,
	LINEAR,
	STACK,
	FREE_LIST,
	POOL
};

template <alloc_t T>
struct allocator;

#define _DGGT_MEM_ALLOC_H_
#endif
