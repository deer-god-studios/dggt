#ifndef _DGGT_COLL_SLLIST_ITER_H_

#include "dggt_coll_sllist_mem.h"
#include "dggt_coll_sllist_key.h"
#include "dggt_coll_iterator.h"

namespace dggt
{
	template <typename T>
	struct sllist;

	template <typename T>
	using sllist_iter_settings=
	iter_settings<T,sllist_mem<T>,sllist<T>,sllist_key<T>>;

	template <typename T>
	using sllist_iter=iterator<sllist_iter_settings<T>>;
}

#define _DGGT_COLL_SLLIST_ITER_H_
#endif
