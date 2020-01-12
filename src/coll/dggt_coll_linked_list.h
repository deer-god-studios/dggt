#ifndef _DGGT_COLL_LINKED_LIST_H_

#include "types/dggt_types.h"
#include "mem/dggt_mem.h"

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
		free_store<list_node<T>> freeStore;
	};

	template <typename T,alloc_t A>
	list_iter<T> push(linked_list<T>* list,allocator<A>* alloc);
	template <typename T,alloc_t A>
	list_iter<T> push(linked_list<T>* list,const T& val,allocator<A>* alloc);

	template <typename T,alloc_t A>
	list_iter<T> pop(linked_list<T>* list,allocator<A>* alloc);
	template <typename T>
	list_iter<T> pop(linked_list<T>* list);
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
