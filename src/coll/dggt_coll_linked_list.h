#ifndef _DGGT_COLL_LINKED_LIST_H_

#include "types/dggt_types.h"

template <typename T>
struct list_node
{
	T val;
	list_node* next;

	private:
	list_node();

	public:
	list_node(const T& val,list_node* next);
	list_node(const T& val);
};

template <typename T>
struct list_iter
{
	list_node* current;

	list_iter();
	list_iter(list_node* begin);

	b32 is_end() const;
	void advance();
	T& get();
	const T& get() const;
};

#include "dggt_coll_linked_list.inl"

#define _DGGT_COLL_LINKED_LIST_H_
#endif
