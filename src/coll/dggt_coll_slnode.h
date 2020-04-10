#ifndef _DGGT_COLL_SLNODE_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T>
	struct slnode
	{
		T val;
		slnode<T>* next;
	};

	template <typename T,typename A>
	slnode<T>* malloc_slnode(A* a,u32 count=1)
	{
		slnode<T>* result=0;
		if (count)
		{
			slnode<T>* current=malloc<slnode<T>>(a);
			*current=slnode<T>();
			result=current;
			u32 c=1;
			while (current&&c<count)
			{
				current->next=malloc<slnode<T>>(a);

				if (current->next)
					*(current->next)=slnode<T>();

				current=current->next;
				++c;
			}
		}
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,slnode<T>* node,u32 count=1)
	{
		b32 result=false;
		if (node&&a)
		{
			result=true;
			slnode<T>* current=node;
			u32 i=0;
			while (current&&i<count)
			{
				slnode<T>* toFree=current;
				current=current->next;
				result=result&&free(a,toFree);
				++i;
			}
		}
		return result;
	}

	template <typename T,typename A>
	b32 owns(A* a,slnode<T>* node)
	{
		b32 result=false;
		if (a&&node)
		{
			result=true;
			slnode<T>* h=node;
			while (h)
			{
				result=result&&owns(a,h);
				if (!result)
					break;
				h=h->next;
			}
		}
		return result;
	}
}

#define _DGGT_COLL_SLNODE_H_
#endif
