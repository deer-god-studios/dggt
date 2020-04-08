#ifndef _DGGT_COLL_IDXTABLE_

#include "dggt_coll_membership.h"

#include "dggt_coll_idxtable_iter.h"

namespace dggt
{
	global const fl32 IDX_EMPTY=MEMB_EMPTY;
	global const fl32 IDX_OCCUPIED=MEMB_OCCUPIED;

	template <typename T>
	struct idxtable
	{
		u32 nextHandle;
		array<T> table;
		array<flag32> flags;
	};

	template <typename T,typename A>
	idxtable<T> create_idxtable(u32 capacity,A* allocator);

	template <typename T,typename A>
	idxtable_iter<T> destroy_idxtable(idxtable<T>* table,A* allocator);

	template <typename T,typename A>
	idxtable_iter<T> add(idxtable<T>* table,A* allocator);

	template <typename T,typename A>
	idxtable_iter<T> add(idxtable<T>* table,const T& val,A* allocator);

	template <typename T,typename A>
	idxtable_iter<T> remove(idxtable<T>* table,const T& val,A* allocator);

	template <typename T,typename A>
	idxtable_iter<T> remove(idxtable<T>* table,u32 handle,A* allocator);

	template <typename T,typename A>
	idxtable_iter<T> clear(idxtable<T>* table,A* allocator);

	template <typename T>
	u32 get_count(const idxtable<T>* table);

	template <typename T>
	idxtable_iter<T> get_iter(idxtable<T>* table);

	template <typename T>
	b32 contains(idxtable<T>* table,const T& item);

	template <typename T>
	u32 get_capacity(idxtable<T>* table);

	template <typename F,typename T>
	F get_load_factor(idxtable<T>* table);

	template <typename T,typename A>
	idxtable_iter<T> resize(idxtable<T>* table,u32 newCapacity,A* allocator);
}

#include "dggt_coll_idxtable_iter.inl"
#include "dggt_coll_idxtable.inl"

#define _DGGT_COLL_IDXTABLE_
#endif
