// TODO: insert should take an iterator instead of slnode<T>*
#ifndef _DGGT_COLL_SLLIST_H_

#include "dggt_coll_sllist_iter.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T>
	using sllist_settings=
	coll_settings<T,sllist_mem<T>,sllist<T>,sllist_iter<T>>;

	template <typename T>
	struct sllist:
		collection<sllist_settings<T>>
	{
		u32 count;
	};

	template <typename T,typename A>
	sllist<T> create_sllist(A* a)
	{
		sllist<T> result=sllist<T>{};
		result.mem=malloc_sllist_mem<T>(a);
		result.count=0;
		return result;
	}

	template <typename T,typename A>
	typename sllist<T>::iter destroy_sllist(sllist<T>& list,A* alloc);

	// if push succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to null but still points to the list.
	template <typename T,typename A>
	typename sllist<T>::iter push(sllist<T>& list,A* alloc);

	template <typename T,typename A>
	typename sllist<T>::iter push(sllist<T>& list,const T& val,A* alloc);

	// if pop succeeds it returns an iterator to the list's new head node
	// otherwise the iterator points to the old head node that might still
	// needs to be freed and points to a null sllist.
	template <typename T,typename A>
	typename sllist<T>::iter pop(sllist<T>& list,A* alloc);

	template <typename T>
	typename sllist<T>::iter peek(sllist<T>& list);

	template <typename T>
	typename sllist<T>::iter get(sllist<T>& list,u32 index);

	template <typename T,typename A>
	typename sllist<T>::iter remove(sllist<T>& list,
			typename sllist<T>::iter& prev,
			typename sllist<T>::iter& node,A* alloc);

	template <typename T,typename A>
	typename sllist<T>::iter clear(sllist<T>& list,A* alloc);

	template <typename T,typename A>
	typename sllist<T>::iter insert(sllist<T>& list,
			typename sllist<T>::iter& node,const T& val,A* alloc);

	template <typename T>
	u32 get_count(const sllist<T>& list);
	
	template <typename T>
	typename sllist<T>::iter get_iter(sllist<T>& list);

	template <typename T>
	b32 contains(sllist<T>& list,const T& item);
}

#include "dggt_coll_sllist.inl"

#define _DGGT_COLL_SLLIST_H_
#endif
