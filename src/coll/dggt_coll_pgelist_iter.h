#ifndef _DGGT_COLL_PGELIST_ITER_H_

#include "mem/dggt_mem_page.h"
#include "dggt_coll_sllist.h"

namespace dggt
{
	template <typename T,u32 S>
	struct pgelist;

	template <typename T,u32 S>
	using page_mem=starray<T,S>

	template <typename T,u32 S>
	using page_mem_iter=starray_iter<T,S>;

	template <typename T,u32 S>
	using pgelist_mem=sllist<page_mem<T,S>>;

	template <typename T,u32 S>
	using pgelist_mem_iter=sllist_iter<page_mem<T,S>>;

	template <typename T,u32 S>
	struct pgelist_iter
	{
		pgelist_mem<T,S> pgeListMem;
		page_mem_iter<T<S> pgeMemIter;
		pgelist_mem_iter<T,S> pgelistMemIter;
		pgelist<T,S>* pgeList;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		pgelist_iter<T>& operator++();
		pgelist_iter<T> operator++(int);
	};
}

#define _DGGT_COLL_PGELIST_ITER_H_
#endif
