#ifndef _DGGT_COLL_BLOCK_LIST_ITER_H_

#include "dggt_coll_starray.h"
#include "dggt_coll_sllist.h"

namespace dggt
{
	template <typename T,u32 PAGESIZE>
	struct pgelist;

	template <typename T,u32 S>
	using page=starray<T,S>;

	template <typename T,u32 S>
	using pgelist_mem=sllist<page<T,S>>;

	template <typename T,u32 S>
	using page_iter=starray_iter<T,S>;

	template <typename T,u32 S>
	using pgelist_mem_iter=sllist_iter<page<T,S>>;

	template <typename T,u32 S>
	struct pgelist_iter
	{
	};
}

#define _DGGT_COLL_BLOCK_LIST_ITER_H_
#endif
