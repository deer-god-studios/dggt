#ifndef _DGGT_COLL_LINKED_LIST_H_

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
	struct list_iter
	{
		slnode<T>* current;
		linked_list<T>* list;
		b32 memIsValid;

		T& operator*();
		const T& operator*() const;
		list_iter<T>& operator++();
		list_iter<T>& operator++(int);
	};

	template <typename T>
	b32 is_end(const list_iter<T>* it);

	template <typename T>
	b32 advance(list_iter<T>* it);

	template <typename T>
	T& get(list_iter<T>* it);

	template <typename T>
	const T& get(const list_iter<T>* it);

	template <typename T>
	T* get_ptr(list_iter<T>* it);

	template <typename T>
	const T* get_ptr(const list_iter<T>* it);
	
	template <typename T>
	slnode<T>* get_mem(list_iter<T>* it);

	template <typename T>
	const slnode<T>* get_mem(const list_iter<T>* it);

	template <typename T>
	b32 is_coll_valid(const list_iter<T>* it);

	template <typename T>
	b32 is_mem_valid(const list_iter<T>* it);

	template <typename T>
	b32 vindicate_mem(list_iter<T>* it);

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

#include "dggt_coll_linked_list.inl"

#define _DGGT_COLL_LINKED_LIST_H_
#endif
