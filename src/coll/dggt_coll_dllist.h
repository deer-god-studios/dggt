#ifndef _DGGT_COLL_DL_NODE_H_

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
	dlchain=blk<dlnode<T>>;

	template <typename T>
	struct dllist
	{
		slchain<T> chain;

		dllist() : chain(dlnode) { }
	};

	// if push succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to null but still points to the list.
	template <typename T,typename A>
	dllist_iter<T> push(dllist<T>* list,A* alloc);

	template <typename T,typename A>
	dllist_iter<T> push(dllist<T>* list,const T& val,A* alloc);

	// if pop succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to the old head node that might still
	// needs to be freed and points to a null dllist.
	template <typename T,typename A>
	dllist_iter<T> pop(dllist<T>* list,A* alloc);

	template <typename T>
	dllist_iter<T> peek(dllist<T>* list);

	template <typename T>
	dllist_iter<T> get(dllist<T>* list,u32 index);

	template <typename T,typename A>
	dllist_iter<T> remove(dllist<T>* list,slnode<T>* prev,
			slnode<T>* toRemove,A* alloc);

	template <typename T,typename A>
	dllist_iter<T> clear(dllist<T>* list,A* alloc);

	template <typename T,typename A>
	dllist_iter<T> insert(dllist<T>* list,slnode<T>* prev,
			const T& val,A* alloc);

	template <typename T>
	u32 get_count(const dllist<T>* list);
	
	template <typename T>
	dllist_iter<T> get_iter(dllist<T>* list);

	template <typename T>
	b32 contains(dllist<T>* list,const T& item);
}

#include "dggt_coll_dllist_iter.inl"
#define _DGGT_COLL_DL_NODE_H_
#endif
