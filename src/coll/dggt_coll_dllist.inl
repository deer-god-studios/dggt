
#include "mem/dggt_mem.h"

namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T>
		dllist_iter<T> def_dllist_iter(dllist<T>* list)
		{
			return dllist_iter<T>{0,list,0};
		}
	}

	template <typename T,typename A>
	dllist_iter<T> push(dllist<T>* list,A* a)
	{
		dllist_iter<T> result=dggt_internal_::def_dllist_iter(list);
		if (list&&a)
		{
			dlnode<T>* newNode=alloc<dlnode<T>>(a);
			if (newNode)
			{
				newNode->next=list->chain.ptr;
				list->chain.ptr->prev=newNode;
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
	dllist_iter<T> push(dllist<T>* list,const T& val,A* a)
	{
		dllist_iter<T> result=push(list,a);
		if (!is_end(result))
		{
			result.current->val=val;
		}
		return result;
	}

	template <typename T,typename A>
	dllist_iter<T> pop(dllist<T>* list,A* a)
	{
		dllist_iter<T> result=dggt_internal_::def_dllist_iter(list);
		if (list&&list->chain.count)
		{
			dlnode<T>* nodeToFree=list->chain.ptr;
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
	dllist_iter<T> peek(dllist<T>* list)
	{
		return dllist_iter<T>{list?list->chain.ptr:0,list};
	}

	template <typename T>
	dllist_iter<T> get(dllist<T>* list,u32 index)
	{
		dllist_iter<T> result=dllist_iter<T>{0,list};
		dllist_iter<T> it=get_iter(list);
		u32 i=0;
		while (!is_end(it)&&i<index)
		{
			++i;
			advance(it);
		}
		if (!is_end(it))
		{
			result=it;
		}
		return result;
	}

	template <typename T>
	dllist_iter<T> get_iter(dllist<T>* list)
	{
		return peek(list);
	}

	template <typename T>
	u32 get_count(const dllist<T>* list)
	{
		return list?list->chain.count:0;
	}

	template <typename T>
	b32 contains(dllist<T>* list,const T& item)
	{
		b32 result=false;
		for (dllist_iter<T> it=get_iter(list);
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
	dllist_iter<T> remove(
			dllist<T>* list,
			dlnode<T>* prev,
			dlnode<T>* toRemove,A* a)
	{
		dllist_iter<T> result={0,list,0};
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
	dllist_iter<T> clear(dllist<T>* list,A* a)
	{
		dllist_iter<T> result=dggt_internal_::def_dllist_iter(list);
		if (list)
		{
			dlnode<T>* current=list->chain.ptr;
			result.memIsValid=1;
			while (current)
			{
				dlnode<T>* nodeToFree=current;
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
	dllist_iter<T> insert(dllist<T>* list,dlnode<T>* prev,
			const T& val,A* a)
	{
		dllist_iter<T> result=dllist_iter<T>{0,list,0};
		if (list)
		{
			dlnode<T>* newNode=alloc<dlnode<T>>(a);
			if (newNode)
			{
				result.current=newNode;
				result.memIsValid=1;
				newNode->val=val;
				if (prev)
				{
					newNode->next=prev->next;
					newNode->prev=newNode;
					prev->next=newNode;
				}
				else
				{
					list->chain.ptr->prev=newNode;
					newNode->next=list->chain.ptr->next;
					list->chain.ptr=newNode;
				}
				++list->chain.count;
			}
		}
		return result;
	}
}
