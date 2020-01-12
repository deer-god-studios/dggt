#ifndef _DGGT_COLL_LINKED_LIST_H_

#include "dggt_coll_common.h"

namespace dggt
{
	template <typename T>
	struct list_node
	{
		T val;
		list_node* next;

		list_node();
		list_node(const T& val,list_node* next);
		list_node(const T& val);
	};

	template <typename T>
	struct list_iter
	{
		list_node<T>* current;

		list_iter();
		list_iter(list_node<T>* begin);

		b32 is_end() const;
		void advance();
		T& get();
		const T& get() const;
		list_node<T>* node();
		const list_node<T>* node() const;

		operator list_node<T>*() { return current; }
	};

	template <typename T>
	struct linked_list
	{
		list_node<T>* head;
		u32 count;
	};

	// NOTE: If a free_store<list_node<T>>* if supplied, push attempts to
	// 		allocate from the freeStore first before trying the allocator<A>
	// 		if neither work list_iter points to null (one-past-last item).
	template <typename T,alloc_t A>
	list_iter<T> push(linked_list<T>* list,allocator<A>* alloc,
			free_store<list_node<T>>* freeStore=0);
	template <typename T,alloc_t A>
	list_iter<T> push(linked_list<T>* list,const T& val,allocator<A>* alloc,
			free_store<list_node<T>>* freeStore=0);

	// NOTE: If any pop function fails to free the head node
	// 		pop still removes the node but returns a list_iter to the
	// 		node to be freed by the user, otherwise it returns a
	// 		list_iter to the list's head node for iteration.
	// 		This can be checked with is_begin_iter which will return
	// 		true if the list_iter points to the list's head node.
	// 		If freeStore is provided, pop will still attempt to free
	// 		the node using the allocator if possible using the freeStore
	// 		as a fall-back
	// TODO: Change check-alloc-first behavior?
	template <typename T,alloc_t A>
	list_iter<T> pop(linked_list<T>* list,allocator<A>* alloc,
			free_store<list_node<T>>* freeStore=0);
	template <typename T>
	list_iter<T> pop(linked_list<T>* list,
			free_store<list_node<T>>* freeStore=0);
	template <typename T>
	list_iter<T> peek(linked_list<T>* list);
	template <typename T>
	list_iter<T> get(linked_list<T>* list,u32 index);

	template <typename T>
	list_iter<T> begin_iter(linked_list<T>* list);

	template <typename T>
	b32 is_begin_iter(linked_list<T>* list,list_iter<T> iter);

}
#include "dggt_coll_linked_list.inl"

#define _DGGT_COLL_LINKED_LIST_H_
#endif
