#ifndef _DGGT_COLL_IDX_TABLE_

#include "dggt_coll_membership.h"

namespace dggt
{
	global const fl32 IDX_EMPTY=MEMB_EMPTY;
	global const fl32 IDX_OCCUPIED=MEMB_OCCUPIED;

	template <typename T>
	struct idx_table
	{
		u32 nextHandle;
		array<T> table;
		array<flag32> flags;
	};

	template <typename T,typename A>
	idx_table<T> create_idx_table(u32 capacity,A* allocator);

	template <typename T,typename A>
	idx_table_iter<T> destroy_idx_table(idx_table<T>* table,A* allocator);

	template <typename T,typename A>
	idx_table_iter<T> add(idx_table<T>* table,A* allocator);

	template <typename T,typename A>
	idx_table_iter<T> add(idx_table<T>* table,const T& val,A* allocator);

	template <typename T,typename A>
	idx_table_iter<T> remove(idx_table<T>* table,const T& val,A* allocator);

	template <typename T,typename A>
	idx_table_iter<T> remove(idx_table<T>* table,u32 handle,A* allocator);

	template <typename T,typename A>
	idx_table_iter<T> clear(idx_table<T>* table,A* allocator);

	template <typename T>
	u32 get_count(const idx_table<T>* table);

	template <typename T>
	idx_table_iter<T> get_iter(idx_table<T>* table);

	template <typename T>
	b32 contains(idx_table<T>* table,const T& item);

	template <typename T>
	u32 get_capacity(idx_table<T>* table);

	template <typename F,typename T>
	F get_load_factor(idx_table<T>* table);

	template <typename T,typename A>
	idx_table_iter<T> resize(idx_table<T>* table,u32 newCapacity,A* allocator);
}

#include "dggt_coll_idx_table_iter.inl"
#include "dggt_coll_idx_table.inl"

#define _DGGT_COLL_IDX_TABLE_
#endif
