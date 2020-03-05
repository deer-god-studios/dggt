#ifndef _DGGT_COLL_LINKED_LIST_H_

#include "mem/dggt_mem_blk.h"
#include "dggt_coll_list_iter.h"

namespace dggt
{
	template <typename T>
	struct slnode
	{
		T val;
		slnode* next;
	};

	template <typename T>
	struct linked_list
	{
		blk<slnode<T>> chain;

		linked_list() : chain(blk<slnode<T>>()) { }
	};

	template <typename T>
	linked_list<T> create_linked_list()
	{
		return linked_list<T>();
	}

	// if push succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to null but still points to the list.
	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,A* alloc);

	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,const T& val,A* alloc);

	// if pop succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to the old head node that might still
	// needs to be freed and points to a null linked_list.
	template <typename T,typename A>
	list_iter<T> pop(linked_list<T>* list,A* alloc);

	template <typename T>
	list_iter<T> peek(linked_list<T>* list);

	template <typename T>
	list_iter<T> get(linked_list<T>* list,u32 index);

	template <typename T,typename A>
	list_iter<T> remove(linked_list<T>* list,slnode<T>* prev,
			slnode<T>* toRemove,A* alloc);

	template <typename T,typename A>
	list_iter<T> clear(linked_list<T>* list,A* alloc);

	template <typename T,typename A>
	list_iter<T> insert(linked_list<T>* list,slnode<T>* prev,
			const T& val,A* alloc);

	template <typename T>
	u32 get_count(const linked_list<T>* list);
	
	template <typename T>
	list_iter<T> get_iter(linked_list<T>* list);

	template <typename T>
	b32 contains(linked_list<T>* list,const T& item);
}

#include "dggt_coll_list_iter.inl"
#include "dggt_coll_linked_list.inl"

#define _DGGT_COLL_LINKED_LIST_H_
#endif
