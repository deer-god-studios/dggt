#include "mem/dggt_mem.h"

namespace dggt
{
	template <typename T,typename A>
	typename sllist<T>::iter destroy_sllist(sllist<T>& list,A* alloc)
	{
		typename sllist<T>::iter result=clear(list,alloc);
		if (is_mem_valid(result))
		{
			result=typename sllist<T>::iter();
		}
		return result;
	}

	template <typename T,typename A>
	typename sllist<T>::iter push(sllist<T>& list,A* a)
	{
		typename sllist<T>::iter result=typename sllist<T>::iter(list);
		if (a)
		{
			slnode<T>* newNode=malloc_slnode<T>(a);
			if (newNode)
			{
				newNode->next=list.mem.head;
				zero_struct<T>(&newNode->val);
				list.mem.head=newNode;
				++list.count;
				result=peek(list);
			}
		}
		return result;
	}

	template <typename T,typename A>
	typename sllist<T>::iter push(sllist<T>& list,const T& val,A* a)
	{
		typename sllist<T>::iter result=push(list,a);
		if (is_mem_valid(result)&&
				result==peek(list))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,typename A>
	typename sllist<T>::iter pop(sllist<T>& list,A* a)
	{
		typename sllist<T>::iter result=typename sllist<T>::iter(list);
		if (get_count(list))
		{
			slnode<T>* nodeToFree=list.mem.head;
			result=peek(list);
			result.mem.valid=false;
			list.mem.head=nodeToFree->next;
			--list.count;
			if (free<slnode<T>>(a,nodeToFree))
			{
				result=peek(list);
			}
		}
		return result;
	}

	template <typename T>
	typename sllist<T>::iter peek(sllist<T>& list)
	{
		typename sllist<T>::iter result=typename sllist<T>::iter(list);
		result.current=sllist_key<T>(list.mem.head);
		return result;
	}

	template <typename T>
	typename sllist<T>::iter get(sllist<T>& list,u32 index)
	{
		typename sllist<T>::iter result=typename sllist<T>::iter(list);
		typename sllist<T>::iter it=get_iter(list);
		u32 i=0;
		for (typename sllist<T>::iter it=get_iter(list);
				!is_end(it)&&i<index;++it)
		{
			++i;
		}
		if (!is_end(it))
		{
			result=it;
		}
		return result;
	}

	template <typename T>
	typename sllist<T>::iter get_iter(sllist<T>& list)
	{
		return peek(list);
	}

	template <typename T>
	u32 get_count(const sllist<T>& list)
	{
		return list.count;
	}

	template <typename T>
	b32 contains(sllist<T>& list,const T& item)
	{
		b32 result=false;
		for (typename sllist<T>::iter it=get_iter(list);
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
	typename sllist<T>::iter remove(
			sllist<T>& list,
			typename sllist<T>::iter& prev,
			typename sllist<T>::iter& node,A* a)
	{
		slnode<T>* p=prev.current.node;
		slnode<T>* n=node.current.node;
		typename sllist<T>::iter result=typename sllist<T>::iter(list);
		{
			if (p)
			{
				result.current=sllist_key<T>(n);
				result.mem.valid=false;
				p->next=n->next;
				--list.count;
				if (free<T>(a,n))
				{
					result.current=sllist_key<T>(p);
					result.mem.valid=list.mem.valid;
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
	typename sllist<T>::iter clear(sllist<T>& list,A* a)
	{
		typename sllist<T>::iter result=typename sllist<T>::iter(list);
		slnode<T>* current=list.mem.head;
		while (current)
		{
			slnode<T>* nodeToFree=current;
			current=current->next;
			if (!free<slnode<T>>(a,nodeToFree))
			{
				nodeToFree->next=result.current.node;
				result.current=nodeToFree;
				result.mem.valid=false;
			}
		}
		if (result.mem.valid)
		{
			result.current=list.mem.head;
		}
		list.count=0;
		return result;
	}

	template <typename T,typename A>
	typename sllist<T>::iter insert(sllist<T>& list,
			typename sllist<T>::iter& node,
			const T& val,A* a)
	{
		slnode<T>* n=node.current.node;
		typename sllist<T>::iter result=typename sllist<T>::iter(list);
		slnode<T>* newNode=malloc_slnode<T>(a);
		if (newNode)
		{
			result.current=sllist_key<T>(newNode);
			newNode->val=val;
			if (n)
			{
				result.current=sllist_key<T>(n);
				newNode->next=n->next;
				n->next=newNode;
			}
			else
			{
				newNode->next=list.mem.head->next;
				list.mem.head=newNode;
			}
			++list.count;
		}
		return result;
	}
}
