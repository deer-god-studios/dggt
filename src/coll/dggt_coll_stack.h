#ifndef _DGGT_COLL_STACK_H_

#include "dggt_coll_common.h"

namespace dggt
{
	template <typename T>
	struct stack
	{
		blk<T> mem;
		u32 count;
	};
}

#include "dggt_coll_stack.inl"

#define _DGGT_COLL_STACK_H_
#endif
