#ifndef _DGGT_COLL_ARRAY_ITER_H_

#include "dggt_coll_iterator.h"
#include "dggt_coll_array_mem.h"
#include "dggt_coll_array_key.h"

namespace dggt
{	
	template <typename T>
	struct array;

	template <typename T>
	using array_iter_settings=
	iter_settings<T,array_mem<T>,array<T>,array_key<T>>;

	template <typename T>
	using array_iter=iterator<array_iter_settings<T>>;
}

#define _DGGT_COLL_ARRAY_ITER_H_
#endif
