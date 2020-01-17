#ifndef _DGGT_COLL_STACK_H_

#include "dggt_coll_iter.h"
namespace dggt
{
	template <typename T>
	struct stack;

	template <typename T>
	using stack_iter=iter<T,stack<T>>;

	template <typename T>
	struct stack_iter<T>
	{
	};
}

#define _DGGT_COLL_STACK_H_
#endif
