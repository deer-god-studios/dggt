#ifndef _DGGT_COLL_HEAP_MEM_H_

#include "dggt_coll_array.h"

namespace dggt
{
	template <typename T>
	using heap_mem=array<T>;

	template <typename T>
	global constexpr const array<T> NULL_HEAP_MEM=array<T>();

	template <typename T>
	heap_mem<T> malloc_heap_mem(A* a,msize capacity)
	{
		return create_array(a,capacity);
	}
}

#define _DGGT_COLL_HEAP_MEM_H_
#endif
