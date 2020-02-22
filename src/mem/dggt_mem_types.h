/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_TYPES_H_
#define _DGGT_MEM_TYPES_H_
/*! @endcond */

#include "defines/dggt_defines.h"
#include "dggt_mem_defines.h"

namespace dggt
{
	typedef msize stack_state;

	typedef u32 alloc_t;

	global const stack_state SAVE_STACK_FAIL=MAX_MSIZE;
	global const u32 NO_BLOCKSIZE=0;
	global const u32 DEF_BLOCKSIZE=BYTES(4);
	global const u32 DEF_BUFFSIZE=KB(10);

	global const u32 NO_TABLESIZE=0;
	global const u32 DEF_TABLESIZE=4096;

	struct free_block;
	template <u32 BLOCKSIZE=NO_BLOCKSIZE>
	struct pool_block;
	struct store_block;
}

/*! @cond IncludeGuard */
#endif
/*! @endcond */
