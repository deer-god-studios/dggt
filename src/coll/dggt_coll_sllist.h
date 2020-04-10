#ifndef _DGGT_COLL_SLLIST_H_

#include "dggt_coll_sllist_iter.h"
#include "dggt_coll_slnode.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T>
	struct slchain
	{
		slnode<T>* head;
		b32 valid;

		explicit operator slnode<T>*() { return mem; }
	};

	template <typename T>
	struct sllist:
		collection<T,sllist_mem<T>,sllist<T>,sllist_iter<T>>
	{
		u32 count;
	};

	template <typename T,typename A>
	b32 free(A* a,sllist_mem<T>& mem)
	{
		mem.valid=false;
		return free(a,mem.head);
	}

	template <typename T,typename A>
	sllist<T> create_sllist(u32 capacity,A* a)
	{
		sllist<T> result=sllist<T>();
		result.mem.head=malloc_slnode<T>(a,capacity);
		result.mem.valid=true;
		result.count=capacity;
		return result;
	}

	template <typename T,typename A>
	sllist<T>::iter destroy_sllist(sllist<T>* list,A* alloc);

	// if push succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to null but still points to the list.
	template <typename T,typename A>
	sllist<T>::iter push(sllist<T>* list,A* alloc);

	template <typename T,typename A>
	sllist<T>::iter push(sllist<T>* list,const T& val,A* alloc);

	// if pop succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to the old head node that might still
	// needs to be freed and points to a null sllist.
	template <typename T,typename A>
	sllist<T>::iter pop(sllist<T>* list,A* alloc);

	template <typename T>
	sllist<T>::iter peek(sllist<T>* list);

	template <typename T>
	sllist<T>::iter get(sllist<T>* list,u32 index);

	template <typename T,typename A>
	sllist<T>::iter remove(sllist<T>* list,slnode<T>* prev,
			slnode<T>* toRemove,A* alloc);

	template <typename T,typename A>
	sllist<T>::iter clear(sllist<T>* list,A* alloc);

	template <typename T,typename A>
	sllist<T>::iter insert(sllist<T>* list,slnode<T>* prev,
			const T& val,A* alloc);

	template <typename T>
	u32 get_count(const sllist<T>* list);
	
	template <typename T>
	sllist<T>::iter get_iter(sllist<T>* list);

	template <typename T>
	b32 contains(sllist<T>* list,const T& item);
}

#include "dggt_coll_sllist_iter.inl"
#include "dggt_coll_sllist.inl"

#define _DGGT_COLL_SLLIST_H_
#endif
