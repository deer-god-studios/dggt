#ifndef _DGGT_COLL_STACK_ITER_H_

#include "dggt_coll_array.h"
#include "dggt_coll_stack_mem.h"
#include "dggt_coll_stack_key.h"

namespace dggt
{
	template <typename T>
	struct stack;

	template <typename T>
	using stack_iter_settings=
	iterator<T,stack_mem<T>,stack<T>,stack_key<T>>;
}

#define _DGGT_COLL_STACK_ITER_H_
#endif
