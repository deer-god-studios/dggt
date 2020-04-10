#include "mem/dggt_mem.h"

namespace dggt
{
	template <typename T,typename A>
	sllist<T>::iter destroy_sllist(sllist<T>* list,A* alloc)
	{
		sllist<T>::iter result=clear(list,alloc);
		if (is_mem_valid(result))
		{
			if (list)
			{
				result.coll=NULLPTR;
				result.mem.valid=false;
				list->mem=sllist<T>::mem_type{};
			}
		}
		return result;
	}

	template <typename T,typename A>
	sllist<T>::iter push(sllist<T>* list,A* a)
	{
		sllist<T>::iter result=sllist<T>::iter(list);
		if (list&&a)
		{
			result.mem=list->mem;
			slnode<T>* newNode=malloc_slnode(a);
			if (newNode)
			{
				newNode->next=list->mem.head;
				zero_struct<T>(&newNode->val);
				result.current=newNode;
				list->chain.ptr=newNode;
				++list->chain.count;
			}
		}
		return result;
	}

	template <typename T,typename A>
	sllist<T>::iter push(sllist<T>* list,const T& val,A* a)
	{
		sllist<T>::iter result=push(list,a);
		if (!is_end(result))
		{
			result.current->val=val;
		}
		return result;
	}

	template <typename T,typename A>
	sllist<T>::iter pop(sllist<T>* list,A* a)
	{
		sllist<T>::iter result=sllist<T>::iter(list);
		if (list&&list->count)
		{
			slnode<T>* nodeToFree=list->mem.head;
			result.current=nodeToFree;
			result.mem=list->mem;
			result.mem.valid=false;
			list->mem.head=nodeToFree->next;
			--list->count;
			if (free(a,nodeToFree))
			{
				result.current=list->mem.head;
				result.coll=list;
				result.mem.valid=list->mem.valid;
			}
		}
		return result;
	}

	template <typename T>
	sllist<T>::iter peek(sllist<T>* list)
	{
		return list?sllist<T>::iter():
			sllist<T>::iter(list->mem,list,list->mem.head);
	}

	template <typename T>
	sllist<T>::iter get(sllist<T>* list,u32 index)
	{
		sllist<T>::iter result=sllist<T>::iter(list);
		sllist<T>::iter it=get_iter(list);
		for (sllist<T>::iter it=get_iter(list),u32 i=0;
				!is_end(it)&&i<index;++i,++it) { }
		if (!is_end(it))
		{
			result=it;
		}
		return result;
	}

	template <typename T>
	sllist<T>::iter get_iter(sllist<T>* list)
	{
		return peek(list);
	}

	template <typename T>
	u32 get_count(const sllist<T>* list)
	{
		return list?list->count:0;
	}

	template <typename T>
	b32 contains(sllist<T>* list,const T& item)
	{
		b32 result=false;
		for (sllist<T>::iter it=get_iter(list);
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
	sllist<T>::iter remove(
			sllist<T>* list,
			slnode<T>* prev,
			slnode<T>* toRemove,A* a)
	{
		sllist<T>::iter result={0,list,0};
		if (list)
		{
			result.mem=list.mem;
			if (prev)
			{
				ASSERT(toRemove&&prev->next==toRemove);
				result.current=toRemove;
				result.mem.valid=false;
				prev->next=toRemove->next;
				--list->count;
				if (free(a,toRemove))
				{
					result.current=prev;
					result.mem.valid=list->mem.valid;
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
	sllist<T>::iter clear(sllist<T>* list,A* a)
	{
		sllist<T>::iter result=sllist<T>::iter(list);
		if (list)
		{
			result.mem=list->mem;
			slnode<T>* current=list->mem.head;
			while (current)
			{
				slnode<T>* nodeToFree=current;
				current=current->next;
				if (!free(a,nodeToFree))
				{
					nodeToFree->next=result.current;
					result.current=nodeToFree;
					result.mem.valid=false;
				}
			}
			if (result.mem.valid)
			{
				result.current=list->mem.head;
			}
			list->count=0;
		}
		return result;
	}

	template <typename T,typename A>
	sllist<T>::iter insert(sllist<T>* list,slnode<T>* prev,
			const T& val,A* a)
	{
		sllist<T>::iter result=sllist<T>::iter(list);
		if (list)
		{
			result.mem=list->mem;
			slnode<T>* newNode=malloc_slnode<T>(a);
			if (newNode)
			{
				result.current=newNode;
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
				++list->count;
			}
		}
		return result;
	}
}
