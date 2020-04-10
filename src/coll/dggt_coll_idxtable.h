#ifndef _DGGT_COLL_IDXTABLE_

#include "dggt_coll_membership.h"

#include "dggt_coll_idxtable_iter.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T>
	struct idxtable_mem
	{
		idxmem<T> mem;
		idxmem<flag32> flags;
	};

	global const fl32 IDX_EMPTY=MEMB_EMPTY;
	global const fl32 IDX_OCCUPIED=MEMB_OCCUPIED;

	template <typename T>
	struct idxtable:
		collection<T,idxtable_mem<T>,idxtable<T>,idxtable_iter<T>>
	{
		msize nextHandle;
		u32 count;
	};

	template <typename T,typename A>
	b32 free(A* a,idxtable_mem<T>& mem)
	{
		return free(a,(stack_mem<T>&)mem.mem)&&
			free((stack_mem<flag32>&)a,mem.flags);
	}

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
