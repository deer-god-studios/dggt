#ifndef _DGGT_MEM_ALLOC_H_

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
	};

	struct pool_block;
	struct store_block;
	struct free_block;
	typedef msize stack_state;

	template <alloc_t A>
	struct allocator
	{
		static const alloc_t TYPE=alloc_t::NONE;
	};
}

#define _DGGT_MEM_ALLOC_H_
#endif
