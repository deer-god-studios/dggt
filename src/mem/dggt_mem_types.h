/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_TYPES_H_
#define _DGGT_MEM_TYPES_H_
/*! @endcond */

namespace dggt
{
	typedef msize stack_state;

	global const SAVE_STACK_FAIL=MAX_MSIZE;

	struct free_block;
	template <u32 BLOCKSIZE=NO_BLOCKSIZE>
	struct pool_block;
	struct store_block;
}

/*! @cond IncludeGuard */
#endif
/*! @endcond */
