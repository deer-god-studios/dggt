#ifndef _DGGT_COLL_DLLIST_H_

#include "dggt_coll_dllist_iter.h"

namespace dggt
{
	template <typename T>
	struct dlnode
	{
		T val;
		dlnode<T>* prev;
		dlnode<T>* next;
	};

	template <typename T>
	struct dl_list
	{
		blk<dlnode<T>> chain;

		dl_list() : chain(dlnode<T>()) { }
	};

	// if push succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to null but still points to the list.
	template <typename T,typename A>
	dllist_iter<T> push(sllist<T>* list,A* alloc);

	template <typename T,typename A>
	dllist_iter<T> push(sllist<T>* list,const T& val,A* alloc);

	// if pop succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to the old head node that might still
	// needs to be freed and points to a null sllist.
	template <typename T,typename A>
	dllist_iter<T> pop(sllist<T>* list,A* alloc);

	template <typename T>
	dllist_iter<T> peek(sllist<T>* list);

	template <typename T>
	dllist_iter<T> get(sllist<T>* list,u32 index);

	template <typename T,typename A>
	dllist_iter<T> remove(sllist<T>* list,slnode<T>* prev,
			slnode<T>* toRemove,A* alloc);

	template <typename T,typename A>
	dllist_iter<T> clear(sllist<T>* list,A* alloc);

	template <typename T,typename A>
	dllist_iter<T> insert(sllist<T>* list,slnode<T>* prev,
			const T& val,A* alloc);

	template <typename T>
	u32 get_count(const sllist<T>* list);
	
	template <typename T>
	dllist_iter<T> get_iter(sllist<T>* list);

	template <typename T>
	b32 contains(sllist<T>* list,const T& item);
}

#include "dggt_coll_dllist_iter.inl"
#include "dggt_coll_dllist.inl"

#define _DGGT_COLL_DLLIST_H_
#endif
