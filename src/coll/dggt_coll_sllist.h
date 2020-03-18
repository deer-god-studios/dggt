#ifndef _DGGT_COLL_SLLIST_H_

#include "mem/dggt_mem_blk.h"
#include "dggt_coll_sllist_iter.h"

namespace dggt
{
	template <typename T>
	struct slnode
	{
		T val;
		slnode* next;
	};

	template <typename T>
	using slchain=blk<slnode<T>>;

	template <typename T>
	struct sllist
	{
		slchain<T> chain;

		sllist() : chain(slchain<T>()) { }
	};

	template <typename T>
	sllist<T> create_sllist()
	{
		return sllist<T>();
	}

	template <typename T,typename A>
	sllist_iter<T> destroy_sllist(sllist<T>* list,A* alloc);

	// if push succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to null but still points to the list.
	template <typename T,typename A>
	sllist_iter<T> push(sllist<T>* list,A* alloc);

	template <typename T,typename A>
	sllist_iter<T> push(sllist<T>* list,const T& val,A* alloc);

	// if pop succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to the old head node that might still
	// needs to be freed and points to a null sllist.
	template <typename T,typename A>
	sllist_iter<T> pop(sllist<T>* list,A* alloc);

	template <typename T>
	sllist_iter<T> peek(sllist<T>* list);

	template <typename T>
	sllist_iter<T> get(sllist<T>* list,u32 index);

	template <typename T,typename A>
	sllist_iter<T> remove(sllist<T>* list,slnode<T>* prev,
			slnode<T>* toRemove,A* alloc);

	template <typename T,typename A>
	sllist_iter<T> clear(sllist<T>* list,A* alloc);

	template <typename T,typename A>
	sllist_iter<T> insert(sllist<T>* list,slnode<T>* prev,
			const T& val,A* alloc);

	template <typename T>
	u32 get_count(const sllist<T>* list);
	
	template <typename T>
	sllist_iter<T> get_iter(sllist<T>* list);

	template <typename T>
	b32 contains(sllist<T>* list,const T& item);
}

#include "dggt_coll_sllist_iter.inl"
#include "dggt_coll_sllist.inl"

#define _DGGT_COLL_SLLIST_H_
#endif
