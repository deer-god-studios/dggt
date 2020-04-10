#ifndef _DGGT_COLL_DLNODE_H_

#include "types/dggt_types.h"
#include "dggt_coll_pair.h"

namespace dggt
{
	template <typename T>
	struct dlnode
	{
		T val;
		dlnode<T>* prev;
		dlnode<T>* next;
	};

	template <typename T>
	struct dlpair:
		pair<dlnode<T>*>
	{
		dlnode<T>* get_head() { return first; }
		const dlnode<T>* get_head() const { return first; }
		dlnode<T>* get_tail() { return second; }
		const dlnode<T>* get_tail() const { return second; }
	};

	template <typename T,typename A>
	dlpair<T> malloc_dlpair(A* a,u32 count=1)
	{
		dlpair<T> result={};
		result.first=0;
		if (count)
		{
			dlnode<T>* current=malloc<dlnode<T>>(a);
			dlnode<T>* tail=current;
			if (current)
				*current=dlnode<T>();
			result.first=current;
			u32 c=1;
			while (current&&c<count)
			{
				current->next=malloc<dlnode<T>>(a);

				if (current->next)
					current->next->prev=current;

				tail=current;
				current=current->next;
				++c;
			}
			result.second=tail;
		}
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,dlpair<T>& pair,u32 count=1)
	{
		dlnode<T>* node=pair.get_head();
		b32 result=false;
		if (a&&node)
		{
			result=true;
			dlnode<T>* current=node;
			u32 i=0;
			while (current&&i<count)
			{
				dlnode<T>* toFree=current;
				current=current->next;
				result=result&&free(a,toFree);
				++i;
			}
		}
		return result;
	}
}

#define _DGGT_COLL_DLNODE_H_
#endif
