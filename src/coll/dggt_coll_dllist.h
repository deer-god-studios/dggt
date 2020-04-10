#ifndef _DGGT_COLL_DLLIST_H_

#include "dggt_coll_dllist_iter.h"
#include "dggt_coll_dlnode.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T>
	struct dlchain
	{
		dlpair<T> pair;
		b32 valid;
	};

	template <typename T>
	struct dllist:
		collection<T,dllist_mem<T>,dllist<T>,dllist_iter<T>>
	{
		u32 count;
	};

	template <typename T,typename A>
	b32 free(A* a,dllist_mem<T>& mem)
	{
		mem.valid=false;
		return free(a,mem.pair);
	}

	template <typename T,typename A>
	dllist<T> create_dllist(u32 capacity,A* a)
	{
		dllist<T> result=dllist<T>();
		result.mem.pair=malloc_dlpair(a,capacity);
		result.mem.valid=true;
		return result;
	}

	template <typename T,typename A>
	dllist<T>::iter destroy_dllist(dllist<T>* list,A* a);

	// if push succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to null but still points to the list.
	template <typename T,typename A>
	dllist<T>::iter push(dllist<T>* list,A* alloc);

	template <typename T,typename A>
	dllist<T>::iter push(dllist<T>* list,const T& val,A* alloc);

	// if pop succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to the old head node that might still
	// needs to be freed and points to a null dllist.
	template <typename T,typename A>
	dllist<T>::iter pop(dllist<T>* list,A* alloc);

	template <typename T>
	dllist<T>::iter peek(dllist<T>* list);

	template <typename T>
	dllist<T>::iter get(dllist<T>* list,u32 index);

	template <typename T,typename A>
	dllist<T>::iter remove(dllist<T>* list,dlnode<T>* toRemove,A* alloc);

	template <typename T,typename A>
	dllist<T>::iter clear(dllist<T>* list,A* alloc);

	template <typename T,typename A>
	dllist<T>::iter insert(dllist<T>* list,
			dlnode<T>* prev,const T& val,A* alloc);

	template <typename T>
	u32 get_count(const dllist<T>* list);
	
	template <typename T>
	dllist<T>::iter get_iter(dllist<T>* list);

	template <typename T>
	b32 contains(dllist<T>* list,const T& item);
}

#include "dggt_coll_dllist_iter.inl"
#include "dggt_coll_dllist.inl"

#define _DGGT_COLL_DLLIST_H_
#endif
