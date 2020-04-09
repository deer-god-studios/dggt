#ifndef _DGGT_COLL_BLOCK_LIST_H_

#include "dggt_coll_pgelist_iter.h"

namespace dggt
{
	template <typename T,u32 S>
	struct pgelist
	{
		pgelist_mem<T,S> list;
	};

	template <typename T,u32 S,typename A>
	pgelist<T,S> create_pgelist(u32 capacity,A* allocator);

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> destroy_pgelist(pgelist<T,S>* pgeList,A* allocator);

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> push(pgelist<T,S>* pgeList,A* allocator);

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> push(pgelist<T,S>* pgeList,const T& val,A* allocator);

	template <typename T,u32 S>
	pgelist_iter<T,S> peek(pgelist<T,S>* pgeList);

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> pop(pgelist<T,S>* pgeList,
			A* allocator);

	template <typename T,u32 S>
	pgelist_iter<T,S> get(pgelist<T,S>* pgeList,u32 index);

	template <typename T,u32 S>
	page_mem_iter<T,S> get_page_mem(pgelist<T,S>* pgeList,u32 pgeIndex);

	template <typename T,u32 S>
	pgelist_mem_iter<T,S> get_pgelist_mem(pgelist<T,S>* pgeList,u32 pgeIndex);

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> clear(pgelist<T,S>* pgeList,A* allocator);

	template <typename T,u32 S>
	pgelist_iter<T,S> get_iter(pgelist<T,S>* pgeList);

	template <typename T,u32 S>
	b32 contains(pgelist<T,S>* pgeList,const T& item);

	template <typename T,u32 S>
	u32 get_capacity(pgelist<T,S>* pgeList);

	template <typename T,u32 S>
	u32 get_count(pgelist<T,S>* pgeList);
}

#include "dggt_coll_pgelist_iter.inl"
#include "dggt_coll_pgelist.inl"

#define _DGGT_COLL_PGELIST_H_
#endif
