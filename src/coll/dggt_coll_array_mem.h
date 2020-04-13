#ifndef _DGGT_COLL_ARRAY_MEM_H_

#include "mem/dggt_mem_page.h"

namespace dggt
{
	template <typename T>
	using array_mem=page<T>;

	template <typename T>
	global constexpr const array_mem<T> NULL_ARRAY_MEM=NULL_PAGE<T>;

	template <typename T,typename A>
	array_mem<T> malloc_array_mem(A* a,msize capacity)
	{
		return malloc_page<T>(a,capacity);
	}
}

#define _DGGT_COLL_ARRAY_MEM_H_
#endif
