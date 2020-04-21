
#include "mem/dggt_mem.h"

namespace dggt
{
	template <typename T,typename A>
	typename dllist<T>::iter destroy_dllist(dllist<T>& list,A* alloc)
	{
		typename dllist<T>::iter result=clear(list,alloc);
		if (is_mem_valid(result))
		{
			result=typename dllist<T>::iter();
		}
		return result;
	}

	template <typename T,typename A>
	typename dllist<T>::iter push(dllist<T>& list,A* a)
	{
		typename dllist<T>::iter result=typename dllist<T>::iter(list);
		if (a)
		{
			dlnode<T>* newNode=malloc<dlnode<T>>(a);
			if (newNode)
			{
				zero_struct<T>(&newNode->val);
				newNode->next=list.mem.pair.first;
				newNode->prev=0;
				list.mem.pair.first=newNode;
				if (get_count(list)==0)
				{
					list.mem.pair.second=newNode;
				}
				if (newNode->next)
				{
					newNode->next->prev=newNode;
				}

				result=peek(list);
				++list.count;
			}
		}
		return result;
	}

	template <typename T,typename A>
	typename dllist<T>::iter push(dllist<T>& list,const T& val,A* a)
	{
		typename dllist<T>::iter result=push(list,a);
		if (is_mem_valid(result)&&
				result==peek(list))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,typename A>
	typename dllist<T>::iter pop(dllist<T>& list,A* a)
	{
		typename dllist<T>::iter result=typename dllist<T>::iter(list);
		if (get_count(list))
		{
			dlnode<T>* nodeToFree=list.mem.pair.first;
			result.current=dllist_key<T>(nodeToFree);
			result.mem.valid=false;
			list.mem.pair.first=nodeToFree->next;
			if (list.mem.pair.first)
			{
				list.mem.pair.first->prev=0;
			}
			--list.count;
			if (free(a,nodeToFree))
			{
				result.current=peek(list);
			}
			if (get_count(list)<=1)
			{
				list.mem.pair.second=list.mem.pair.first;
			}
		}
		return result;
	}

	template <typename T>
	typename dllist<T>::iter peek(dllist<T>& list)
	{
		typename dllist<T>::iter result=typename dllist<T>::iter(list);
		result.current=dllist_key<T>(list.mem.pair.first);
		return result;
	}

	template <typename T>
	typename dllist<T>::iter get_begin(dllist<T>& list)
	{
		return get_iter(list);
	}

	template <typename T>
	typename dllist<T>::iter get_end(dllist<T>& list)
	{
		typename dllist<T>::iter result=typename dllist<T>::iter(list);
		result.current=dllist_key<T>(list.mem.pair.second);
		return result;
	}


	template <typename T>
	typename dllist<T>::iter get(dllist<T>& list,u32 index)
	{
		typename dllist<T>::iter result=typename dllist<T>::iter(list);
		typename dllist<T>::iter it=get_iter(list);
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
	typename dllist<T>::iter get_iter(dllist<T>& list)
	{
		return peek(list);
	}

	template <typename T>
	u32 get_count(const dllist<T>& list)
	{
		return list.count;
	}

	template <typename T>
	b32 contains(dllist<T>& list,const T& item)
	{
		b32 result=false;
		for (typename dllist<T>::iter it=get_iter(list);
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
	typename dllist<T>::iter remove(
			dllist<T>& list,
			dlnode<T>* prev,
			dlnode<T>* toRemove,A* a)
	{
		typename dllist<T>::iter result={0,list,0};
		{
			if (prev)
			{
				ASSERT(toRemove&&prev->next==toRemove);
				result.current=toRemove;
				result.mem.valid=false;
				prev->next=toRemove->next;
				--list.count;
				if (free(a,toRemove))
				{
					result.current=prev;
					result.list=list;
					result.mem.valid=false;
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
	typename dllist<T>::iter clear(dllist<T>& list,A* a)
	{
		typename dllist<T>::iter result=typename dllist<T>::iter(list);
		{
			dlnode<T>* current=list.mem.pair.get_head();
			result.mem.valid=true;
			while (current)
			{
				dlnode<T>* nodeToFree=current;
				current=current->next;
				if (!free(a,nodeToFree))
				{
					nodeToFree->next=result.current.node;
					result.current=dllist_key<T>(nodeToFree);
					result.mem.valid=0;
				}
			}
			if (result.mem.valid)
			{
				result.current=dllist_key<T>(list.mem.pair.get_head());
			}
			list.count=0;
		}
		return result;
	}

	template <typename T,typename A>
	typename dllist<T>::iter insert(dllist<T>& list,dlnode<T>* prev,
			const T& val,A* a)
	{
		typename dllist<T>::iter result=typename dllist<T>::iter{0,list,0};
		{
			dlnode<T>* newNode=alloc<dlnode<T>>(a);
			if (newNode)
			{
				result.current=newNode;
				result.mem.valid=false;
				newNode->val=val;
				if (prev)
				{
					newNode->next=prev->next;
					newNode->prev=newNode;
					prev->next=newNode;
				}
				else
				{
					list.mem.pair.first->prev=newNode;
					newNode->next=list.mem.pair.get_head()->next;
					list.mem.pair.first=newNode;
				}
				++list.count;
			}
		}
		return result;
	}
}
