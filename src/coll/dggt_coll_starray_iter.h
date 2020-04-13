#ifndef _DGGT_COLL_STARRAY_ITER_H_

#include "dggt_coll_iterator.h"
#include "dggt_coll_starray_mem.h"
#include "dggt_coll_starray_key.h"

namespace dggt
{
	template <typename T,msize S>
	struct starray;

	template <typename T,msize S>
	using starray_iter_settings=
	iter_settings<T,starray_mem<T,S>,starray<T,S>,starray_key<T,S>>;

	template <typename T,msize S>
	using starray_iter=iterator<starray_iter_settings<T,S>>;
}

#define _DGGT_COLL_STARRAY_ITER_H_
#endif
