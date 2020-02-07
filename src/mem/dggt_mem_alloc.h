/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_ALLOC_H_
/*! @endcond */

// TODO: implement is_valid(block) to check if a block has already 
// 		been 'freed'.
// TODO: allow pool allocs to free multiple blocks. 

#include "dggt_mem_blk.h"

 // TODO: fix allocators!  This enumerator shit sucks.

namespace dggt
{
	/*!
	 * @addtogroup mem
	 * @{
	 * */

	/*!
	 * @brief an enumerator containing all the basic allocators.
	 * */
	enum alloc_t:u32
	{
		NONE,
		LINEAR,
		STACK,
		AUTO_STACK,
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

	/*!
	 * @}
	 * */
}

/*! @cond IncludeGuard */
#define _DGGT_MEM_ALLOC_H_
#endif
/*! @endcond */
