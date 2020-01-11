#ifndef _DGGT_MEM_FREE_LIST_H_

struct free_node
{
	free_node* next;
};

template <typename T>
struct free_list
{
	free_node* head;
};

#define _DGGT_MEM_FREE_LIST_H_
#endif
