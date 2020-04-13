#ifndef _DGGT_COLL_STACK_MEM_H_

#include "dggt_coll_array.h"

namespace dggt
{
	template <typename T>
	using stack_mem=array<T>;

	template <typename T,typename A>
	stack_mem<T> malloc_stack_mem(A* a,msize capacity)
	{
		return create_array(a,capacity);
	}

	template <typename T,typename A>
	b32 free(A* a,stack_mem<T>& mem)
	{
		mem.count=0;
		return destroy_array(&mem,a)==array<T>::iter();
	}
}

#define _DGGT_COLL_STACK_MEM_H_
#endif
