#ifndef _DGGT_COLL_PGELIST_ITER_H_

#include "dggt_coll_starray.h"
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
		pgelist_mem<T,S> pgelistMem;
		pgelist_mem_iter<T,S> pgelistMemIter;
		page_mem_iter<T<S> pgeMemIter;
		pgelist<T,S>* pgeList;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		pgelist_iter<T>& operator++();
		pgelist_iter<T> operator++(int);
	};

	template <typename T>
	b32 is_end(const pgelist_iter<T>& it);

	template <typename T>
	b32 advance(pgelist_iter<T>& it);

	template <typename T>
	T& get(pgelist_iter<T>& it);

	template <typename T>
	const T& get(const pgelist_iter<T>& it);

	template <typename T>
	T* get_ptr(pgelist_iter<T>& it);

	template <typename T>
	const T* get_ptr(const pgelist_iter<T>& it);
	
	template <typename T>
	pgelist_mem get_mem(pgelist_iter<T>& it);

	template <typename T>
	const pgelist_mem get_mem(const pgelist_iter<T>& it);

	template <typename T>
	b32 is_coll_valid(const pgelist_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const pgelist_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(pgelist_iter<T>& it);

	template <typename T,typename A>
	b32 free(A* a,pgelist_iter<T>& it);
}

#define _DGGT_COLL_PGELIST_ITER_H_
#endif
