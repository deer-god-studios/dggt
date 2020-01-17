#ifndef _DGGT_COLL_LINKED_LIST_H_

#include "types/dggt_types.h"
#include "dggt_coll_iter.h"

namespace dggt
{
	template <typename T>
	struct slnode
	{
		T val;
		slnode* next;
	};

	template <typename T>
	struct linked_list;

	template <typename T>
	using list_iter=iter<T,linked_list<T>>;

	template <typename T>
	struct iter<T,linked_list<T>>
	{
		slnode<T>* current;
		linked_list<T>* list;

		b32 is_end() const;
		b32 next();
		T& get();
		const T& get() const;
		T* get_ptr();
		const T* get_ptr() const;
		slnode<T>* get_node();
		const slnode<T>* get_node() const;
	};

	template <typename T>
	struct linked_list
	{
		slnode<T>* head;
		u32 count;
	};

	template <typename T>
	linked_list<T> create_linked_list()
	{
		return linked_list<T>{};
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

	template <typename T>
	u32 get_count(const linked_list<T>* list);
	
	template <typename T>
	list_iter<T> get_iter(linked_list<T>* list);

}
#include "dggt_coll_linked_list.inl"
#define _DGGT_COLL_LINKED_LIST_H_
#endif
