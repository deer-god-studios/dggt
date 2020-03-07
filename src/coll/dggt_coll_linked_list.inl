#include "mem/dggt_mem.h"

namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T>
		list_iter<T> def_list_iter(linked_list<T>* list)
		{
			return list_iter<T>{0,list,0};
		}
	}

	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,A* a)
	{
		list_iter<T> result=dggt_internal_::def_list_iter(list);
		if (list&&a)
		{
			slnode<T>* newNode=alloc<slnode<T>>(a);
			if (newNode)
			{
				newNode->next=list->chain.ptr;
				zero_struct<T>(&newNode->val);
				result.current=newNode;
				result.list=list;
				result.memIsValid=true;
				list->chain.ptr=newNode;
				++list->chain.count;
			}
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,const T& val,A* a)
	{
		list_iter<T> result=push(list,a);
		if (!is_end(result))
		{
			result.current->val=val;
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> pop(linked_list<T>* list,A* a)
	{
		list_iter<T> result=dggt_internal_::def_list_iter(list);
		if (list&&list->chain.count)
		{
			slnode<T>* nodeToFree=list->chain.ptr;
			result.current=nodeToFree;
			result.memIsValid=false;
			list->chain.ptr=nodeToFree->next;
			--list->chain.count;
			if (free(a,nodeToFree,1))
			{
				result.current=list->chain.ptr;
				result.list=list;
				result.memIsValid=1;
			}
		}
		return result;
	}

	template <typename T>
	list_iter<T> peek(linked_list<T>* list)
	{
		return list_iter<T>{list?list->chain.ptr:0,list};
	}

	template <typename T>
	list_iter<T> get(linked_list<T>* list,u32 index)
	{
		list_iter<T> result=list_iter<T>{0,list};
		list_iter<T> it=get_iter(list);
		u32 i=0;
		while (!is_end(it)&&i<index)
		{
			++i;
			next(it);
		}
		if (!is_end(it))
		{
			result=it;
		}
		return result;
	}

	template <typename T>
	list_iter<T> get_iter(linked_list<T>* list)
	{
		return peek(list);
	}

	template <typename T>
	u32 get_count(const linked_list<T>* list)
	{
		return list?list->chain.count:0;
	}

	template <typename T>
	b32 contains(linked_list<T>* list,const T& item)
	{
		b32 result=false;
		for (list_iter<T> it=get_iter(list);
				!is_end(it);
				++it)
		{
			if (get(it)==item)
			{
				result=true;
				break;
			}
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> remove(
			linked_list<T>* list,
			slnode<T>* prev,
			slnode<T>* toRemove,A* a)
	{
		list_iter<T> result={0,list,0};
		if (list)
		{
			if (prev)
			{
				ASSERT(toRemove&&prev->next==toRemove);
				result.current=toRemove;
				result.memIsValid=0;
				prev->next=toRemove->next;
				--list->chain.count;
				if (free(a,toRemove,1))
				{
					result.current=prev;
					result.list=list;
					result.memIsValid=1;
				}
			}
			else
			{
				result=pop(list,a);
			}
		}

		return result;
	}

	template <typename T,typename A>
	list_iter<T> clear(linked_list<T>* list,A* a)
	{
		list_iter<T> result=dggt_internal_::def_list_iter(list);
		if (list)
		{
			slnode<T>* current=list->chain.ptr;
			result.memIsValid=1;
			while (current)
			{
				slnode<T>* nodeToFree=current;
				current=current->next;
				if (!free(a,nodeToFree,1))
				{
					nodeToFree->next=result.current;
					result.current=nodeToFree;
					result.memIsValid=0;
				}
			}
			if (result.memIsValid)
			{
				result.current=list->chain.ptr;
			}
			list->chain.count=0;
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> insert(linked_list<T>* list,slnode<T>* prev,
			const T& val,A* a)
	{
		list_iter<T> result=list_iter<T>{0,list,0};
		if (list)
		{
			slnode<T>* newNode=alloc<slnode<T>>(a);
			if (newNode)
			{
				result.current=newNode;
				result.memIsValid=1;
				newNode->val=val;
				if (prev)
				{
					newNode->next=prev->next;
					prev->next=newNode;
				}
				else
				{
					newNode->next=list->chain.ptr->next;
					list->chain.ptr=newNode;
				}
				++list->chain.count;
			}
		}
		return result;
	}
}
