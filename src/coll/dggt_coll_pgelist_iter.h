#ifndef _DGGT_COLL_PGELIST_ITER_H_

#include "mem/dggt_mem_page.h"
#include "dggt_coll_sllist.h"

namespace dggt
{
	template <typename T,u32 PAGESIZE>
	struct pgelist;

	template <typename T,u32 S>
	using pgelist_mem=sllist<page<T,S>>;

	template <typename T,u32 S>
	using pgelist_mem_iter=sllist_iter<page<T,S>>;

	template <typename T,u32 S>
	struct pgelist_iter
	{
		pgelist_mem<T,S> pgeListMem;
		pgelist_mem_iter<T,S> sllistIter;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		array_iter<T>& operator++();
		array_iter<T> operator++(int);
	};
}

#define _DGGT_COLL_PGELIST_ITER_H_
#endif
