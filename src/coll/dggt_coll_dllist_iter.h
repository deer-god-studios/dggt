#ifndef _DGGT_COLL_DLLIST_ITER_H_

#include "dggt_coll_iterator.h"
#include "dggt_coll_dllist_mem.h"
#include "dggt_coll_dllist_key.h"

namespace dggt
{
	template <typename T>
	struct dllist;

	template <typename T>
	using dllist_iter_settings=
	iter_settings<T,dllist_mem<T>,dllist<T>,dllist_key<T>>;

	template <typename T>
	using dllist_iter=iterator<dllist_iter_settings<T>>;
}


#define _DGGT_COLL_DLLIST_ITER_H_
#endif
