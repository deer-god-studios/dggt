#ifndef _DGGT_MEM_ALLOC_H_

// TODO: implement is_valid(block) to check if a block has already 
// 		been 'freed'.

#include "dggt_mem_blk.h"

namespace dggt
{
	enum alloc_t:u32
	{
		NONE,
		LINEAR,
		STACK,
		POOL,
		FREE_LIST,
		STORE,
		STORE_TABLE,
		FALLBACK,
	};

	struct pool_block;
	struct store_block;
	struct free_block;
	typedef msize stack_state;

	// NOTE: variadic template args are for composite allocator types.
	template <alloc_t A,u32 SIZE=0,u32... As>
	struct allocator;
}

#define _DGGT_MEM_ALLOC_H_
#endif
