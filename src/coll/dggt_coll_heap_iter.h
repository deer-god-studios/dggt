#ifndef _DGGT_COLL_HEAP_ITER_H_

#include "dggt_coll_array_iter.h"
#include "dggt_coll_heap_mem.h"
#include "dggt_coll_heap_key.h"

namespace dggt
{
	template <typename T>
	using heap_iter_settings=
	iter_settings<T,heap_mem<T>,heap<T>,heap_key<T>>;

	template <typename T>
	using heap_iter=iterator<heap_iter_settings<T>>;
}

#define _DGGT_COLL_HEAP_ITER_H_
#endif
